#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

typedef struct dStore {
    int num1;
    int num2;
    char message[50];
} dStore;

bool checkCLA(int count) {

    return (count == 4);
}

void* calcRatio(void* data) {
    double *ratio = (double*)malloc(sizeof(double));
    
    *ratio = (double)((dStore*)data)->num1 / (double)((dStore*)data)->num2;
    printf("Thread 1: tig %ld, ratio is %.2lf\n", pthread_self(), *ratio);

    pthread_exit((void *)ratio);

}

void* reverseMessage(void* message) {
    char* revMessage = (char*)malloc(sizeof(char)*strlen(message));

    for (int i = strlen((char*)message)-1; i >= 0; i--) {
        
        revMessage[strlen((char*)message) - i - 1] = ((char*)message)[i];
    }

    printf("Thread 2: tig %ld, message is \"%s\"\n", pthread_self(), revMessage);

    pthread_exit((void *)revMessage);
}


int main(int argc, char* argv[]) {

    if (checkCLA(argc)) {
        dStore *sharedDS = (dStore*)malloc(sizeof(dStore));
        sharedDS->num1 = atoi(argv[1]);
        sharedDS->num2 = atoi(argv[2]);
        strcpy(sharedDS->message, argv[3]);

        int pid1 = fork();

        if (pid1 == 0) {
            execl("./area", "area", argv[1], argv[2], NULL);

        }

        else {
            wait(NULL);
            int pid2 = fork();

            if (pid2 == 0) {
                execl("./perimeter", "area", argv[1], argv[2], NULL);

            }

            else {
                wait(NULL);
                pthread_t thread1ID;
                pthread_t thread2ID;
        
                int t1Status = pthread_create(&thread1ID, NULL, &calcRatio, (void *)sharedDS);

                if (t1Status != 0) {
                    printf("Thread 1 not succesfully created..Exiting..\n");
                    exit(-1);
                }

                double* ratio;
                

        

                int t2Status = pthread_create(&thread2ID, NULL, &reverseMessage, (void *)sharedDS->message);

                if (t2Status != 0) {
                    printf("Thread 1 not succesfully created..Exiting..\n");
                    exit(-1);
                }

                char* revMessage;
                pthread_join(thread1ID, (void**)&ratio);
                pthread_join(thread2ID, (void**)&revMessage);

                printf("\nParent: pid %d, ratio: %.2lf, message: \"%s\"\n", getpid(), *ratio, revMessage);

                free(ratio);
                free(revMessage);
            }

        }

        free(sharedDS);
    }

    else {
        printf("Incorrect # of CLAs provided.\nNeeded: 4, Provided: %d\n", argc);
        exit(-1);
    }

    return 0;

}