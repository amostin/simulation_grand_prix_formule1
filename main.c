#include <stdlib.h>
/* Pour fprintf() */
#include <stdio.h>
/* Pour fork() */
#include <unistd.h>
/* Pour le type pid_t */
#include <sys/types.h>
/* Pour le strcat() */
#include <string.h>
/* Pour les sémaphores */
#include <semaphore.h>
#include <sys/shm.h>
/* Pour le utils */
#include "utils.h"

int ID[20] = {44, 77, 5, 7, 3, 33, 11, 31, 18, 35, 27, 55, 10, 28, 8, 20, 2, 14, 9, 16};

int main()
{
    buffer *b;
    key_t key = 42;
    int shmid = shmget(key, sizeof(buffer), IPC_CREAT | 00777);
    if (shmid == -1)
    {
        printf("error shmget\n");
        return 0;
    }
    b = (buffer *)shmat(shmid, NULL, 0);
    if (b == (void *)-1)
    {
        printf("error shmat\n");
        return 0;
    }
    init_buff(b);

    column();
    pid_t pid;
    for (int i = 0; i < 20; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            srand(getpid());
            voiture v;
            init_voiture(&v, ID[i]);
            buffer *b = shmat(shmid, NULL, 0);
            if (b == (void *)-1)
            {
                printf("error shmat\n");
                return -1;
            }

            for (int i = 0; i < 50; i++)
            {
                insert(b, &v);
                usleep(200000);
            }
            if (shmdt(b) == -1)
            {
                perror("shmdt");
                return -1;
            }
            return 0;
        }
    }
    for (int i = 0; i < 1000; i++)
    {
        usleep(1000);
        voiture temp = rem(b);
        if (i % 20 ==0 ) {
            sleep(1);
            system("clear");
        }

        affichage(temp);
    }
    if (shmdt(b) == -1)
    {
        perror("shmdt");
        return -1;
    }
    return 0;
}