#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#define N 3
int main() {
    pid_t arr[N];
    for(int i = 0; i<N; i++) {
        pid_t pid = fork();
        arr[i] = pid;
       
        switch(pid) {
            case -1:
                perror("fork");
                exit(EXIT_FAILURE);
            case 0:
                printf("im %dth process", i);
                printf("child with pid %d\n", getpid());
                exit(0);
            default:
                printf("childs pid is %d\n", pid);
                break;
        }
        
    }
    for(int i = 0; i<N; i++) {
        printf("%d ", arr[i]);
    }

    wait(NULL);
    return 0;
}
