#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int produced = 0, consumed = 0;
sem_t *empty, *full;
pthread_mutex_t mutex;

void *producer(void *args) {
    while (produced <= BUFFER_SIZE) {
        sem_wait(empty);
        pthread_mutex_lock(&mutex);

        buffer[produced] = produced; // Assign sequential numbers to the buffer
        printf("Produced %d\n", buffer[produced]);
        produced++;

        pthread_mutex_unlock(&mutex);
        sem_post(full);
    }

    return NULL;
}

void *consumer(void *args) {
    while (consumed <= BUFFER_SIZE) {
        sem_wait(full);
        pthread_mutex_lock(&mutex);

        int item = buffer[consumed];
        printf("Consumed %d\n", item);
        consumed++;

        pthread_mutex_unlock(&mutex);
        sem_post(empty);
    }

    return NULL;
}

int main() {
    pthread_t producerThread, consumerThread;

    empty = sem_open("/empty", O_CREAT, 0644, BUFFER_SIZE);
    full = sem_open("/full", O_CREAT, 0644, 0);

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    sem_unlink("/empty");
    sem_unlink("/full");
    sem_close(empty);
    sem_close(full);

    pthread_mutex_destroy(&mutex);

    return 0;
}
