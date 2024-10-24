/*
============================================================================
Name : 31.c
Author : Gaurav Verma
Description : Write a program to create a semaphore and initialize value to the semaphore.
               a. create a binary semaphore
               b. create a counting semaphore

Date: 20th Sept, 2024.
============================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

typedef union semun {
    int val;                   // Value for initializing semaphore
    struct semid_ds *buf;      // Data structure for semaphore info
    unsigned short int *array; // Array for GETALL, SETALL
} semun;

int main() {
    semun arg;
    key_t key;
    int semid;

    //Create binary semaphore
    key = ftok(".", 3);
    semid = semget(key, 1, IPC_CREAT | 0744);
    if (semid == -1) {
        perror("Failed to create binary semaphore");
        return 1;
    }

    arg.val = 1; // for binary semaphore
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("Failed to initialize binary semaphore");
        return 1;
    }
    printf("Binary semaphore created and initialized to %d\n", arg.val);

    //Create counting semaphore
    key = ftok(".", 4);
    semid = semget(key, 1, IPC_CREAT | 0744);
    if (semid == -1) {
        perror("Failed to create counting semaphore");
        return 1;
    }

    arg.val = 10; // for counting semaphore
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("Failed to initialize counting semaphore");
        return 1;
    }
    printf("Counting semaphore created and initialized to %d\n", arg.val);

    return 0;
}
