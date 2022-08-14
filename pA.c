#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h> /* for exit */
#include <string.h>
#include <unistd.h>


/* 
 * shm-server - not sure of the origin of code segment.
 * Old source, not sure of the origin
 *  possibly: David Marshalls course : http://www.cs.cf.ac.uk/Dave/C/CE.html
 * or Steve Holmes : http://www2.its.strath.ac.uk/courses/c/
 */



#define SHMSZ     27


int 
main()
{
    char c;
    int shmid, shmid2;
    key_t key, key2;
    char *shmS, *s, *shmI;


    /*
     * We'll name our shared memory segment
     * "5678".
     */

    key = 8167;

    /*
     * Create the segment. for int
     */
    if( (shmid = shmget(key, SHMSZ, IPC_CREAT | 0600)) < 0 )
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

    // create for string?   
    if( (shmid2 = shmget(key2, SHMSZ, IPC_CREAT | 0666)) < 0 )
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



    // write 1 to integer shared memory
    *shmI = 1;
   

    // write string
    strcpy(shmS, "I am Process A");
    printf("%s \n", shmS);
    

    // poll until integer shared memory is 2
    while(*shmI != 2)
        sleep(1);

    // print new string shared memory
    printf("%s \n", shmS);
    

    // poll until integer shared memory is 3
    while(*shmI != 3)
        sleep(1);

    // print new string shared memory
    printf("%s \n", shmS);

    // print goodbye
    printf("GoodBye");

    // detach and remove the shared memory
    shmdt(shmI);
    shmctl(shmid, IPC_RMID, NULL);

    shmdt(shmS);
    shmctl(shmid2, IPC_RMID, NULL);

    return 0;


}
 