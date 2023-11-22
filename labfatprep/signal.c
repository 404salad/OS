#include <signal.h>

void siginthandler() {
    puts("sigint\n");
    exit(0);
}

int main() {
    signal(SIGINT,siginthandler);
    kill(pid,SIGHUP);
}
