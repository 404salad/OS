#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void userfunction() {
    fflush(stdout);
    printf("just a user function\n");
}
void* worker() {
    //calls a system call sleep
    userfunction();
    printf("This is thread1 id: %ld\n", pthread_self());
    sleep(1);
    pthread_exit(0);
}

void* worker2() {
    printf("This is thread2 id: %ld\n", pthread_self());
    sleep(2);
    pthread_exit(0);
}
int main() {
    pthread_t t1;

    int start = clock();
    if( pthread_create(&t1, NULL, worker, NULL ) != 0 ) {
        perror("cannot create thread\n");
        exit(1);
    }
    int end = clock();
    printf("time taken by thread 1 is %d\n", end - start);

    pthread_t t2;
    int start1 = clock();
    if( pthread_create(&t2, NULL, worker2, NULL) !=0) {
        perror("error creating thread 2");
        exit(1);
    }
    int end1 = clock();
    printf("time taken by thread 2 is %d\n", end1 - start1);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);    return 0;}
