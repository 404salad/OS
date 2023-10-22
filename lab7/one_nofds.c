#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    int fd[2];
    pid_t childpid;
    char* string = "nobara";
    char readbuffer[20]; // Define a buffer for reading data
    ssize_t nbytes;     // Use ssize_t for read/write return values
    if (pipe(fd) == -1) {
        perror("Pipe");
        exit(1);
    }
    
    if ((childpid = fork()) == -1) {
        perror("Fork");
        exit(1);
    }
    
    if (childpid == 0) {
    
        write(fd[1], string, strlen(string) + 1);
   
    } 
    else {
  
        nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
 
        
        if (nbytes < 0) {
            perror("Read");
            exit(1);
        } else if (nbytes == 0) {
            printf("No data received from child.\n");
        } else {
            printf("Received string: %s\n", readbuffer);
        }
    }
    
    return 0;
}

