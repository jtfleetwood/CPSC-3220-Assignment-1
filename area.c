#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int main(int arc, char* argv[]) {
    int result = atoi(argv[1]) * atoi(argv[2]);

    fprintf(stdout, "\nChild 1: pid %d, ppid %d, area is %d\n", getpid(), getppid(), result);

    return 0;

}