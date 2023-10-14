#include <stdio.h>
#include "pthread.h"
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

//// QUEUE IMPLEMENTATION FROM https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/
// A structure to represent a queue
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
// Takes size as parameter and creates the queue of the parameter size
struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(
            sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(
            queue->capacity * sizeof(int));
    return queue;
}

// Queue is full when size becomes
// equal to the capacity
// Takes queue as parameter and return if queue is full or not
int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
// Takes queue as parameter and return if queue is empty or not
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
// Takes queue and item as parameter and enqueues value passed by parameter
void enqueue(struct Queue* queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
//    printf("%d enqueued to queue\n", item);
}

// Function to remove an item from queue.
// It changes front and size
// Takes queue as parameter and dequeues front element and returns that value
int dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to get front of queue
// Takes queue as parameter and return front element of queue
int front(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}

// Function to get rear of queue
// Takes queue as parameter and return rear element of queue
int rear(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->rear];
}

// Function to print queue on one line
// Made myself (not gotten from internet source)
// Takes queue as parameter and prints the entire queue
void print(struct Queue* queue){
    if (isEmpty(queue)){
        printf("( )\n");
        return;
    }
    printf("( ");
    if(queue->front > queue->rear){
        for (int i = queue->front; i < queue->capacity; i++) {
            printf("%d ", queue->array[i]);
        }
        for (int i = 0; i < queue->rear; i++) {
            printf("%d ", queue->array[i]);
        }
    }
    else {
        for (int i = queue->front; i < queue->rear; i++) {
            printf("%d ", queue->array[i]);
        }
    }
    printf("%d )\n", queue->array[queue->rear]);
}

void *runner(void *param1); /* the thread */
int N; // num players on one table at once (threads)
int T; // Num of numbers
int p; // Total number of players
struct Queue* queue; // queue of numbers (dealer cards)
int* scores;
pthread_mutex_t mutex; // This mutex is used for when threads/ the dealer is accessing the queue
pthread_mutex_t playerFinishedMutex; // This mutex is used for when threads/ the a person has won 100+ points
char **playerNames;
char **playersPlaying;
int playersFinished;
int* threadActive;
int playerIsFinished;

int main(int argc, char* argv[]) {
    // Read from file
    FILE *fp;
    char buff[255];
    fp = fopen(argv[1], "r");
    fscanf(fp, "%s", buff);
    N = atoi(buff);
    fscanf(fp, "%s", buff);
    T = atoi(buff);
    fscanf(fp, "%s", buff);
    p = atoi(buff);

    // Read in player names to array of char**
    playerNames = (char*)malloc(p * sizeof(char*));
    for(int i = 0; i < p; i++){
        fscanf(fp, "%s", buff);
        playerNames[i] = (char*)malloc((strlen(buff+1)) * sizeof(char));
        strcpy(playerNames[i],buff);
    }
    fclose(fp);

    // Initialize queue and mutexes
    queue = createQueue(T);
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&playerFinishedMutex, NULL);

    // Set all starting scores to 0
    scores = calloc(N, sizeof(int));
    threadActive = calloc(N, sizeof(int));
    playersPlaying = malloc(N * sizeof(char*));
    for(int i = 0; i < N; i++) {
        scores[i] = 0;
        threadActive[i] = 1; // 1 is active - 0 id not active
        playersPlaying[i] = (char*)malloc((strlen(playerNames[i])+1) * sizeof(char));
        strcpy(playersPlaying[i], playerNames[i]);
    }

    // Create Threads
    pthread_t tid[N]; /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */
    pthread_attr_init(&attr); /* get the default attributes */
    playersFinished = 0;
    for (int j = 0; j < N; j++) {
        int *k = (int *)malloc(sizeof(int));
        *k = j;
        pthread_create(&(tid[j]),&attr,runner, (void *) k);
//        printf("Parent: Created thread with ID: %d\n", tid[j]);
    }

    //// Dealer starts adding cards
    /* Intializes random number generator */
    time_t t;
    srand((unsigned) time(&t));
    playerIsFinished = 0; // 0 means game is not over/ 1 means game is over
    printf("\n Game start!\n");
    do {
        while(playerIsFinished == 0){
            int x = rand() % (40) + 1; // Create random number
            while (queue->size > N) {
                if (playerIsFinished == 1)
                    break; // Wait until there are no more than N numbers unless a player finishes
            }
            if (playerIsFinished == 1)
                continue; // If player has finished then don't add card and handle player finishing

            pthread_mutex_lock(&mutex);
            /* Beginning of Critical Section */
            printf("\tThe dealer inserted : %d\n", x);
            enqueue(queue, x); // Fills queue with random numbers
            print(queue); // print queue after value added
            /* End of Critical Section */
            pthread_mutex_unlock(&mutex);
        }
        pthread_mutex_lock(&playerFinishedMutex);
        /* Beginning of Critical Section */
        for(int i = 0; i < N; i++){
            if(threadActive[i] == 0){
                playersFinished++;
                if((N + playersFinished) <= p){ // Players left in queue to enter
                    printf("%s scored %d points.\n%s left and %s joined.\n", playersPlaying[i], scores[i],
                           playersPlaying[i], playerNames[playersFinished+N-1]);
                    realloc(playersPlaying[i], (strlen(playerNames[N + playersFinished-1])+1) * sizeof(char));
                    strcpy(playersPlaying[i], playerNames[N + playersFinished-1]);
                    scores[i] = 0;
                }
                else{
                    printf("%s scored %d points.\nNo more players can join. Game is ending!\n",
                           playersPlaying[i], scores[i]);
                }
                threadActive[i] = 1;
            }
        }
        playerIsFinished = 0; // 0 means game is not over/ 1 means game is over
        /* End of Critical Section */
        pthread_mutex_unlock(&playerFinishedMutex);

    } while(playersFinished <= (p-N));

    /* now wait for the thread to exit */
    for (int j = 0; j < N; j++) {
        pthread_join(tid[j], NULL);
//        printf("Parent: Joined thread %d %d\n", tid[j], j);
    }

    return 0;
}

