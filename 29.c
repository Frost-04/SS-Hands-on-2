/*
============================================================================
Name : 29.c
Author : Gaurav Verma
Description : Write a program to remove the message queue.

Date: 20th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    // Generate a unique key for the message queue
    key_t key = ftok(".", 1);
    if (key == -1) {
        perror("ftok failed");
        return 1;
    }

    // Get the message queue ID
    int msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID failed");
        return 1;
    }

    printf("Message queue removed successfully.\n");

    return 0;
}
