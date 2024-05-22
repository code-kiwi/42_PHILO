#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char **argv) {
    pid_t   pid;
    int     x = 2;

    pid = fork();
    if (pid == -1) {
        return (EXIT_FAILURE);
    }
    if (pid == 0) {
        x++;
    }
    printf("Value of x: %d\n", x);
    printf("Process id: %d\n", getpid());
    if (pid != 0) {
        wait(NULL);
    }
    return (0);
}