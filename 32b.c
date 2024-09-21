/*
============================================================================
Name : 32b.c
Author : Gaurav Verma
Description : Write a program to implement semaphore to protect any critical section.
              a. rewrite the ticket number creation program using semaphore
              b. protect shared memory from concurrent write access
              c. protect multiple pseudo resources ( may be two) using counting semaphore
              d. remove the created semaphore 
Date: 20th Sept, 2024.
============================================================================
*/

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>

typedef union semun {
    int val;               // Value of the semaphore
    struct semid_ds *buf;  // Buffer for IPC_STAT, IPC_SET
    unsigned short *array; // Array for GETALL, SETALL
} semun;

int main() {
    // Step 1: Create shared memory
    key_t shaKey = ftok(".", 666);
    int shmid = shmget(shaKey, 1024, IPC_CREAT | 0744);
    char *shmPointer = shmat(shmid, NULL, 0); // Attach shared memory

    // Step 2: Create semaphore
    key_t semKey = ftok(".", 332);
    int semIdentifier = semget(semKey, 1, IPC_CREAT | 0700);
    if (semIdentifier == -1) {
        perror("Error while creating semaphore!");
        return 1;
    }

    semun semSet;
    semSet.val = 1; // Set binary semaphore value
    if (semctl(semIdentifier, 0, SETVAL, semSet) == -1) {
        perror("Error while initializing semaphore!");
        return 1;
    }

    struct sembuf semOp;
    semOp.sem_num = 0;
    semOp.sem_flg = 0;

    printf("Entering to obtain lock on the critical section...\n");

    // Step 3: Lock the critical section
    semOp.sem_op = -1; // Wait operation
    if (semop(semIdentifier, &semOp, 1) == -1) {
        perror("Error while operating on semaphore!");
        return 1;
    }

    printf("Obtained lock on critical section!\n");
    printf("Now entering critical section!\n");

    // =========== Start of Critical Section ===========

    printf("Write to shared memory: ");
    scanf(" %[^\n]", shmPointer); // Read input into shared memory
    printf("Data from shared memory: %s\n", shmPointer);

    // =========== End of Critical Section =============

    printf("Exiting critical section...\n");

    // Step 4: Unlock the critical section
    semOp.sem_op = 1; // Signal operation
    if (semop(semIdentifier, &semOp, 1) == -1) {
        perror("Error while operating on semaphore!");
        return 1;
    }

    // Step 5: Clean up
    if (shmdt(shmPointer) == -1) {
        perror("Error detaching shared memory!");
    }
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("Error removing shared memory!");
    }
    if (semctl(semIdentifier, 0, IPC_RMID) == -1) {
        perror("Error removing semaphore!");
    }

    return 0;
}
