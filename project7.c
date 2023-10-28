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

// buffer used by both produer and consumer
int buffer[10];
int produced, consumed; // producer and consumer values respectively
int bufferIndex;
sem_t empty, full; 
pthread_mutex_t mutex; 


// producer function *functionName is the syntax required for threads in pthread
void *producer(void *args) {
    int item = 0;
    // run infinite loop
    while(1) {
        sem_wait(&empty); // decrements the value of empty (if <= 0 -> block the thread)
        pthread_mutex_lock(&mutex); // lock it so that the consumer is not able to use it at the same time

        buffer[bufferIndex] = item; 
        printf("Produced %d", item);
        item++;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }

}

// consumer functions 
void *consumer(void *args) {

}

int main() {
    pthread_t producerThread, consumerThread; 

    sem_init(&empty, 0, 10);
    sem_inti(&full, 0, 10);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // destroy the created semaphores and mutex 
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0; 
}