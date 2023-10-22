#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MESSAGE_SIZE 256

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_MESSAGE_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Generate a unique key for the message queue
    key = ftok("/tmp", 'A');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a message queue (the same key as the receiver)
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    while (1) {
        // Get user input
        printf("Enter message: ");
        fgets(message.msg_text, sizeof(message.msg_text), stdin);

        // Send the message
        message.msg_type = 1;
        if (msgsnd(msgid, &message, strlen(message.msg_text) + 1, 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }

    return 0;
}

