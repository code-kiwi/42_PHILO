#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/**
 * MUTEX
*/

int mails = 0;
pthread_mutex_t mutex;

void    *routine(void *param) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char **argv) {
    pthread_t   t1, t2, t3, t4;

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        return (EXIT_FAILURE);
    }
    if (pthread_create(&t1, NULL, routine, NULL) != 0) {
        return (EXIT_FAILURE);
    }
    if (pthread_create(&t2, NULL, routine, NULL) != 0) {
        return (EXIT_FAILURE);
    } 
    if (pthread_create(&t3, NULL, routine, NULL) != 0) {
        return (EXIT_FAILURE);
    } 
    if (pthread_create(&t4, NULL, routine, NULL) != 0) {
        return (EXIT_FAILURE);
    } 
    if (pthread_join(t1, NULL) != 0) { // Waits for the thread
        return (EXIT_FAILURE);
    }
    if (pthread_join(t2, NULL) != 0) { // Waits for the thread
        return (EXIT_FAILURE);
    }
    if (pthread_join(t3, NULL) != 0) { // Waits for the thread
        return (EXIT_FAILURE);
    }
    if (pthread_join(t4, NULL) != 0) { // Waits for the thread
        return (EXIT_FAILURE);
    }
    if (pthread_mutex_destroy(&mutex) != 0) {
        return (EXIT_FAILURE);
    }
    printf("Number of mails: %d\n", mails);
    return (0);
}