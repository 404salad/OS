#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
 
void* f1();
void* f2();

int shared = 1;
sem_t s;

int main() {
    sem_init(&s,0,1);    
    pthread_t thread1,thread2;
    pthread_create(&thread1,NULL,f1,NULL);
    pthread_create(&thread2,NULL,f2,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    printf("Final value of shares is %d\n", shared);
}
void* f1() {
    int x;
    sem_wait(&s);
    x = shared;
    printf("Thread1 reads the value as %d\n", x);
    x++;
    printf("local updation by thread 1: %d\n", x);
    sleep(1);
    shared=x;
    printf("Value of shared variable updated by thread 1 is %d\n", shared);
    sem_post(&s);
}
void* f2() {
    int y;
    sem_wait(&s);
    y = shared; 
    printf("THread 2 reads the value of %d\n", y);
    y--;
    printf("local updation by thread2: %d\n", y);
    sleep(1);
    shared = y;
    printf("value of shared variable updated by thread2 is %d\n", shared);
    sem_post(&s);
}
