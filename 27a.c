/*
============================================================================
Name : 27a.c
Author : Gaurav Verma
Description : Write a program to receive messages from the message queue.
              a. with 0 as a flag
              b. with IPC_NOWAIT as a flag

Date: 19th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct mesg_buffer
{
    long mesg_type;
    char mesg_text[100];
} mesg_buffer;
int main()
{
    mesg_buffer message;
    // generate unique no
    key_t key = ftok(".", 1);

    int msgid = msgget(key, 0666 | IPC_CREAT);
    printf("enter msgtype:\n");
    scanf("%ld", &message.mesg_type);
    int size_s = msgrcv(msgid, &message, sizeof(message), message.mesg_type, 0); // 0 flag will wait for msg and give us warning if message of type is not in msg queue.
    if (size_s <= 0)
    {
        perror("No message in queue\n");
    }
    else
    {
        printf("Message: %s\n", message.mesg_text);
    }
    return 0;
}