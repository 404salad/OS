#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_PHILOSOPHERS 5
#define MAX_EAT_COUNT 1

pthread_mutex_t forks[NUM_PHILOSOPHERS];
int eat_count[NUM_PHILOSOPHERS] = {0};

void monpickup(int philosopher_id) {
    pthread_mutex_lock(&forks[philosopher_id]);
    pthread_mutex_lock(&forks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);
}

void monputdown(int philosopher_id) {
    pthread_mutex_unlock(&forks[philosopher_id]);
    pthread_mutex_unlock(&forks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);
}

void* philosopher(void* arg) {
    int philosopher_id = *(int*)arg;
    while (eat_count[philosopher_id] < MAX_EAT_COUNT) {
        // Think
        printf("Philosopher %d is thinking.\n", philosopher_id);
        // Pick up forks
        monpickup(philosopher_id);
        // Eat
        printf("Philosopher %d is eating.\n", philosopher_id);
        eat_count[philosopher_id]++;
        // Put down forks
        monputdown(philosopher_id);
    }
    return NULL;
}

int main() {
    pthread_t philosopher_threads[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
        philosopher_ids[i] = i;
        pthread_create(&philosopher_threads[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosopher_threads[i], NULL);
    }

    return 0;
}

