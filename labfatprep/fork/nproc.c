#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#define N 4
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
                //sleep(N-i);
                switch(i) { // 3 1 2 0
                    case 0: sleep(4); break;
                    case 1: sleep(2); break;
                    case 2: sleep(3); break;
                    case 3: sleep(1); break;
                }
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
        wait(NULL);
        //waitpid(arr[i], NULL, 0); // Wait for child processes in LIFO order
    }

    return 0;
}
