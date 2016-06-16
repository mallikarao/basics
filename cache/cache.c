#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define SUCCESS true
#define ERROR   false

#define FILENAME_LEN            128
#define MAX_FILE_SIZE           10000

/*
 * Assumptions made:
 * 1. dirty bit 0 = not written to/not dirty.
 *    dirty bit = 1 = written to/ is dirty
 * 2. The case where pin_count is 0 and dirty bit is 1 is assumed to never
 *    happen/invalid. Though using ASSERT on user defined vars is not the right
 *    way, we still use to help us recognize a problem ahead of time.
 * 3. In functions where we give read, write access, just by what we return, we
 *    assume whether the file can be further opend for reading or not (char * vs
 *    const char *) 
 * 4. All operations happen one file at a time as of now. 
 */

struct file_entry {
    char *filename;   // file identified by its filename
    char *data;             // ptr to data buffer in cache
    int perm;               // R/W permission
    int pin_count;          // pin_count > 1
    int dirty;              // if 1, write to disk.
};

struct file_cache {
    struct file_entry **farray;     // array of pointers to file entries
    int max_cache_entries;          // user given value
};

/*
 * Start modules
 */

static void
file_cache_destroy(struct file_cache *cache)
{
    int i;
    printf("Flushing out the dirty contents to disk\n"); 
    for(i=0; i<cache->max_cache_entries; i++) { 
        if(cache->farray[i]->dirty == 1) {
            /*
             * This entry has been modified, so we need to write to disk
             * fwrite from farray[i]->data to file with filename as a handle
             */
            FILE *fd;
            char *filename = cache->farray[i]->filename;
            fd = fopen(filename, "w");
            if (fd ==NULL) {
               printf("File could not be opened to write\n");
            }
            fwrite(cache->farray[i]->data, sizeof(char),
            strlen(cache->farray[i]->data), fd);
            fclose(fd);
            cache->farray[i]->dirty = 0;
        }
    }
    printf("\n");
}

/*
 * const char * ensures we cannot change the contents of the data pointed to by
 * the char * pointer, neat!
 */

static const char *
file_cache_file_data(struct file_cache *cache, const char *file)
{
    int i;
    
    // If file not pinned, do not bother giving R perm
    // If filename not even found in cache, do not bother giving R perm

    printf("Trying to give read access to %s\n", file);
    for(i = 0; i < cache->max_cache_entries; i++) {
        if ((strcmp(file, cache->farray[i]->filename) == 0) && (cache->farray[i]->pin_count != 0)) {
            //provide 'R' permissions on the data buffer ptd. by farray[i] 
            printf("The file was pinned, hence gave it read access\n");
            printf("\n");
            return ((const char *)cache->farray[i]->filename);
        }
    }
    // If we came here, then the page was not pinned or found.
    printf("File not pinned/buffered in cache to assign R access\n");
    printf("\n");
    return (file);
}

static char *
file_cache_mutable_file_data(struct file_cache *cache, const char *file)
{
    int i;
    
    // If file not pinned, do not bother giving W perm
    // If filename not even found in cache, then do not bother giving W perm
    printf("Trying to give write access to %s\n", file);
    for(i = 0; i < cache->max_cache_entries; i++) {
        if ((strcmp(file, cache->farray[i]->filename) == 0) && (cache->farray[i]->pin_count != 0)) {
            // provide 'W' permissions on the data buffer ptd. by farray[i]
            cache->farray[i]->dirty = 1;
            printf("File pinned, giving write access\n");
            printf("\n");
            return ((char *)cache->farray[i]->filename);
        }
    }
    // If we came here, the page was not pinned/found
    printf("File not pinned/buffered in cache to assign W access\n");
    printf("\n");
    return ((char *)file);
}

static void
file_cache_unpin_files(struct file_cache *cache, const char **files, int num_files)
{
    int i, j, len;

    printf("Trying to unpin %s\n", *files);
    /*
     * unpinning = decrementing the pincount
     */
    for(i = 0; i < num_files; i++) {
        for(j = 0; j < cache->max_cache_entries; j++) {
            if(strcmp(cache->farray[j]->filename, files[i]) == 0) {
                if(cache->farray[j]->pin_count) {
                // if pincount is 1 and dirty bit is 1, fwrite to disk
                    if((cache->farray[j]->pin_count ==1) &&
                        (cache->farray[j]->dirty == 1)) {
                        printf("File to be unpinned: %s\n", files[0]);
                        FILE *fd;
                        fd = fopen(files[0], "w");
                        if (fd ==NULL) {
                            printf("File could not be opened to write\n");
                        }
                        len = strlen(cache->farray[j]->data);
                        printf("Flushing buffer contents to disk file: %s\n",
                        cache->farray[j]->data);
                        fwrite(cache->farray[j]->data, sizeof(char), len, fd);
                        fclose(fd);
                        cache->farray[j]->dirty = 0;
                    }
                    (cache->farray[j]->pin_count)--;
                } else {
                    printf("Cannot unpin a page which is not yet pinned\n");
                }
            }
        }
    }
    printf("\n");
}

