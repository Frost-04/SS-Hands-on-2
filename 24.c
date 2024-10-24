/*
============================================================================
Name : 24.c
Author : Gaurav Verma
Description : Write a program to create a message queue and print the key and message queue id.

Date: 19th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} mesg_buffer;

int main() {
    mesg_buffer message;
    
    // Generate a unique key
    key_t key = ftok(".", 1);
    printf("Generated key: %d\n", key);

    int msgid = msgget(key, 0666 | IPC_CREAT);
    printf("Message queue ID: %d\n", msgid);

    return 0;
}
