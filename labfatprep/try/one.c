#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void createProcesses(int level, int maxLevel);

int main() {
    int n;

    // Get the value of n
    printf("Enter the value of n: ");
    scanf("%d", &n);

    // Create processes
    createProcesses(1, n);

    return 0;
}

void createProcesses(int level, int maxLevel) {
    if (level > maxLevel) {
        // Base case: reached the maximum level
        printf("Process %d (pid %d) exiting\n", level - 1, getpid());
        exit(0);
    }

    pid_t pid;
    int i;

    for (i = 0; i < level; ++i) {
        pid = fork();

        if (pid == -1) {
            // Error handling
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            printf("Child process %d (pid %d) created\n", i + 1, getpid());
            createProcesses(level + 1, maxLevel);  // Recursive call for creating i child processes
            printf("Process %d exiting\n", getpid());
            exit(0);
        }
    }

    // Parent process
    for (i = 0; i < level; ++i) {
        // Wait for child processes to finish
        wait(NULL);
    }
}

