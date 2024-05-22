#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>


/**
 * RETURN VALUE FROM A THREAD
 *  - notice that the pointer we pass to pthread_join() function is allocated
 *  by our roll_dice() function, which is not really good: we always prefer to
 *  allocate/deallocate within the same function in order to write clean code
 *  
 *  => We will prefer using the pthread_create function in order to pass
 *  ARGUMENTS to the roll_dice() function
*/

void    *roll_dice(void *param) {
    int *value;

    value = (int *) malloc(sizeof(int));
    *value = (rand() % 6) + 1;
    printf("Value: %d\n", *value);
    return ((void *) value);
}

int main(int argc, char **argv) {
    pthread_t   th[4];
    int         *res[4];
    int         i;

    srand(time(NULL));
    for (i = 0; i < 4; i++) {
        if (pthread_create(th + i, NULL, roll_dice, NULL) != 0) {
            return (EXIT_FAILURE);
        }
    }
    for (i = 0; i < 4; i++) {
        if (pthread_join(th[i], (void **) (res + i)) != 0) {
            return (EXIT_FAILURE);
        }
    }
    for (i = 0; i < 4; i++) {
        printf("Dice #%d: %d\n", i, *(res[i]));
    }
    for (i = 0; i < 4; i++) {
        free(res[i]);
    }
    return (0);
}