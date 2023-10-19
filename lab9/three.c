#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
int count = 0;
char buf[N];

void monenter() {
    pthread_mutex_lock(&mutex);
}

void monexit() {
    pthread_mutex_unlock(&mutex);
}

void moninsert(char alpha) {
    monenter();
    while (count == N) {
        printf("Buffer is full. Waiting...\n");
        pthread_cond_wait(&full, &mutex);
    }
    buf[(count++) % N] = alpha; // Insert alpha into buf, wrapping around when necessary
    printf("Produced: %c\n", alpha);
    if (count == 1) {
        pthread_cond_signal(&empty);
    }
    monexit();
}

char monremove() {
    monenter();
    while (count == 0) {
        printf("Buffer is empty. Waiting...\n");
        pthread_cond_wait(&empty, &mutex);
    }
    char item = buf[--count % N]; // Remove an item from buf, wrapping around when necessary
    printf("Consumed: %c\n", item);
    if (count == N - 1) {
        pthread_cond_signal(&full);
    }
    monexit();
    return item;
}

void* producer(void* arg) {
    while (1) {
        char item = 'A' + rand() % 26; // Produce a random uppercase letter
        moninsert(item);
    }
    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        char item = monremove();
    }
    return NULL;
}

int main() {
    pthread_t producer_threads[6];
    pthread_t consumer_threads[6];

    for (int i = 0; i < 6; i++) {
        pthread_create(&producer_threads[i], NULL, producer, NULL);
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < 6; i++) {
        pthread_join(producer_threads[i], NULL);
        pthread_join(consumer_threads[i], NULL);
    }

    return 0;
}

