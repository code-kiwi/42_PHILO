#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/**
 * Differences between threads and processes:
 *  - threads are "run" into the same process (one pid in our example)
 *  - in threads, all the variables are into the same address space: all the
 *  threads can access the same variables, while processes have encapsulated
 *  address spaces
 * 
 *  => all resources are shared by threads
 *  => leads to problems when accessing data
*/

int x = 2;

void    *routine(void *param) {
    x++;
    sleep(2);
    printf("Value of x: %d\n", x);
}

void    *routine2(void *param) {
    sleep(2);
    printf("Value of x: %d\n", x);
}

int main(int argc, char **argv) {
    pthread_t   t1, t2;

    if (pthread_create(&t1, NULL, routine, NULL) != 0) {
        return (EXIT_FAILURE);
    }
    if (pthread_create(&t2, NULL, routine2, NULL) != 0) {
        return (EXIT_FAILURE);
    }
    if (pthread_join(t1, NULL) != 0) {
        return (EXIT_FAILURE);
    }
    if (pthread_join(t2, NULL) != 0) {
        return (EXIT_FAILURE);
    }
    return (0);
}