/*
 * shm-client - client program to demonstrate shared memory.
 * shm-client - not sure of the origin of these code segments.
 * possibly: David Marshalls course : http://www.cs.cf.ac.uk/Dave/C/CE.html
 * or Steve Holmes : http://www2.its.strath.ac.uk/courses/c/
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SHMSZ     27

int
main()
{
    int shmid, shmid2;
    key_t key, key2;
    char *shmI, *shmS, *s;

    /*
     * We need to get the segment named
     * "5678", created by the server.
     */
    key = 8167;

    /*
     * Locate the segment for int
     */
    if( (shmid = shmget(key, SHMSZ, 0666)) < 0 )
    {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if( (shmI = shmat(shmid, NULL, 0)) == (char *) -1 )
    {
        perror("shmat");
        exit(1);
    }


    key2 = 8168;
     /*
     * Locate the segment for string
     */
    if( (shmid2 = shmget(key2, SHMSZ, 0600)) < 0 )
    {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if( (shmS = shmat(shmid2, NULL, 0)) == (char *) -1 )
    {
        perror("shmat");
        exit(1);
    }



    // B checks for 1 in shared memory
    s = shmI;
    while(*s != 1){
        sleep(1);
    }

    // write into string shared memory
    strcpy(shmS, "I am Process B");
    usleep(3000000);
    // change integer shared memory
    *shmI = 2;


    // detach the shared memory
    shmdt(shmI);
    shmdt(shmS);


    // B quits
    return 0;

}
