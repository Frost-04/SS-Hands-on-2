/*
============================================================================
Name : 25.c
Author : Gaurav Verma
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
              a. access permission
              b. uid, gid
              c. time of last message sent and received
              d. time of last change in the message queue
              d. size of the queue
              f. number of messages in the queue
              g. maximum number of bytes allowed
              h. pid of the msgsnd and msgrcv

Date: 19th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main() {
    // Generate unique key
    key_t key = ftok(".", 1);
    if (key == -1) {
        perror("ftok failed");
        return 1;
    }

    // Get message queue ID
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    // Structure to hold message queue data
    struct msqid_ds buf;

    // Get message queue details
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl failed");
        return 1;
    }

    printf("Access permissions: %o\n", buf.msg_perm.mode);

    printf("UID: %d\n", buf.msg_perm.uid);

    printf("GID: %d\n", buf.msg_perm.gid);

    printf("Last message sent: %s", ctime(&(buf.msg_stime)));

    printf("Last message received: %s", ctime(&(buf.msg_rtime)));

    printf("Last change: %s", ctime(&(buf.msg_ctime)));

    printf("Current size of queue: %lu bytes\n", buf.__msg_cbytes);

    printf("Number of messages in queue: %lu\n", buf.msg_qnum);

    printf("Max bytes allowed in queue: %lu\n", buf.msg_qbytes);

    printf("PID of last msgsnd: %d\n", buf.msg_lspid);

    printf("PID of last msgrcv: %d\n", buf.msg_lrpid);

    return 0;
}
