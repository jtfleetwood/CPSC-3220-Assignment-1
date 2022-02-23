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

// Main function to calculate area.
int main(int arc, char* argv[]) {
    // Calculating area..
    int result = atoi(argv[1]) * atoi(argv[2]);

    // Printing results.
    fprintf(stdout, "\nChild 1: pid %d, ppid %d, area is %d\n", getpid(), 
            getppid(), result);

    return 0;

}