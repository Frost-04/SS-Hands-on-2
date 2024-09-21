/*
============================================================================
Name : 26.c
Author : Gaurav Verma
Description : Write a program to send messages to the message queue. Check $ipcs -q

Date: 19th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

typedef struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} mesg_buffer;

int main() {
    mesg_buffer message;
    
    // Generate a unique key
    key_t key = ftok(".", 1);
    
    // Check if key generation was successful
    if (key == -1) {
        perror("ftok failed");
        return 1;
    }

    // Get message queue ID
    int msgid = msgget(key, 0666 | IPC_CREAT);
    
    // Check if message queue creation was successful
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    // Prepare the message
    printf("Enter message type: ");
    scanf("%ld", &message.mesg_type);
    getchar(); // To clear newline after scanf

    printf("Enter message text: ");
    fgets(message.mesg_text, sizeof(message.mesg_text), stdin);

    // Send the message to the message queue
    if (msgsnd(msgid, &message, sizeof(message.mesg_text), 0) == -1) {
        perror("msgsnd failed");
        return 1;
    }

    printf("Message sent to queue successfully!\n");

    return 0;
}
