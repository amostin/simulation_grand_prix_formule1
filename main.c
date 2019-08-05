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
        {   .id = 44, .bestour = -1    },
        {   .id = 77, .bestour = -1    },
        {   .id = 5 , .bestour = -1    },
        {   .id = 7 , .bestour = -1    },
        {   .id = 3 , .bestour = -1    },
        {   .id = 33 , .bestour = -1   },
        {   .id = 11  , .bestour = -1  },
        {   .id = 31  , .bestour = -1  },
        {   .id = 18  , .bestour = -1  },
        {   .id = 35  , .bestour = -1  },
        {   .id = 27  , .bestour = -1  },
        {   .id = 55  , .bestour = -1  },
        {   .id = 10  , .bestour = -1  },
        {   .id = 28  , .bestour = -1  },
        {   .id = 8 , .bestour = -1    },
        {   .id = 20 , .bestour = -1   },
        {   .id = 2  , .bestour = -1   },
        {   .id = 14  , .bestour = -1  },
        {   .id = 9  , .bestour = -1   },
        {   .id = 16  , .bestour = -1  },
};

int compare_qualification(const void * a, const void * b)
{
    voiture *voitureA = (voiture *)a;
    voiture *voitureB = (voiture *)b;

    return (voitureA->id - voitureB->id);
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

        voiture temp = rem(b);
        for (int i =0; i< nbrVoiture; i++)
        {
            if ( sorter[i].id == temp.id)
            {
                if (sorter[i].bestour == -1)
                {
                    sorter[i] = temp;

                }
            }
        }
        qsort(sorter, 20, sizeof(voiture), compare_qualification);

        for (int i; i<nbrVoiture; i++)
        {
            printf("%d\t|", sorter[i].id);
            printf("%.3f\n", sorter[i].bestour);
        }
        //affichage(temp);


        /*if (i % 20 ==0 ) {
            sleep(1);
            system("clear");
            column();


        }*/


    }
    if (shmdt(b) == -1)
    {
        perror("shmdt");
        return -1;
    }
    return 0;
}