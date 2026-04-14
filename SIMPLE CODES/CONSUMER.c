#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define SIZE 5

int main()
{
    int shmid = shmget(1234, SIZE * sizeof(int), 0666);
    int *buffer = (int *)shmat(shmid, NULL, 0);

    int semid = semget(1234, 3, 0666);

    int out = 0, item;

    for(int i = 0; i < 10; i++)
    {
        // wait(full)
        semop(semid, &(struct sembuf){1, -1, 0}, 1);
        // wait(mutex)
        semop(semid, &(struct sembuf){2, -1, 0}, 1);

        item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % SIZE;

        // signal(mutex)
        semop(semid, &(struct sembuf){2, 1, 0}, 1);
        // signal(empty)
        semop(semid, &(struct sembuf){0, 1, 0}, 1);

        sleep(1);
    }
}