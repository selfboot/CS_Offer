/*
* @Author: xuelangZF
* @Date:   2016-06-09 20:18:58
* @Last Modified time: 2016-06-09 20:38:31
* Refer to: https://www.cs.cf.ac.uk/Dave/C/node27.html
*/
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ     27

int main()
{
    int shmid;
    key_t key;
    char *shm, *s;

    // We need to get the segment named "5678", created by the server.
    key = 5678;

    // Locate the segment.
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Now we attach the segment to our data space.
    if ((shm = (char *)shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Now read what the server put in the memory.
    for (s = shm; *s != 0; s++)
        putchar(*s);
    putchar('\n');

    /*
     * Finally, change the first character of the segment to '*',
     * indicating we have read the segment.
     */
    *shm = '*';

    exit(0);
}
