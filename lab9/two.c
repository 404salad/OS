#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_PHILOSOPHERS 5
#define EATING 0
#define THINKING 1
#define HUNGRY 2

int state[NUM_PHILOSOPHERS];
sem_t mutex;
sem_t chopsticks[NUM_PHILOSOPHERS];
int total_eat_count = 0; // Total number of times all philosophers have eaten

void grab_forks(int philosopher_id) {
    sem_wait(&mutex);
    state[philosopher_id] = HUNGRY;
    printf("Philosopher %d is hungry.\n", philosopher_id);
    test(philosopher_id);
    sem_post(&mutex);
    sem_wait(&chopsticks[philosopher_id]);
}

void put_away_forks(int philosopher_id) {
    sem_wait(&mutex);
    state[philosopher_id] = THINKING;
    printf("Philosopher %d is thinking.\n", philosopher_id);
    test((philosopher_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS);
    test((philosopher_id + 1) % NUM_PHILOSOPHERS);
    sem_post(&mutex);
}

void test(int philosopher_id) {
    if (state[philosopher_id] == HUNGRY &&
        state[(philosopher_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS] != EATING &&
        state[(philosopher_id + 1) % NUM_PHILOSOPHERS] != EATING) {
        state[philosopher_id] = EATING;
        printf("Philosopher %d is eating.\n", philosopher_id);
        sem_post(&chopsticks[philosopher_id]);
        total_eat_count++;
    }
}

void* philosopher(void* arg) {
    int philosopher_id = *((int*)arg);
    while (total_eat_count < NUM_PHILOSOPHERS) {
        // Thinking
        sleep(1);

        // Hungry and trying to eat
        grab_forks(philosopher_id);

        // Eating
        sleep(1);

        // Done eating, put away forks
        put_away_forks(philosopher_id);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&chopsticks[i], 0, 0);
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}

