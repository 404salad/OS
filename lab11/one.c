#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

pid_t fork();
int main() {
    pid_t child = fork();

    if(child == 0 ) { // child 
       execlp("cat","cat","file.txt",NULL);
       return 0;
    }
    else if(child > 0) { // parent
        return 0;
    }
    else {
        perror("fork error");
    }
    return 0;
}
