#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#define size 10 

struct roundtable {
    int places[size]; 
};

void printCircle(struct roundtable r1); 
void algorithm(int left, int center,int right);
void* p0f(void*);
void* p1f(void*);
void* p2f(void*);
void* p3f(void*);
void* p4f(void*);

sem_t forkaccess;
struct roundtable table;
//just for printing

void* p0f(void*) {
    sem_wait(&forkaccess);
    algorithm(9,0,1);
    sem_post(&forkaccess);
};
void* p1f(void*) {
    sem_wait(&forkaccess);
    algorithm(1,2,3);
    sem_post(&forkaccess);
};
void* p2f(void*) {
    sem_wait(&forkaccess);
    algorithm(3,4,5);
    sem_post(&forkaccess);
};
void* p3f(void*) {
    sem_wait(&forkaccess);
    algorithm(5,6,7);
    sem_post(&forkaccess);
};
void* p4f(void*) {
    sem_wait(&forkaccess);
    algorithm(7,8,9);
};

int main() {
    // here 0s represent diners and 1 represents the forks
    // in order for a philo to be done dining they require 2 forks
    pthread_t p1,p2,p3,p4,p0;
    for(int i = 0; i<size; i++) { 
        if(i%2 == 0) table.places[i] = 0;
        else table.places[i] = 1;
    }
    printCircle(table); 
    sem_init(&forkaccess,0,1);

    pthread_create(&p0, NULL, p0f, NULL);
    pthread_create(&p1, NULL, p1f, NULL);
    pthread_create(&p2, NULL, p2f, NULL);
    pthread_create(&p3, NULL, p3f, NULL);
    pthread_create(&p4, NULL, p4f, NULL);

    pthread_join(p0, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    
    printf("all philosophers done eating\n");
    printCircle(table);
    return 0;
}

void printCircle(struct roundtable r1) {
    printf("        p0.%d\n"
            "     %d        %d\n"
            "p4.%d           p1.%d\n"
            "   %d          %d\n"
            "    p3.%d   p2.%d\n"
            "         %d\n",
         r1.places[0],
         r1.places[9], r1.places[1],
         r1.places[8], r1.places[2],
         r1.places[7], r1.places[3],
         r1.places[6], r1.places[4],
         r1.places[5]
            );
}

void algorithm(int left, int center,int right) {
    printf("\n philosopher %d eating\n", center/2);
   table.places[left]--;
   table.places[right]--;
   table.places[center]+=2;
   printCircle(table);
   table.places[center]-=2;
   table.places[left]++;
   table.places[right]++;
};
