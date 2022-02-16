#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <fcntl.h>   
#include <semaphore.h>
#define SHARE_SIZE 128

int main()
{
    int j;
    int pid;
    int id;
    char curr;
    /* Shared memory variables. */
    int shmid;
    key_t memKey, semKey;
    char *buffer;
    sem_t *mutex;
    sem_t *empty;
    sem_t *full;
    mutex = sem_open("mutex", O_CREAT | O_EXCL, 0644, 1);
    empty = sem_open("empty", O_CREAT | O_EXCL, 0644, SHARE_SIZE);
    full = sem_open("full", O_CREAT | O_EXCL, 0644, 0);
    semKey = 456;
    memKey = 101;

    printf("Hey there! \n");
    pid = fork();
    if(pid == -1)
    {
        printf("Error: fork() failed. \n");
    }

    // Producer
    else if (pid == 0) 
    {
        /* Lets the user know that the child program is running*/
        printf("child \n");
        /* Create a piece of shared memory. */
        if ((shmid = shmget(memKey, SHARE_SIZE, IPC_CREAT|0666)) == -1) 
        {
            printf("Child: Error allocating shared memory \n");
            exit(shmid);
        }
        /* Attach to the memory. */
        if ((buffer = shmat(shmid, NULL, 0)) == (char *)-1) 
        {
            printf("Child: Could not attach to shared memory.\n");
            exit(-1);
        }
        /* Initialize the buffer. */
        for(j=0;j<SHARE_SIZE;j++) 
        {
            buffer[j] = 0;
        }
        /* Load the buffer. */
        for(int x = 0; x < 5; x++)
        {
            curr = 'a';
            for(j=0;j<26;j++) 
            {
                sem_wait(empty);
                sem_wait(mutex);
                buffer[j] = curr;
                curr++;
                sleep(1);
                sem_post(full);
                sem_post(mutex);
                

            }
        }

    }
    else
    {
        /* Lets the user know that the parent function is running*/
        printf("parent \n");
        /* Create a piece of shared memory. */
        if ((shmid = shmget(memKey, SHARE_SIZE, IPC_CREAT|0666)) == -1) 
        {
            printf("Parent: Error allocating shared memory \n");
            exit(shmid);
        }
        /* Attach to the memory. */
        if ((buffer = shmat(shmid, NULL, 0)) == (char *)-1) 
        {
            printf("Parent: Could not attach to shared memory.\n");
            exit(-1);
        }

        for(j=0;j<26;j++) 
        {
            sem_wait(full);
            sem_wait(mutex);
            printf("%c  ", buffer[j]);
            sleep(3);
            sem_post(mutex);
            sem_post(empty);
        }


    }   
    sem_unlink("mutex");
    sem_unlink("empty");
    sem_unlink("full");
    sem_close(mutex);
    sem_close(empty);
    sem_close(full);
    return 0;
}
