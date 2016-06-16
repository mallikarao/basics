1. This is a single thread model implementation.
2. Assumtions made:

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

Test cacse implemented:
----------------------
----------------------
1. Driver functions to check if after pinning, we are able to give R and W
access

2. Driver function to test multiple pinning

3. Driver functions to check if R and W access is denied if entry is not yet
pinned 

4. Driver functions to check if R and W access is denied if file is not
matching, test4.txt did not even exist in folder.

5. Will pinning create the file for me?, It should, and it does. It tries to
open file in r+ mode, then it finds test4.txt does not exists, so it will create
one in w mode.

6. Can I really write to an entry marked with read access

7. Write to test4, but do not call unpin, so file on disk will not have
changes yet

8. Driver functions to pin test3.txt, also give read access to it, but do
not write anything. So this will be our test for pinned and clean entry.


9. Now when we call destroy(), we should flush what we have pinned and
dirtied to disk. So, test1.txt, test2.txt and test4.txt will be
overwritten with our buffer, whereas, test3.txt is untouched, because we
did not dirty it.
This is possible because we marked mode in file open as r+.

Notes:
The idea is that, we only have 3 test files to start with test1.txt, test2.txt
and test3.txt with their own contents.
We see if test4.txt gets created as part of pinning for us.
Also, we try to overwrite some buffer contents when we call the mutable_file()

Everything is one file cache.c, since the structures were simple and few, did
not create a seperate .h file.
It was compiled using gcc 4.2.1
Arch used: x86_64
Platform/OS used: MAC OSX 10.8.5

I had test files and cachec in same pwd

------*****--------
-rw-r--r--   1 mallikarao  staff  14746 Nov  3 00:25 cache.c
-rw-r--r--   1 mallikarao  staff     18 Nov  3 00:37 test1.txt
-rw-r--r--   1 mallikarao  staff     18 Nov  3 00:37 test2.txt
-rw-r--r--   1 mallikarao  staff     18 Nov  3 00:38 test3.txt
-rw-r--r--   1 mallikarao  staff   2051 Nov  3 00:39 readme.txt
drwxr-xr-x  16 mallikarao  staff    544 Nov  3 00:39 .
MALLRAO-M-612B:cache mallikarao$ 
MALLRAO-M-612B:cache mallikarao$ 
MALLRAO-M-612B:cache mallikarao$ 
MALLRAO-M-612B:cache mallikarao$ cat test*.txt
This is test1.txt
This is test2.txt
This is test3.txt
MALLRAO-M-612B:cache mallikarao$ pwd
/Users/mallikarao/Documents/practise/cache
MALLRAO-M-612B:cache mallikarao$ 
-------******-------
After files are flushed, test file contents change accordingly.

MALLRAO-M-612B:cache mallikarao$ cat test*.txt
abc123 overwritten over original fileabc123 overwritten over original fileabc123
overwritten over original fileMALLRAO-M-612B:cache mallikarao$ 
------******-------

I had lots of fun doing this and while it is an interesting problem and I am
till improving it as ideas come to me, I decide to send it over with this
current state of program, because sometimes done is better than better. Thank you, Nutanix ! :)

One complete run of all driver functions are here:
// begin test run

MALLRAO-M-612B:cache mallikarao$ gcc cache.c
MALLRAO-M-612B:cache mallikarao$ ./a.out 
How many entries do you want the cache to support, please enter
3
Initialing our data structures
cache->max_cache_entries: 3

TEST 1   Driver functions to check if after pinning, we are able to give R and W
access
Trying to pin files: test1.txt
File not yet in cache, so getting it now
Got test1.txt in cache
The number of bytes of file read: 37
pin count of test1.txt: 1

Cache was not full, hence pinned successfully

Trying to give read access to test1.txt
The file was pinned, hence gave it read access

Trying to give write access to test1.txt
File pinned, giving write access

filename in write_to_buf: test1.txt
After write, cache buffer contains: abc123 overwritten over original file
file: pin: dirty:: test1.txt: 1: 1  
TEST 2   Driver function to test multiple pinning
Trying to pin files: test1.txt
found test1.txt in cache

file: pin: dirty:: test1.txt: 2: 1  
TEST 3   Driver functions to check if R and W access is denied if entry is not
yet pinned
Trying to give read access to test2.txt
File not pinned/buffered in cache to assign R access

Trying to give write access to test2.txt
File not pinned/buffered in cache to assign W access

file: pin: dirty:: test1.txt: 2: 1  
TEST 4   Driver functions to check if R and W access is denied if file is not
matching, test4.txt did not even exist in folder.
Trying to give read access to test4.txt
File not pinned/buffered in cache to assign R access

Trying to give write access to test4.txt
File not pinned/buffered in cache to assign W access

file: pin: dirty:: test1.txt: 2: 1  
TEST 5   Driver function to check if matching, test4.txt did not even exist in
folder.
Trying to pin files: test4.txt
File not yet in cache, so getting it now
Got test4.txt in cache
The number of bytes of file read: 37
pin count of test4.txt: 1

Cache was not full, hence pinned successfully

Trying to give read access to test4.txt
The file was pinned, hence gave it read access

Trying to give write access to test4.txt
File pinned, giving write access

file: pin: dirty:: test1.txt: 2: 1  file: pin: dirty:: test4.txt: 1: 1  
TEST 6   Driver to check Can I really write to an entry marked with read access
Trying to pin files: test2.txt
File not yet in cache, so getting it now
Got test2.txt in cache
The number of bytes of file read: 37
pin count of test2.txt: 1

Cache was not full, hence pinned successfully

file: pin: dirty:: test1.txt: 2: 1  file: pin: dirty:: test4.txt: 1: 1  file:
pin: dirty:: test2.txt: 1: 0    
Trying to give write access to test2.txt
File pinned, giving write access

filename in write_to_buf: test2.txt
After write, cache buffer contains: abc123 overwritten over original file
Trying to unpin test2.txt
File to be unpinned: test2.txt
Flushing buffer contents to disk file: abc123 overwritten over original file

file: pin: dirty:: test1.txt: 2: 1  file: pin: dirty:: test4.txt: 1: 1  
TEST 7   Write to test4, but do not call unpin, so file on disk will not have
changed yet
Trying to give write access to test4.txt
File pinned, giving write access

filename in write_to_buf: test4.txt
After write, cache buffer contains: abc123 overwritten over original file
file: pin: dirty:: test1.txt: 2: 1  file: pin: dirty:: test4.txt: 1: 1  
TEST 8   Driver functions to pin test3.txt, also give read access to it, but do
not write anything. So this will be our test for pinned and clean entry.
Trying to pin files: test3.txt
File not yet in cache, so getting it now
Got test3.txt in cache
The number of bytes of file read: 0
pin count of test3.txt: 1

Cache was not full, hence pinned successfully

Trying to give read access to test3.txt
The file was pinned, hence gave it read access

file: pin: dirty:: test1.txt: 2: 1  file: pin: dirty:: test4.txt: 1: 1  file:
pin: dirty:: test3.txt: 1: 0    
file: pin: dirty:: test1.txt: 2: 1  file: pin: dirty:: test4.txt: 1: 1  file:
pin: dirty:: test3.txt: 1: 0    
TEST 9   Diver to check flushing to disk
Flushing out the dirty contents to disk

file: pin: dirty:: test1.txt: 2: 0  file: pin: dirty:: test4.txt: 1: 0  file:
pin: dirty:: test3.txt: 1: 0    
MALLRAO-M-612B:cache mallikarao$ 
// end of test run
