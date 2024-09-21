/*
============================================================================
Name : 30a.c
Author : Gaurav Verma
Description : Write a program to create a shared memory.
              a. write some data to the shared memory
              b. attach with O_RDONLY and check whether you are able to overwrite.
              c. detach the shared memory
              d. remove the shared memory
Date: 20th Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of shared memory

int main() {
    // Step 1: Create shared memory
    key_t key = ftok(".", 1);
    if (key == -1) {
        perror("ftok failed");
        return 1;
    }

    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    // Step 2: Write data to the shared memory
    char *shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)(-1)) {
        perror("shmat failed");
        return 1;
    }

    // Write data
    const char *data = "Hello, Shared Memory!";
    strncpy(shm_ptr, data, SHM_SIZE);
    printf("Data written to shared memory: %s\n", shm_ptr);

    // Step 3: Detach the shared memory
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt failed");
        return 1;
    }

    // Step 4: Attach with O_RDONLY
    shm_ptr = shmat(shmid, NULL, SHM_RDONLY);
    if (shm_ptr == (char *)(-1)) {
        perror("shmat failed");
        return 1;
    }

    // Print the data (read-only)
    printf("Data read from shared memory: %s\n", shm_ptr);

    // Step 5: Detach the shared memory
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt failed");
        return 1;
    }

    // Step 6: Remove the shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID failed");
        return 1;
    }

    printf("Shared memory removed successfully.\n");

    return 0;
}
