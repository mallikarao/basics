#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SUCCESS                 0
#define ERROR                   -1
#define FERROR                  -2

#define FILENAME_LEN            128
#define MAX_FILE_SIZE           10000

#define READ                    0x2
#define WRITE                   0x4

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
 /

struct file_entry {
    const char *filename;   // file identified by its filename
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

void
file_cache_destroy(struct file_cache *cache)
{
    int i;
    
    for(i=0; i<cache->max_cache_entries; i++) { 
        if(cache->farray[i]->dirty == 1) {
            /*
             * This entry has been modified, so we need to write to disk
             * fwrite from farray[i]->data to file with filename as a handle
             */
            FILE *fd;
            fd = fopen(filename, 'w');
            if (fd ==NULL) {
               printf("File could not be opened to write\n");
            }
            fwrite(cache->farray[i]->data, sizeof(char), MAX_FILE_SIZE, fd);
            fclose(fd);
            cache->farray[i]->dirty = 0;
        }
    }
}

void
print_cache_details(struct file_cache *cache)
{
    if(cache) {
        int space_left = cache->cachesize - (cache->num_cache_entries*MAX_FILE_SIZE);
        printf("cache:\n\tnum of files: %d\n\tcachesize: %d\n\tRemaining space:%d\n", cache->num_cache_entries, cache->cachesize, space_left);
    } else {
        printf("Cache empty, not yet constructed\n");
    }
}

/*
 * const char * ensures we cannot change the contents of the data pointed to by
 * the char * pointer, neat!
 */

const char *
file_cache_file_data(file_cache *cache, const char *file)
{
    int i;
    
    // If file not pinned, do not bother giving R perm
    // If filename not even found in cache, do not bother giving R perm

    for(i = 0; i < max_cache_entries; i++) {
        if ((cache->farray[i]->filename == file) &&
            (cache->farray[i]->pin_count != 0)) {
            // provide 'R' permissions on the data buffer ptd. by farray[i] 
            printf("The file was pinned, hence gave it read access\n");
            return ((const char *)cache->farray[i]->filename);
        } else {
            printf("File not buffered | pinned in cache to assign R perm\n");
            return (file);
        }
    }
}

char *
file_cache_mutable_file_data(struct file_cache *cache, const char *file)
{
    int i;
    
    // If file not pinned, do not bother giving W perm
    // If filename not even found in cache, then do not bother giving W perm
    for(i = 0; i < cache->max_cache_entries; i++) {
        if ((cache->farray[i]->filename == file) && 
            (cache->farray[i]->pin_count != 0)) {
            // provide 'W' permissions on the data buffer ptd. by farray[i]
            cache->farray[i]->dirty = 1;
            printf("File pinned, giving write access\n");
            return ((char *)cache->farray[i]->filename);
        } else {
            printf("File not buffered | pinned in cache to assign W perm\n");
            return (file);
        }
    }
}

void
file_cache_unpin_files(struct file_cache *cache,const char **files, int num_files)
{
    int i;
    /*
     * unpinning = decrementing the pincount
     */
    if(cache->farray[i]->pin_count) {
        cache->farray[i]->pin_count--;
    } else {
        printf("Cannot unpin a page which is not yet pinned\n");
    }
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
     * /
     for(i = 0; i < max_cache_entries; i++) {
        if(cache->farray[i]->pin_count == 0) {
            /*
             * Copy the filename into farray[i]->filename
             * Open the file, with right permissions, 
             * fread from file to entry's data buffer
             * fclose the file
             */
            assert(cache->farray[i]->dirty!=0);
            /*
             * makes sure dirty bit is 0, when pincount is 0
             */
            strncpy(cache->farray[i]->filename, filename, FILENAME_LEN);
            FILE *fd;
            fd = fopen(filename, 'r');
            if(fd ==  NULL) {
                printf("file open error\n");
                fclose(fd);
                return FERROR;
            }
            num_bytes_read = fread(cache->farray[i]->data, 1, MAX_FILE_SIZE, fd);
            printf("The number of bytes of file read: %d\n", num_bytes_read);
            cache->farray[i]->pin_count++;
            return SUCCESS;
        }
    }
    /*
     * If we came here that means, we did not find a page that was 'not dirty'
     * So, just wait around till this routine finds a page which is unpinned
     */
    //while(cache->farray[i]->dirty == 0) {
      //  sleep();
    //}
    
    return ERROR;
}

void
file_cache_pin_files(struct file_cache *cache, const char **files,
                            int num_files)
{
    int found;
 
    for(i = 0; i < num_files; i++) {
        found = 0;
        for(j = 0; j < max_cache_entries; j++) {
            if(cache->farray[i]->filename == files[i]) { //how to find the name
                found = 1; // if found, break from for loop to increment pincount
                break;
            }
        }
        if(found) {
            cache->farray[i]->pin_count++;
        } else {
            get_file_to_cache(files[i]); // file not found, so lets get it to cache
        }
    }
}

struct file_cache *
file_cache_construct(int max_cache_entries)
{
    struct file_cache *cache;
    int i;

     /*
      * Cache object, is a pointer to our array. This gives us the flexibility
      * of having multiple cache objects in future, or storing cache related
      * data in this structure.
      */
    cache = (struct file_cache *) malloc(sizeof (struct file_cache));
    cache->max_cache_entries = max_cache_entries;

    /*
     * This array holds pointers to file_entry objects
     */
    cache->farray = (struct file_entry **) malloc(max_cache_entries * sizeof
    (struct file_entry *));
    
    /*
     * The actual file_entry objects, inside which we have to malloc for two
     * pointers, filename and file data buffer size of 10KB and set to 0
     * initially.
     */
    for(i = 0; i < max_cache_entries; i++) {
        cache->farray[i] = (struct file_entry *) malloc(sizeof(struct file_entry));
        cache->farray[i]->data = malloc(MAX_FILE_SIZE);
        memset(cache->farray[i]->data, 0, MAX_FILE_SIZE);
        cache->farray[i]->filename = malloc(sizeof (char) * FILENAME_LEN);
    }
    return (cache);
}

int main(int argc, char **argv)
{
    struct file_cache *cache;
    int max_cache_entries;
    scanf("How many entries do you want the cache to support, entre: %d\n",
    &max_cache_entries);
    cache = file_cache_construct(max_cache_entries); 
    file_cache_destroy(cache);

    print_cache_details(cache);
    
}
