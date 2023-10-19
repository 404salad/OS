#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define N 5  // Number of philosophers
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define MAX_EAT_COUNT 1 // Number of times a philosopher eats before program ends

int *state;
int *eat_count;
int shmid;

void grab_forks(int phil_id) {
    state[phil_id] = HUNGRY;
    printf("Philosopher %d is hungry\n", phil_id);
    int left = (phil_id + N - 1) % N;
    int right = (phil_id + 1) % N;

    if (state[left] != EATING && state[right] != EATING) {
        state[phil_id] = EATING;
        printf("Philosopher %d is eating\n", phil_id);
    }
}

void put_forks(int phil_id) {
    state[phil_id] = THINKING;
    printf("Philosopher %d is thinking\n", phil_id);
    int left = (phil_id + N - 1) % N;
    int right = (phil_id + 1) % N;

    grab_forks(left);
    grab_forks(right);
    eat_count[phil_id]++;
}

void philosopher(int phil_id) {
    while (eat_count[phil_id] < MAX_EAT_COUNT) {
        printf("Philosopher %d is thinking\n", phil_id);
        sleep(1);  // Philosophers think for a while
        grab_forks(phil_id);
        sleep(1);  // Philosophers eat for a while
        put_forks(phil_id);
    }
}

int main() {
    // Create shared memory for philosopher states and eat count
    shmid = shmget(IPC_PRIVATE, N * sizeof(int) * 2, 0666 | IPC_CREAT);
    state = (int *)shmat(shmid, 0, 0);
    eat_count = state + N;

    for (int i = 0; i < N; i++) {
        state[i] = THINKING;
        eat_count[i] = 0;
    }

    for (int i = 0; i < N; i++) {
        if (fork() == 0) {
            philosopher(i);
            exit(0);
        }
    }

    // Wait for child processes to finish
    for (int i = 0; i < N; i++) {
        wait(NULL);
    }

    // Clean up shared memory
    shmdt(state);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

