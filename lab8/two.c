// readers writers using shared memory
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>

int main() {
    pid_t p;
    p = fork();
    if (p < 0) {
        perror("fork fail");
        exit(1);
    } else if (p == 0) {
        // Child process
        int shmid;
        char *shared_memory;
        shmid = shmget((key_t)2345, 1024, 0666 | IPC_CREAT);
        if (shmid == -1) {
            perror("shmget failed");
            exit(1);
        }
        shared_memory = shmat(shmid, NULL, 0);
        printf("Waiting for data from the parent...\n");
        sleep(5); // Wait for the parent to write data
        printf("Data received from the parent: %s\n", shared_memory);
        printf("Enter data to share with the parent: ");scanf("%[^\n]s", shared_memory); 
    } else {
        // Parent process
        int shmid;
        char *shared_memory;
        shmid = shmget((key_t)2345, 1024, 0666);
        if (shmid == -1) {
            perror("shmget failed");
            exit(1);
        }
        shared_memory = shmat(shmid, NULL, 0);

        printf("Enter data to share with the child: ");scanf("%[^\n]s", shared_memory); 
        printf("Data written to shared memory: %s\n", shared_memory);
        sleep(10);
        printf("Data received from the child: %s\n", shared_memory);
    }

    return 0;
}