// Runner function that takes pointer to the thread number. Function acts as player playing game
// It will dequeue cards from the stack when it has the mutex lock and print the queue after
// It will then process cards scores and read cards to the stack if needed and print the queue after changes are made
// If the person is over 99 points then the thread will signal that someone has won and the mai program will handle the replacement
// When the replacement is complete then the thread will continue with a new person
void *runner(void *param)
{
    int k =  *((int *) param);
    while(isEmpty(queue))
        ;   // If dealer hasn't dealt before players made
    while(playersFinished <= (p-N)){
        int score = 0;
        int reinsert = 0;
        pthread_mutex_lock(&mutex);
        /* Beginning of Critical Section */
        if(isEmpty(queue)){
            pthread_mutex_unlock(&mutex);
            continue;
        }
        int x = dequeue(queue); // Get value from queue
        // Logic for scoring/ reinserting
        if(x <= N){
            printf("\tThread %d(%s) popped x = %d. Final bonus for object : no need to push back.\n", k, playersPlaying[k], x);
            score = x;
        }
        else if(x % N == k || x % N == (k+1) % N){
            printf("\tThread %d(%s) popped x = %d. Matched. Need to push 3/5 * x back on queue.\n", k, playersPlaying[k], x);
            score = 2*x/5;
            reinsert = x - (2*x/5);
        }
        else{
            printf("\tThread %d(%s) popped x = %d. Not matched. Need to push x - 2 back on queue.\n", k, playersPlaying[k], x);
            reinsert = x - 2;
        }
        print(queue);
        /* End of Critical Section */
        pthread_mutex_unlock(&mutex);

        struct timespec slptm = {1, (1000000 * (x))};
        nanosleep(&slptm, NULL); // sleep for 1 + x milliseconds after getting number

        pthread_mutex_lock(&mutex);
        /* Beginning of Critical Section */
        scores[k] += score;
        printf("\tThread %d(%s)  score : %d\ttotal : %d\n", k, playersPlaying[k], score, scores[k]);
        if(reinsert != 0){
            printf("\t\tThread %d(%s) pushed %d to the back of the queue.\n", k, playersPlaying[k], reinsert);
            enqueue(queue, reinsert); // Reinsert value if necessary
        }
        else{
            printf("\t\tNothing to push.\n");
        }
        print(queue);
        /* End of Critical Section */
        if(scores[k] >= 100) {
            threadActive[k] = 0;
            pthread_mutex_unlock(&mutex);
            pthread_mutex_lock(&playerFinishedMutex);
            /* Beginning of Critical Section */
            playerIsFinished = 1; // 0 means game is not over/ 1 means game is over
            /* End of Critical Section */
            pthread_mutex_unlock(&playerFinishedMutex);

            while (threadActive[k] == 0)
                ; // While thread has not been given new player, it waits before being able to score more
        }
        else{
            pthread_mutex_unlock(&mutex);
        }
    }

    pthread_exit(0);
}