static bool
get_file_to_cache(struct file_cache *cache, const char *filename)
{
    int i;

    int num_bytes_read;
    
    /*
     * We did not find the file in the cache, so let us first check if we have a
     * free entry, if yes, let us just put it there.
     * and return SUCCESS
     */
    
     for(i = 0; i < cache->max_cache_entries; i++) {
        if(cache->farray[i]->pin_count == 0) {
            /*
             * Copy the filename into farray[i]->filename
             * Open the file, with right permissions, 
             * fread from file to entry's data buffer
             * fclose the file
             */
            assert(cache->farray[i]->dirty == 0);
            /*
             * makes sure dirty bit is 0, when pincount is 0
             */
            memcpy(cache->farray[i]->filename, filename, FILENAME_LEN-1);
            printf("Got %s in cache\n", cache->farray[i]->filename);
            FILE *fd;
            fd = fopen(filename, "r+"); // If a file exists, open in RW mode
            if(fd == NULL) {
                fd = fopen(filename, "w");// maybe it does not exist, create it.
            }
            if(fd ==  NULL) {
                printf("file open error\n");
                fclose(fd);
                printf("\n");
                return ERROR;
            }
            num_bytes_read = fread(cache->farray[i]->data, 1, MAX_FILE_SIZE, fd);
            printf("The number of bytes of file read: %d\n", num_bytes_read);
            (cache->farray[i]->pin_count)++;
            printf("pin count of %s: %d\n", cache->farray[i]->filename,
            cache->farray[i]->pin_count);
            printf("\n");
            return SUCCESS;
        }
    }
    /*
     * If we came here that means, we did not find a page that was 'not dirty'
     * So, just wait around till this routine finds a page which is unpinned
     */
    printf("\n");
    return ERROR;
}

static void
file_cache_pin_files(struct file_cache *cache, const char **files,
                            int num_files)
{
    int found;
    int i, j;
    printf("Trying to pin files: %s\n", *files);

    for(i = 0; i < num_files; i++) {
        found = 0;
        for(j = 0; j < cache->max_cache_entries; j++) {
            if(strcmp(cache->farray[i]->filename, files[i]) == 0) { //how to find the name
                printf("found %s in cache\n", files[i]);
                found = 1; // if found, break from for loop to increment pincount
                break;
            }
        }
        if(found) {
            cache->farray[i]->pin_count++;
        } else {
            printf("File not yet in cache, so getting it now\n");
            // file not found, so lets get it to cache 
            if (get_file_to_cache(cache, files[i]) == SUCCESS) {
                printf("Cache was not full, hence pinned successfully\n");
            } else {
                printf("Cache was full, hence pinning was unsuccessful\n");
            }
        }
    }
    printf("\n");
}

void
print_cache_details(struct file_cache *cache)
{
    int i;
    for(i = 0; i < cache->max_cache_entries; i++) {
        if(cache->farray[i]->pin_count!=0) {
            printf("file: pin: dirty:: %s: %d: %d\t", cache->farray[i]->filename,
            cache->farray[i]->pin_count, cache->farray[i]->dirty);
        }
    }
    printf("\n");
}

static struct file_cache *
file_cache_construct(int max_cache_entries)
{
    int i;

    printf("Initialing our data structures\n");
    struct file_cache *cache;

     /*
      * Cache object, is a pointer to our array. This gives us the flexibility
      * of having multiple cache objects in future, or storing cache related
      * data in this structure.
      */
    cache = (struct file_cache *) malloc(sizeof (struct file_cache));
    if(!cache) {
        printf("malloc() for cache failed\n");
        exit(1);
    }
    cache->max_cache_entries = max_cache_entries;
    printf("cache->max_cache_entries: %d\n", cache->max_cache_entries);
    /*
     * This array holds pointers to file_entry objects
     */
    cache->farray = (struct file_entry **) malloc(max_cache_entries * sizeof
    (struct file_entry *));
    if(!cache->farray) exit(1);
    
    /*
     * The actual file_entry objects, inside which we have to malloc for two
     * pointers, filename and file data buffer size of 10KB and set to 0
     * initially.
     */
    for(i = 0; i < max_cache_entries; i++) {
        cache->farray[i] = (struct file_entry *) malloc(sizeof(struct file_entry));
        if(!cache->farray[i]) exit(1);
        cache->farray[i]->data = malloc(MAX_FILE_SIZE);
        if(!cache->farray[i]->data) exit(1);
        memset(cache->farray[i]->data, 0, MAX_FILE_SIZE);
        cache->farray[i]->filename = malloc(sizeof (char) * FILENAME_LEN);
        if(!cache->farray[i]->filename) exit(1);
        cache->farray[i]->pin_count = 0;
        cache->farray[i]->dirty = 0;
    }
    printf("\n");
    return (cache);
}

