#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/**
 * PASSING ARGS TO THE THREADS
*/

void    *routine(void *param) {
    int prime;

    if (param == NULL) {
        return (NULL);
    }
    prime = *((int *) param);
    printf("Given prime: %d\n", prime);
    return (NULL);
}

int main(int argc, char ** argv) {
    int         primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    pthread_t   th[10];
    int         i;

    for (i = 0; i < 10; i++) {
        pthread_create(th + i, NULL, routine, primes + i);
    }
    for (i = 0; i < 10; i++) {
        pthread_join(th[i], NULL);
    }
    return (0);
}