// make all function start with mon
monenter() {
    sem_wait(&s);
}
monexit() {
    sem_post(&s);
}
moneat() etc lmao
