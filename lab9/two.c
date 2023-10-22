#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_PHILOSOPHERS 5
#define EATING 0
#define THINKING 1
#define HUNGRY 2

int semid;
int total_eat_count = 0;

void grab_forks(int philosopher_id) {
    struct sembuf sop[2];

    sop[0].sem_num = philosopher_id;
    sop[0].sem_op = -1;
    sop[0].sem_flg = 0;

    sop[1].sem_num = (philosopher_id + 1) % NUM_PHILOSOPHERS;
    sop[1].sem_op = -1;
    sop[1].sem_flg = 0;

    semop(semid, sop, 2);
}

void put_away_forks(int philosopher_id) {
    struct sembuf sop[2];

    sop[0].sem_num = philosopher_id;
    sop[0].sem_op = 1;
    sop[0].sem_flg = 0;

    sop[1].sem_num = (philosopher_id + 1) % NUM_PHILOSOPHERS;
    sop[1].sem_op = 1;
    sop[1].sem_flg = 0;

    semop(semid, sop, 2);
}

void* philosopher(void* arg) {
    int philosopher_id = *((int*)arg);
    while (total_eat_count < NUM_PHILOSOPHERS) {
        // Thinking
        printf("Philosopher %d is thinking.\n", philosopher_id);
        sleep(1);

        // Hungry and trying to eat
        grab_forks(philosopher_id);
        printf("Philosopher %d is hungry and grabbing forks.\n", philosopher_id);

        // Eating
        printf("Philosopher %d is eating.\n", philosopher_id);
        sleep(1);

        // Done eating, put away forks
        put_away_forks(philosopher_id);
        printf("Philosopher %d is done eating and putting away forks.\n", philosopher_id);
    }
}

int main() {
    int philosopher_ids[NUM_PHILOSOPHERS];
    pthread_t philosophers[NUM_PHILOSOPHERS];

    // Create a semaphore set with one semaphore per philosopher
    semid = semget(IPC_PRIVATE, NUM_PHILOSOPHERS, IPC_CREAT | 0666);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        semctl(semid, i, SETVAL, 1); // Initialize semaphores to 1 (available)
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Cleanup the semaphore set
    semctl(semid, 0, IPC_RMID);

    return 0;
}

