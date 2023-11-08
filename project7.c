/* 
Program: Produer-Consumer problem using semaphores
Description: 
    Let's do this: enter the numbers '0 1 2 3 4 5 6' in to the buffer and let the threads execute the operations
        When a producer is called, it should print produced '%d' when it enters the number in the buffer
        When a consumer is called, it should print consumed '%d' when it removes the number from the buffer

    pthread.h -> library used to shoe the working of program using threads
        mutex: used to ensure there is mutual exclusion and both producer and consumer get equal access to the buffer. 
        pthread_mutex_lock(&mutex): locks the mutex. If it is already locked, it will wait till it's unlocked and then lock it again.
        pthread_mutex_unlock(&mutex): unlocks the mutex so other processes can continue to execute. 

    semaphore.h -> define the sem_t type which is used for performing operations in the program
        sem_t s: defines a semaphore s. This is used to allow or block access to the shared resource 
        sem_t empty, full: empty and full slots in the buffer
        sem_wait(s): decrements the value of semaphore s and allows the thread to continue the execution of the program. 
                    //   If !(s >= 0), the thread is blocked till (s >= 0)
        sem_post(): increments the value of s and allows the thread that was blocked earlier to execute 

    block, wakeup, P, V all are handled by the functions stated above
Includes <pthread.h> and <semaphore.h>
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

// looping the program for 10 elements 
#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int produced = 0, consumed = 0; // no. of processes produced and consumed by producer and consumer
sem_t *empty, *full; // declare the semaphores used
pthread_mutex_t mutex; // declare the mutex used

void *producer(void *args) {
    // running the program for a set number of instructions 
    while (produced <= BUFFER_SIZE) {
        sem_wait(empty); // wait until the buffer is empty 
        pthread_mutex_lock(&mutex); // lock the mutex to ensure mutual exclusion 

        buffer[produced] = produced; // Assign sequential numbers to the buffer
        printf("Produced %d\n", buffer[produced]); 
        produced++; // increasing the number of items produced 

        pthread_mutex_unlock(&mutex); // unlock the mutex for further execution  
        sem_post(full); // indicate that the semaphore is full 
    }
    return NULL;
}

void *consumer(void *args) {
    // running the program for a set number of instructions 
    while (consumed <= BUFFER_SIZE) {
        sem_wait(full); // wait until the buffer is full
        pthread_mutex_lock(&mutex); // lock the mutex for mutual exclusion 

        int item = buffer[consumed]; // printing the numbers in the buffer array
        printf("Consumed %d\n", item);
        consumed++; // increasing the number of items consumed 

        pthread_mutex_unlock(&mutex); // unlock the mutex for further execution 
        sem_post(empty); // indicate that the buffer is empty 
    }
    return NULL;
}

int main() {
    pthread_t producerThread, consumerThread; // declaring the threads for both producer and consumer processes

    // initializing the semaphores
    empty = sem_open("/empty", O_CREAT, 0644, BUFFER_SIZE);
    full = sem_open("/full", O_CREAT, 0644, 0);

    pthread_mutex_init(&mutex, NULL); // initializing the mutex

    // initializing the threads 
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // joining the threads to ensure concurrency 
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // freeing the memory for semaphores
    sem_unlink("/empty");
    sem_unlink("/full");
    sem_close(empty);
    sem_close(full);

    // freeing the memory for mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}