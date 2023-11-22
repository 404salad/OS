int shared;
sem_t s1;

main() {
    sem_init(&s1,0,1);
}

void threadworker() {
    sem_wait(&s1);
    // do work
    sem_post(&s1);
}
