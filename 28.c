/*
============================================================================
Name : 28.c
Author : Gaurav Verma
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure).

Date: 20th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdlib.h>

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

    struct msqid_ds buf;

    // Get current permissions
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl failed");
        return 1;
    }

    printf("Current permissions: %o\n", buf.msg_perm.mode);

    // Change the permissions
    buf.msg_perm.mode = 0664; // New permissions

    // Set the new permissions
    if (msgctl(msgid, IPC_SET, &buf) == -1) {
        perror("msgctl IPC_SET failed");
        return 1;
    }

    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl failed");
        return 1;
    }
    printf("Updated permissions: %o\n", buf.msg_perm.mode);

    return 0;
}
