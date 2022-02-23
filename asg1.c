/*
Name: JT Fleetwood
Email: jfleetw@clemson.edu
Course: CPSC 3220-001
Assignment: HW 1
*/

// Including appropriate libraries below.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

// Struct definition as described in assignment write-up.
typedef struct dStore {
    int num1;
    int num2;
    char message[50];
} dStore;

// Helper function to check number of command-line arguments.
bool checkCLA(int count) {

    return (count == 4);
}

// Helper function to calculate ratio of num1 to num2.
void* calcRatio(void* data) {
    // Allocating for value to be returned out of thread.
    double *ratio = (double*)malloc(sizeof(double));
    
    // Calculating ratio below using appropriate casting.
    *ratio = (double)((dStore*)data)->num1 / (double)((dStore*)data)->num2;

    // Printing out as specified, to standard output.
    fprintf(stdout, "Thread 1: tig %ld, ratio is %.2lf\n", pthread_self(), 
            *ratio);

    // Exiting with ratio, passing back to parent.
    pthread_exit((void *)ratio);

}

// Helper function to reverse message.
void* reverseMessage(void* message) {
    // Allocating memory for value to be returned.
    char* revMessage = (char*)malloc(sizeof(char)*strlen(message));

    // Reversal below.
    for (int i = strlen((char*)message)-1; i >= 0; i--) {

        // Need appropriate type casting for below operation.
        revMessage[strlen((char*)message) - i - 1] = ((char*)message)[i];
    }

    // Printing and exiting with value to be returned to parent.
    fprintf(stdout, "Thread 2: tig %ld, message is \"%s\"\n", pthread_self(), 
            revMessage);

    pthread_exit((void *)revMessage);
}


int main(int argc, char* argv[]) {

    // If correct # of CLA's passed in, proceed with operations.
    if (checkCLA(argc)) {
        // dynamically allocating struct
        dStore *sharedDS = (dStore*)malloc(sizeof(dStore));

        // Initializing values of struct members.
        sharedDS->num1 = atoi(argv[1]);
        sharedDS->num2 = atoi(argv[2]);
        strcpy(sharedDS->message, argv[3]);

        // Creating first child process.
        int pid1 = fork();

        // If pid == 0, we know we are in the child process.
        if (pid1 == 0) {
            // Executing different routine with child process as specified.
            execl("./area", "area", argv[1], argv[2], NULL);

        }

        else {
            // Before proceeding with parent process, waiting for first child
            wait(NULL);

            // Creating second child process.
            int pid2 = fork();

            // If in second child, execute different routine.
            if (pid2 == 0) {
                execl("./perimeter", "perimeter", argv[1], argv[2], NULL);

            }

            else {
                // Wait for second child to complete before parallel processing.
                wait(NULL);
                pthread_t thread1ID;
                pthread_t thread2ID;

                // Creating first thread to concurrently run calcRatio().
                int t1Status = pthread_create(&thread1ID, NULL, &calcRatio, 
                                (void *)sharedDS);

                // If thread was not created successfully, exiting..
                if (t1Status != 0) {
                    fprintf(stdout, "Thread 1 not succesfully created..");
                    fprintf(stdout, " Exiting...\n");
                    exit(-1);
                }
                
                // Declaring value to be returned from first thread execution.
                double* ratio;

                // Creating second thread to run reverseMessage().
                int t2Status = pthread_create(&thread2ID, NULL, &reverseMessage, 
                                (void *)sharedDS->message);

                if (t2Status != 0) {
                    fprintf(stdout, "Thread 2 not succesfully created..");
                    fprintf(stdout, " Exiting...\n");
                    exit(-1);
                }

                // Value to be returned from second thread.
                char* revMessage;

                // Joining both threads and returning specified values.
                pthread_join(thread1ID, (void**)&ratio);
                pthread_join(thread2ID, (void**)&revMessage);

                // Printing out results in parent process.
                fprintf(stdout, "\nParent: pid %d,", getpid());
                fprintf(stdout, "ratio: %.2lf, message: \"%s\"\n", 
                        *ratio, revMessage);

                // Freeing memory associated with dynamic allocation.
                free(ratio);
                free(revMessage);
            }

        }
        
        // Freeing this separately because in separate control branch.
        free(sharedDS);
    }

    // If incorrect # of CLA's, exiting with error (-1).
    else {
        fprintf(stdout, "Incorrect # of CLAs provided.\nNeeded: 4, Provided: ");
        fprintf(stdout, "%d\n", argc);
        exit(-1);
    }

    return 0;

}