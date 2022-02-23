/*
Name: JT Fleetwood
Email: jfleetw@clemson.edu
Course: CPSC 3220-001
Assignment: HW 1
*/

// Including appropriate libraries.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Main function to calculate perimeter.
int main(int argc, char* argv[]) {
    // Calculating perimeter below.
    int result = 2*(atoi(argv[1]) + atoi(argv[2]));

    // Printing results.
    fprintf(stdout, "Child 2: pid %d, ppid %d, perimeter is %d\n\n", 
            getpid(), getppid(), result);

    return 0;
}