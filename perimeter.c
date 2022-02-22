#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int result = 2*(atoi(argv[1]) + atoi(argv[2]));
    fprintf(stdout, "Child 2: pid %d, ppid %d, perimeter is %d\n\n", getpid(), getppid(), result);

    return 0;
}