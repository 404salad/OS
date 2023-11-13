#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
void* produceControl(void*);
void* consumerControl(void*);
void producer();
void consumer();
int current_index = 0;
int field[10] = {};
sem_t arraylock;
sem_t indexlock;
int main() {
    sem_init(&arraylock, 0, 1);
    sem_init(&indexlock, 0, 1);
    pthread_t consumer_thread, producer_thread;
    printf("initial array\n");
    for(int i = 0; i<10; i++) printf("%d ", field[i]);printf("\n");
    pthread_create(&producer_thread, NULL, produceControl, NULL);
    pthread_create(&consumer_thread, NULL, consumerControl, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    printf("final array values \n");
    for(int i = 0; i<10; i++) printf("%d ", field[i]);printf("\n");
}

void* produceControl(void*) {
    producer(); 
    producer(); 
    producer(); 
    producer(); 
}

void producer() {
    sem_wait(&arraylock);
    sem_wait(&indexlock);
    field[current_index++] = 1;
    printf("item produced\n");
    for(int i = 0; i<10; i++) printf("%d ", field[i]);printf("\n");
    sem_post(&arraylock);
    sem_post(&indexlock);
}

void* consumerControl(void*) {
    consumer();
    consumer();
}

void consumer() {
    sem_wait(&arraylock);
    sem_wait(&indexlock);
    field[--current_index] = 0;
    printf("item consumed nom nom\n");
    for(int i = 0; i<10; i++) printf("%d ", field[i]);printf("\n");
    sem_post(&arraylock);
    sem_post(&indexlock);
}
