#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/**
 * RACE CONDITIONS
 *  - accessing the same variable without protecting it leads to errors
 *  - a thread could access a variable whil the other would access the same
 *  and they would both work on it without taking the other thread's operations
 *  into account
 *  NB: with gcc -S we can compile our file into assembly
 * 
 *  => leads to CORRUPTED DATA!
*/

int mails = 0;

void    *routine(void *param) {
    for (int i = 0; i < 1000000; i++) {
        mails++;
    }
}

int main(int argc, char **argv) {
    pthread_t   t1, t2;

    if (pthread_create(&t1, NULL, routine, NULL) != 0) {
        return (EXIT_FAILURE);
    }
    if (pthread_create(&t2, NULL, routine, NULL) != 0) {
        return (EXIT_FAILURE);
    } 
    if (pthread_join(t1, NULL) != 0) { // Waits for the thread
        return (EXIT_FAILURE);
    }
    if (pthread_join(t2, NULL) != 0) { // Waits for the thread
        return (EXIT_FAILURE);
    }
    printf("Number of mails: %d\n", mails);
    return (0);
}