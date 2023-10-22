#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 3

int semid;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void produce(int item) {
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
}

int consume() {
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    return item;
}

void* producer(void* arg) {
    int producer_id = *((int*)arg);
    int item = 1;

    while (1) {
        // Produce item
        printf("Producer %d is producing item %d.\n", producer_id, item);
        produce(item);

        // Sleep for a random time
        sleep(1);

        item++;
    }
}

void* consumer(void* arg) {
    int consumer_id = *((int*)arg);

    while (1) {
        // Consume item
        int item = consume();
        printf("Consumer %d is consuming item %d.\n", consumer_id, item);

        // Sleep for a random time
        sleep(2);
    }
}

int main() {
    int producer_ids[NUM_PRODUCERS];
    int consumer_ids[NUM_CONSUMERS];
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    // Create a semaphore set with two semaphores (producer and consumer)
    semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    
    // Initialize producer semaphore to buffer size (5)
    semctl(semid, 0, SETVAL, BUFFER_SIZE);
    // Initialize consumer semaphore to 0 (no items to consume initially)
    semctl(semid, 1, SETVAL, 0);

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        producer_ids[i] = i;
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        consumer_ids[i] = i;
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Cleanup the semaphore set
    semctl(semid, 0, IPC_RMID);

    return 0;
}
