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
            exit(EXIT_SUCCESS);
    }
    return 0;
}
