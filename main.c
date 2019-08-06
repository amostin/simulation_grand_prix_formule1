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
const int nbrVoiture = 20;
const int nbrTour = 5;
int ID[20] = {44, 77, 5, 7, 3, 33, 11, 31, 18, 35, 27, 55, 10, 28, 8, 20, 2, 14, 9, 16};
voiture sorter[20] = {
        {   .id = 44  },
        {   .id = 77  },
        {   .id = 5   },
        {   .id = 7   },
        {   .id = 3   },
        {   .id = 33  },
        {   .id = 11  },
        {   .id = 31  },
        {   .id = 18  },
        {   .id = 35  },
        {   .id = 27  },
        {   .id = 55  },
        {   .id = 10  },
        {   .id = 28  },
        {   .id = 8   },
        {   .id = 20  },
        {   .id = 2   },
        {   .id = 14  },
        {   .id = 9   },
        {   .id = 16  },
};

int compare_qualification(const void * a, const void * b)
{
    voiture *voitureA = (voiture *)a;
    voiture *voitureB = (voiture *)b;

    return (voitureA->bestour - voitureB->bestour);
}


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


    pid_t pid;
    for (int i = 0; i < nbrVoiture; i++)
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

            for (int i = 0; i < nbrTour; i++)
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

    for (int i = 0; i < (nbrVoiture * nbrTour); i++)
    {
        usleep(1000);
        int cpt = 1;
        voiture temp = rem(b);
        for (int j =1; j< nbrVoiture; j++)
        {
            if (temp.id == sorter[j].id)
            {
                sorter[j] = temp;
            }
        }
        qsort(sorter, 20, sizeof(voiture), compare_qualification);

        if (i % 20 ==0 && i >= 20) {
            sleep(1);
            system("clear");
            column();
            affichage(sorter);
        }

    }

    if (shmdt(b) == -1)
    {
        perror("shmdt");
        return -1;
    }
    return 0;
}