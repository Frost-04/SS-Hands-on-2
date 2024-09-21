/*
============================================================================
Name : 7.c
Author : Gaurav Verma
Description : Write a simple program to print the created thread ids.

Date: 17th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void* print()
{
    printf("Hello from thread :%lu\n", pthread_self());
    pthread_exit(NULL);
}

void main()
{
    pthread_t thread1, thread2, thread3;
    int pstatus;
    pstatus = pthread_create(&thread1, NULL, print, NULL);
    if (pstatus != 0)
    {
        perror("Error while creating thread");
        _exit(1);
    }

    pstatus = pthread_create(&thread2, NULL, print, NULL);
    if (pstatus != 0)
    {
        perror("Error while creating thread");
        _exit(1);
    }

    pstatus = pthread_create(&thread3, NULL, print, NULL);
    if (pstatus != 0)
    {
        perror("Error while creating thread");
        _exit(1);
    }

}