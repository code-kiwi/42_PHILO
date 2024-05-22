#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/**
 * BASIC INTRODUCTION
*/

void    *routine(void *param) {
    printf("Test from thread\n");
    sleep(3);
    printf("Ending Thread...\n");
}

int main(int argc, char **argv) {
    pthread_t   t1, t2;

    if (pthread_create(&t1, NULL, routine, NULL) != 0)
        return (EXIT_FAILURE);
    if (pthread_create(&t2, NULL, routine, NULL) != 0)
        return (EXIT_FAILURE);
    if (pthread_join(t1, NULL) != 0) // Waits for the thread
        return (EXIT_FAILURE);
    if (pthread_join(t2, NULL) != 0) // Waits for the thread
        return (EXIT_FAILURE);
    return (0);
}