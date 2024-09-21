/*
============================================================================
Name : 6.c
Author : Gaurav Verma
Description : Write a simple program to create three threads

Date: 17th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void* print(void* thread_id)
{
    long tid = (long) thread_id; 
    printf("Hello from thread %ld\n", tid);
    pthread_exit(NULL);
}

void main()
{
    pthread_t thread1, thread2, thread3;
    int t;
    int pstatus;
    t=1;
    pstatus = pthread_create(&thread1, NULL, print, (void*) t);
    if (pstatus != 0)
    {
        perror("Error while creating thread");
        _exit(1);
    }

    t=2;
    pstatus = pthread_create(&thread2, NULL, print, (void*) t);
    if (pstatus != 0)
    {
        perror("Error while creating thread");
        _exit(1);
    }
    t=3;
    pstatus = pthread_create(&thread2, NULL, print, (void*) t);
    if (pstatus != 0)
    {
        perror("Error while creating thread");
        _exit(1);
    }

}