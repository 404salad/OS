#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define SEM_MUTEX_KEY "/tmp/sem-mutex-key"
#define SEM_BUFFER_COUNT_KEY "/tmp/sem-buffer-count-key"
#define SEM_SPOOL_SIGNAL_KEY "/tmp/sem-spool-signal-key"
#define MAX_BUFFERS 10

char buf[MAX_BUFFERS][100];
int buffer_index;
int buffer_print_index;
int mutex_sem, buffer_count_sem, spool_signal_sem;

void *producer(void *arg);
void *spooler(void *arg);

int main() {
    key_t s_key;
    union semun {
        int val;
        struct semid_ds *buf;
        ushort array[1];
    } sem_attr;
    pthread_t tid_producer[10], tid_spooler;
    int i, r;

    buffer_index = buffer_print_index = 0;

    if ((s_key = ftok(SEM_MUTEX_KEY, 'a')) == -1) {
        perror("ftok");
        exit(1);
    }
    if ((mutex_sem = semget(s_key, 1, 0660 | IPC_CREAT)) == -1) {
        perror("semget");
        exit(1);
    }
    sem_attr.val = 1;
    if (semctl(mutex_sem, 0, SETVAL, sem_attr) == -1) {
        perror("semctl SETVAL");
        exit(1);
    }

    if ((s_key = ftok(SEM_BUFFER_COUNT_KEY, 'a')) == -1) {
        perror("ftok");
        exit(1);
    }
    if ((buffer_count_sem = semget(s_key, 1, 0660 | IPC_CREAT)) == -1) {
        perror("semget");
        exit(1);
    }
    sem_attr.val = MAX_BUFFERS;
    if (semctl(buffer_count_sem, 0, SETVAL, sem_attr) == -1) {
        perror(" semctl SETVAL ");
        exit(1);
    }

    if ((s_key = ftok(SEM_SPOOL_SIGNAL_KEY, 'a')) == -1) {
        perror("ftok");
        exit(1);
    }
    if ((spool_signal_sem = semget(s_key, 1, 0660 | IPC_CREAT)) == -1) {
        perror("semget");
        exit(1);
    }
    sem_attr.val = 0;
    if (semctl(spool_signal_sem, 0, SETVAL, sem_attr) == -1) {
        perror(" semctl SETVAL ");
        exit(1);
    }

    if ((r = pthread_create(&tid_spooler, NULL, spooler, NULL)) != 0) {
        fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
        exit(1);
    }

    int thread_no[10];
    for (i = 0; i < 10; i++) {
        thread_no[i] = i;
        if ((r = pthread_create(&tid_producer[i], NULL, producer, (void *)&thread_no[i])) != 0) {
            fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
            exit(1);
        }
    }

    for (i = 0; i < 10; i++) {
        if ((r = pthread_join(tid_producer[i], NULL)) == -1) {
            fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
            exit(1);
        }
    }

    struct sembuf asem[1];
    asem[0].sem_num = 0;
    asem[0].sem_op = 0;
    asem[0].sem_flg = 0;
    if (semop(spool_signal_sem, asem, 1) == -1) {
        perror("semop: spool_signal_sem");
        exit(1);
    }

    if ((r = pthread_cancel(tid_spooler)) != 0) {
        fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
        exit(1);
    }

    if (semctl(mutex_sem, 0, IPC_RMID) == -1) {
        perror("semctl IPC_RMID");
        exit(1);
    }
    if (semctl(buffer_count_sem, 0, IPC_RMID) == -1) {
        perror("semctl IPC_RMID");
        exit(1);
    }
    if (semctl(spool_signal_sem, 0, IPC_RMID) == -1) {
        perror("semctl IPC_RMID");
        exit(1);
    }

    exit(0);
}

void *producer(void *arg) {
    int i;
    int my_id = *((int *)arg);
    struct sembuf asem[1];
    int count = 0;

    asem[0].sem_num = 0;
    asem[0].sem_op = 0;
    asem[0].sem_flg = 0;

    for (i = 0; i < 10; i++) {
        asem[0].sem_op = -1;
        if (semop(buffer_count_sem, asem, 1) == -1) {
            perror("semop: buffer_count_sem");
            exit(1);
        }

        asem[0].sem_op = -1;
        if (semop(mutex_sem, asem, 1) == -1) {
            perror("semop: mutex_sem");
            exit(1);
        }

        int j = buffer_index;
        buffer_index++;
        if (buffer_index == MAX_BUFFERS)
            buffer_index = 0;

        asem[0].sem_op = 1;
        if (semop(mutex_sem, asem, 1) == -1) {
            perror("semop: mutex_sem");
            exit(1);
        }

        sprintf(buf[j], "Thread %d: %d\n", my_id, ++count);
        asem[0].sem_op = 1;
        if (semop(spool_signal_sem, asem, 1) == -1) {
            perror("semop: spool_signal_sem");
            exit(1);
        }

        sleep(1);
    }
}

void *spooler(void *arg) {
    struct sembuf asem[1];

    asem[0].sem_num = 0;
    asem[0].sem_op = 0;
    asem[0].sem_flg = 0;

    while (1) {
        asem[0].sem_op = -1;
        if (semop(spool_signal_sem, asem, 1) == -1) {
            perror("semop: spool_signal_sem");
            exit(1);
        }

        printf("%s", buf[buffer_print_index]);

        buffer_print_index++;
        if (buffer_print_index == MAX_BUFFERS)
            buffer_print_index = 0;

        asem[0].sem_op = 1;
        if (semop(buffer_count_sem, asem, 1) == -1) {
            perror("semop: buffer_count_sem");
            exit(1);
        }
    }
}

