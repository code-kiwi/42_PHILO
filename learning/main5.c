#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/**
 * LOOPING FOR CREATING THREADS
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
/**
 * NB: We could not create/join threads into the same loop because they
 * would not execute in parallel
 * Do not:
        for  (i = 0; i < 4; i++) {
            if (pthread_create(th + i, NULL, routine, NULL) != 0) {
                perror("Failed to create thread\n");
                return (EXIT_FAILURE);
            if (pthread_join(th[i], NULL) != 0) {
                perror("Failed to join thread\n");
                return (EXIT_FAILURE);
            }
        }
    Because it would not be multithreading
*/
int main(int argc, char **argv) {
    pthread_t   th[4];
    int         i;

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Failed to init mutex\n");
        return (EXIT_FAILURE);
    }
    for  (i = 0; i < 4; i++) {
        if (pthread_create(th + i, NULL, routine, NULL) != 0) {
            perror("Failed to create thread\n");
            return (EXIT_FAILURE);
        }
    }
    for (i = 0; i < 4; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread\n");
            return (EXIT_FAILURE);
        }
    }
    if (pthread_mutex_destroy(&mutex) != 0) {
        perror("Failed to destroy mutex\n");
        return (EXIT_FAILURE);
    }
    printf("Number of mails: %d\n", mails);
    return (0);
}