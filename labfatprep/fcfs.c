#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
int main() {
    int processTimes[] = {8,1,4,5,3}; 
    int numofprocesses = sizeof(processTimes)/sizeof(processTimes[0]);
    for(int i=0; i<numofprocesses; i++) {
        pid_t pid=fork();
        int status;
        switch(pid){
            case -1:
                perror("fork error");
                break;
            case 0:
                sleep(processTimes[i]);
                printf("child %i with pid %d and parent %d\n",i ,getpid(), getppid());
                exit(0);
                break;
            default:
                waitpid(pid,NULL,NULL);
                break;
        }
    }
    return 0;
}
