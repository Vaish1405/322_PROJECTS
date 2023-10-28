#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// This program simulates producer-consumer problems using semaphores

// Let's do this: enter the numbers '0 1 2 3 4 5 6' in to the buffer and let the threads execute the operations
//      When a producer is called, it should print produced '%d' when it enters the number in the buffer
//      When a consumer is called, it should print consumed '%d' when it removes the number from the buffer

// pthread.h -> library used to shoe the working of program using threads
//      mutex: used to ensure there is mutual exclusion and both producer and consumer get equal access to the buffer. 
//      pthread_mutex_lock(&mutex): locks the mutex. If it is already locked, it will wait till it's unlocked and then lock it again.
//      pthread_mutex_unlock(&mutex): unlocks the mutex so other processes can continue to execute. 

// semaphore.h -> define the sem_t type which is used for performing operations in the program
//      sem_t s: defines a semaphore s. This is used to allow or block access to the shared resource 
//      sem_t empty, full: empty and full slots in the buffer
//      sem_wait(s): decrements the value of semaphore s and allows the thread to continue the execution of the program. 
                //   If !(s >= 0), the thread is blocked till (s >= 0)
//      sem_post(): increments the value of s and allows the thread that was blocked earlier to execute 

void functionToRunByThreads() {

}

void P(Semaphore s) {

}

void V(Semaphore s) {

}

void block(p) {

}

void wakeup(p) {

}


int main() {

    return 0; 
}