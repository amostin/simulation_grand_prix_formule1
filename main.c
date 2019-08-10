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
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
/* Pour le utils */
#include "utils.h"
const int nbrVoiture = 20;
const int nbrTour = 25;
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






int run(int param, int shmid)
{
    buffer *b;
    b = (buffer *)shmat(shmid, NULL, 0);
    if (b == (void *)-1)
    {
        printf("error shmat\n");
        return 0;
    }
    init_buff(b);

    double tempsTotalQ = 18*60*1000;

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
                exit(EXIT_FAILURE);
            }
            if (param == 0) {
                for (int i = 0; i < nbrTour; i++)
                {
                    insert(b, &v, 0);
                    if (v.out == 1) {
                        break;
                    }
                    usleep(1000*1000);
                }
            } else if (param == 1) {
                while(!v.finished) {
                    insert(b, &v, tempsTotalQ);
                    if (v.out == 1) {
                        break;
                    }
                    usleep(1000*1000);
                }
            }

            if (shmdt(b) == -1)
            {
                perror("shmdt");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
    }


    if (param == 0) {
        for (int i = 0; i < (nbrTour); i++) {
            usleep(1000);
            for (int j = 0; j < nbrVoiture; j++) {
                voiture temp = rem(b);
                for (int k = 0; k < nbrVoiture; k++) {
                    if (temp.id == sorter[k].id) {
                        memcpy(&sorter[k], &temp, sizeof(voiture));
                    }
                }
            }
            qsort(sorter, 20, sizeof(voiture), compare_race);
            if (i != (nbrTour - 1)) {
                sleep(1);
                system("clear");
                column();
                affichage(sorter);
            } else {
                sleep(1);
                system("clear");
                column();
                affichage(sorter);
                sleep(1);
                podium(sorter);
            }
        }

    }
    else if (param == 1)
    {
        int finished = 0;
        while (!finished) {
            usleep(1000);
            for (int j = 0; j < nbrVoiture; j++) {
                voiture temp = rem(b);
                for (int k = 0; k < nbrVoiture; k++) {
                    if (temp.id == sorter[k].id) {
                        memcpy(&sorter[k], &temp, sizeof(voiture));
                    }
                }
            }
            int nbFinished = 0;
            for (int i = 0; i < nbrVoiture; i++) {
                if (sorter[i].finished) {
                    nbFinished++;
                }
            }
            qsort(sorter, nbrVoiture, sizeof(voiture), compare_qualification);
            if (nbFinished != nbrVoiture) {
                sleep(1);
                system("clear");
                column();
                affichage(sorter);
            } else
            {
                sleep(1);
                system("clear");
                column();
                affichage(sorter);
                sleep(1);
                grid(sorter);
                finished = 1;
            }
        }

    }



    if (shmdt(b) == -1)
    {
        perror("shmdt");
        return -1;
    }
    //return sorter;

    return 0;
}


int main(int argc, char  **argv) {
    //run(1);
    //sleep(10);
    if (argc < 2) {
        printf("Veuillez introduire le type de course\n");
        return 0;
    }
    key_t key = ftok("/dev/null", 42);
    int shmid = shmget(key, sizeof(buffer), IPC_CREAT | 0666);
    if (shmid == -1)
    {
        printf("error shmget\n");
        return 0;
    }
    run(atoi(argv[1]), shmid);
    sleep(2);
    buffer *b = shmat(shmid, NULL, 0);
    sem_reset(b->mutex, 0);
    semctl(b->mutex, 0, IPC_RMID, NULL);
    shmdt(b);
    shmctl(shmid, IPC_RMID, NULL);
}