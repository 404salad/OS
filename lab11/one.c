#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

pid_t fork();
int main() {
    pid_t child = fork();

    if(child == 0 ) { // child 
       execlp("./lock.sh","./lock.sh",NULL);
       exit(0);
    }
    else if(child > 0) { // parent
       execlp("./lock.sh","./lock.sh",NULL);
       exit(0);
    }
    else {
        perror("fork error");
        exit(0);
    }
    wait(NULL);
    return 0;
}