static bool
write_to_buf(struct file_cache *cache, char *file)
{
    int i;
    
    printf("filename in write_to_buf: %s\n", file);
    for(i = 0; i < cache->max_cache_entries; i++) {
        if ((strcmp(file, cache->farray[i]->filename) == 0)) {
            cache->farray[i]->data = "abc123 overwritten over original file";
            printf("After write, cache buffer contains: %s\n",
            cache->farray[i]->data);
            return SUCCESS;
        }
    }
    return ERROR;
}

int main(int argc, char **argv)
{
    struct file_cache *cache;
    int max_cache_entries;
    printf("How many entries do you want the cache to support, please enter\n");
    scanf("%d", &max_cache_entries);
    cache = file_cache_construct(max_cache_entries);

    // Driver functions to check if after pinning, we are able to give R and W
    // access

    printf("TEST 1\t Driver functions to check if after pinning, we are able to give R and W access\n");

    char *filename = "test1.txt";
    const char *ret_file1;
    file_cache_pin_files(cache, (const char **) &filename, 1);
    ret_file1 = file_cache_file_data(cache, filename);
    file_cache_mutable_file_data(cache, filename);
    write_to_buf(cache, (char *)ret_file1);
    print_cache_details(cache);
    
    // Driver function to test multiple pinning
    printf("TEST 2\t Driver function to test multiple pinning\n");
    
    file_cache_pin_files(cache, (const char **) &filename, 1);
    print_cache_details(cache);

    // Driver functions to check if R and W access is denied if entry is not yet
    // pinned
    
    printf("TEST 3\t Driver functions to check if R and W access is denied if entry is not yet pinned\n");

    char *filename2 = "test2.txt";
    file_cache_file_data(cache, filename2);
    file_cache_mutable_file_data(cache, filename2);
    print_cache_details(cache);

    // Driver functions to check if R and W access is denied if file is not
    // matching, test4.txt did not even exist in folder.

    printf("TEST 4\t Driver functions to check if R and W access is denied if file is not matching, test4.txt did not even exist in folder.\n");

    char *filename4 = "test4.txt";
    file_cache_file_data(cache, filename4);
    file_cache_mutable_file_data(cache, filename4);
    print_cache_details(cache);

    // will pinning create the file for me?
    // Pin should create file if it does not exist
    printf("TEST 5\t Driver function to check if matching, test4.txt did not even exist in folder.\n");

    file_cache_pin_files(cache, (const char **) &filename4, 1);
    file_cache_file_data(cache, filename4);
    file_cache_mutable_file_data(cache, filename4);
    print_cache_details(cache);

    // Can I really write to an entry marked with read access
    printf("TEST 6\t Driver to check Can I really write to an entry marked with read access\n");
    char *ret_file2;
    file_cache_pin_files(cache, (const char **) &filename2, 1);
    print_cache_details(cache);
    ret_file2 = file_cache_mutable_file_data(cache, filename2);
    write_to_buf(cache, ret_file2);
    file_cache_unpin_files(cache, (const char **)&filename2, 1);
    print_cache_details(cache);

    // Write to test4, but do not call unpin, so file on disk will not have
    // changes yet
    printf("TEST 7\t Write to test4, but do not call unpin, so file on disk will not have changed yet\n");
    char *ret_file3;
    ret_file3 = file_cache_mutable_file_data(cache, filename4);
    write_to_buf(cache, ret_file3);
    print_cache_details(cache);

    // Driver functions to pin test3.txt, also give read access to it, but do
    // not write anything. So this will be our test for pinned and clean entry.

    printf("TEST 8\t Driver functions to pin test3.txt, also give read access to it, but do not write anything. So this will be our test for pinned and clean entry.\n");
    char *filename3 = "test3.txt";
    file_cache_pin_files(cache, (const char **) &filename3, 1);
    file_cache_file_data(cache, filename3);
    print_cache_details(cache);
    
    /*
     * Now when we call destroy(), we should flush what we have pinned and
     * dirtied to disk. So, test1.txt, test2.txt and test4.txt will be
     * overwritten with our buffer, whereas, test3.txt is untouched, because we
     * did not dirty it.
     */
    print_cache_details(cache);
    printf("TEST 9\t Diver to check flushing to disk\n");
    file_cache_destroy(cache);
    print_cache_details(cache);
}
