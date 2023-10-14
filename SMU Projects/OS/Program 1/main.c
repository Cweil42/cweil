#include <stdio.h>
#include "pthread.h"
#include <stdlib.h>
#include <stdbool.h>

bool* P; // Array of primes
void *runner(void *param); /* the thread */
int size;

int main(int argc, char* argv[]) {
    // Read from command line
    size = atoi(argv[1]);
    int numThreads = atoi(argv[2]);

    pthread_t tid[numThreads]; /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */

    /* get the default attributes */
    pthread_attr_init(&attr);

    // Allocate the array and set all to true
    P = calloc(size, sizeof(bool));
    for(int i = 2; i < size; i++) {
        P[i] = true;
    }

    // Loop through all the values to check if true
    for(int i = 2; i < size; i+=numThreads){
        /* create the thread */
        for (int j = 0; j < numThreads && j+i < size; j++){
            int *x = (int *)malloc(sizeof(int));
            *x = i+j;
            pthread_create(&(tid[j]),&attr,runner, (void *) x);
            printf("Parent: Created thread with ID: %d\n", tid[j]);
        }

        /* now wait for the thread to exit */
        for (int j = 0; j < numThreads; j++){
//            printf("Parent: Joined thread %d\n", tid[j]);
            pthread_join(tid[j],NULL);
        }
    }

    // Print all primes values that = true
    for(int i = 2; i < size; i++)
        if(P[i]==true)
            printf("%d\n", i);

    return 0;
}

// Runner function that turns multiples of param to false
void *runner(void *param)
{
    int  q =  *((int *) param);
    // Set all P[x] to false where x is a multiple of q
    if(P[q] == 1){
        for(int i = q*2; i < size; i+=q){
            P[i] = false;
        }
    }
    pthread_exit(0);
}
