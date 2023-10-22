#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
//sem_t sync;
int main() {
    int ptc_pipe[2];
    int ctp_pipe[2];
    pid_t childpid;

    char* parentToChild = "loveptc";
    char* childToParent = "lovectp";
    char readbufferptc[20];
    char readbufferctp[20];
    ssize_t ptcbytes;
    ssize_t ctpbytes;

    if(pipe(ptc_pipe) == -1 || pipe(ctp_pipe) == -1) {
        perror("pipe");
        exit(1);
    }

    if((childpid = fork()) == -1) {
        perror("fork");
    }

    if(childpid == 0) {
        printf("child pid esta %d\n", getpid());
        
        //these will only be useful for parent
        close(ptc_pipe[1]); // close write end of ptc pipe
        close(ctp_pipe[0]); // close read end of ctp pipe 

        ptcbytes = read(ptc_pipe[0], readbufferptc, sizeof(readbufferptc));

        if(ptcbytes < 0) {
            perror("Read");
            exit(1);
        } else if (ptcbytes == 0)  {
            printf("No data recieved from parent. \n");
        } else {
            printf("Recieved string in child: %s\n", readbufferptc);
        }
        close(ptc_pipe[0]); // closed read end of ptc as already read
        write(ctp_pipe[1], childToParent, strlen(childToParent) + 1);
        close(ctp_pipe[1]);// close write

    }
    else {
        printf("parent pid esta %d\n", getpid());
        
        //these will only be useful for child
        close(ctp_pipe[1]); 
        close(ptc_pipe[0]); 

        write(ptc_pipe[1], parentToChild, strlen(parentToChild) + 1);
        close(ptc_pipe[1]);// close write

        ctpbytes = read(ctp_pipe[0], readbufferctp, sizeof(readbufferctp));
        if(ctpbytes < 0) {
            perror("Read");
            exit(1);
        } else if (ctpbytes == 0)  {
            printf("No data recieved from child. \n");
        } else {
            printf("Recieved string in parent: %s\n", readbufferctp);
        }
        close(ctp_pipe[0]); // closed read end of ptc as already read


        wait(NULL);
    }
    return 0;
}
