#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/**
 * PRACTICAL EXAMPLE
*/

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void    *routine(void *param) {
    int init_index;
    int *sum;

    if (param == NULL) {
        return (NULL);
    }
    sum = (int *) malloc(sizeof(int));
    if (sum == NULL) {
        return (NULL);
    }
    init_index = *((int *) param);
    *sum = 0;
    for (int i = 0; i < 5; i++) {
        *sum += primes[init_index + i];
    }
    free(param);
    return (sum);
}

int main(int argc, char ** argv) {
    
    pthread_t   th[2];
    int         i;
    int         *i_cpy;
    int         *sums[2];
    int         sum;

    for (i = 0; i < 2; i++) {
        i_cpy = (int *) malloc(sizeof(int));
        if (i_cpy == NULL) {
            return (EXIT_FAILURE);
        }
        *i_cpy = i * 5;
        if (pthread_create(th + i, NULL, routine, i_cpy) != 0) {}
    }
    for (i = 0; i < 2; i++) {
        pthread_join(th[i], (void **)(sums + i));
    }
    if (sums[0] == NULL || sums[1] == NULL) {
        free(sums[0]);
        free(sums[1]);
        perror("Error calculating the sums...\n");
        return (EXIT_FAILURE);
    }
    sum = *(sums[0]) + *(sums[1]);
    free(sums[0]);
    free(sums[1]);
    printf("SUM: %d\n", sum);
    return (0);
}