#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
        pid_t p1 = fork();
        switch(p1) {
            case -1:
                perror("fork");
                exit(EXIT_FAILURE);
            case 0:
                printf("child with pid %d\n", getpid());
                exit(EXIT_SUCCESS);
            default:
                puts("this is parent");
                printf("childs pid is %d\n", p1);
                break;
        }
        wait(NULL);
        pid_t p2 = fork();
        switch(p2) {
            case -1:
                perror("fork");
                exit(EXIT_FAILURE);
            case 0:
                printf("child with pid %d\n", getpid());
                exit(EXIT_SUCCESS);
            default:
                puts("this is parent");
                printf("childs pid is %d\n", p2);
                break;
        }
        
    return 0;
}
