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
int ID[20] = {44, 77, 5, 7, 3, 33, 11, 31, 18, 35, 27, 55, 10, 28, 8, 20, 2, 14, 9, 16};
car sorter[20] = {
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

car sector_sorter[20] = {
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




int run(int param, int shmid, int nbrTour) {
    double tpsE1 = 90*60*1000;
    double tpsE2 = 90*60*1000;
    double tpsE3 = 60*60*1000;
    double tpsQ1 = 18*60*1000;
    double tpsQ2 = 15*60*1000;
    double tpsQ3 = 12*60*1000;
    buffer *b;
    b = (buffer *)shmat(shmid, NULL, 0);
    if (b == (void *)-1) {
        printf("error shmat\n");
        return 0;
    }
    init_buff(b);

    pid_t pid;
    for (int i = 0; i < nbrVoiture; i++) {
        if (param == 10) {
            int numV = ID[i];
            int outQualif = 0;
            for (int m = 0; m < nbrVoiture; m++) {
                if (sorter[m].id == numV) {
                    outQualif = sorter[m].out_qualif1;
                }
            }
            if (outQualif) {
                continue;
            }
        }
        if (param == 11) {
            int numV = ID[i];
            int outQualif = 0;
            for (int m = 0; m < nbrVoiture; m++) {
                if (sorter[m].id == numV) {
                    outQualif = sorter[m].out_qualif2;
                }
            }
            if (outQualif) {
                continue;
            }
        }
        pid = fork();
        if (pid == 0) {
            srand(getpid());
            car v;
            if (param == 4) {
                init_voiture(&v, sorter[i].id);
                usleep(sorter[i].pos_grid*100*1000);
            } else {
                init_voiture(&v, ID[i]);
            }

            buffer *b = shmat(shmid, NULL, 0);
            if (b == (void *)-1) {
                printf("error shmat\n");
                exit(EXIT_FAILURE);
            }
            if (param == 4) {
                for (int j = 0; j < nbrTour; j++)
                {
                    insert(b, &v, 0);
                    if (v.out == 1) {
                        break;
                    }
                    usleep(1000*1000);
                }
                v.finished = 1;
                sem_lock(b->mutex, 0);
                b->size++;
                b->tab[b->last] = v;
                b->last = (b->last + 1) % (b->maxsize);
                sem_unlock(b->mutex, 0);
            } else {
                double temps;
                switch (param){
                    case 0:
                        temps = tpsE1;
                        break;
                    case 1:
                        temps = tpsE2;
                        break;
                    case 2:
                        temps = tpsE3;
                        break;
                    case 3:
                        temps = tpsQ1;
                        break;
                    case 10:
                        temps = tpsQ2;
                        break;
                    case 11:
                        temps = tpsQ3;
                        break;
                    default:
                        return -1;
                }
                while(!v.finished) {
                    insert(b, &v, temps);
                    if (v.out == 1) {
                        break;
                    }
                    usleep(1000*1000);
                }
            }

            if (shmdt(b) == -1) {
                perror("shmdt");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
    }

    if (param == 4) {
        for(int i = 0; i < nbrVoiture; i++) {
            sorter[i].total = 0;
            sorter[i].finished = 0;
            sorter[i].num_lap = 0;
            sorter[i].out = 0;
            sorter[i].s1 = 0;
            sorter[i].s2 = 0;
            sorter[i].s3 = 0;
            sorter[i].best_s1 = 0;
            sorter[i].best_s2 = 0;
            sorter[i].best_s3 = 0;
            sorter[i].pit = 0;
            sorter[i].best_lap = 0;
        }
        int finished = 0;
        while (!finished) {
            usleep(1000);
            for (int j = 0; j < nbrVoiture; j++) {
                car temp = rem(b);
                for (int k = 0; k < nbrVoiture; k++) {
                    if (temp.id == sorter[k].id) {
                        memcpy(&sorter[k], &temp, sizeof(car));
                    }
                }
            }
            int nbFinished = 0;
            for (int i = 0; i < nbrVoiture; i++) {
                if (sorter[i].finished) {
                    nbFinished++;
                }
            }
            qsort(sorter, 20, sizeof(car), compare_race);
            if (nbFinished != nbrVoiture) {
                sleep(1);
                system("clear");
                printf("--------- Grand Prix ----------\n");
                column();
                display(sorter);
                printf("\n");
                display_best_sectors(sorter);
            } else {
                sleep(1);
                system("clear");
                printf("--------- Grand Prix ----------\n");
                column();
                display(sorter);
                printf("\n");
                display_best_sectors(sorter);
                sleep(1);
                podium(sorter);
                finished = 1;
            }
        }

    } else {
        char titre[100];
        switch(param) {
            case 0:
                for (int i = 0; i < nbrVoiture; i++) {
                    sorter[i].finished = 0;
                }
                sprintf(titre, "---- Essai 1 ----\n");
                break;
            case 1:
                for (int i = 0; i < nbrVoiture; i++) {
                    sorter[i].finished = 0;
                }
                sprintf(titre, "---- Essai 2 ----\n");
                break;
            case 2:
                for (int i = 0; i < nbrVoiture; i++) {
                    sorter[i].finished = 0;
                }
                sprintf(titre, "---- Essai 3 ----\n");
                break;
            case 3:
                for (int i = 0; i < nbrVoiture; i++) {
                    sorter[i].finished = 0;
                }
                sprintf(titre, "---- Qualification 1 ----\n");
                break;
            case 10:
                for (int i = 0; i < nbrVoiture; i++) {
                    if (!sorter[i].out_qualif1) {
                        sorter[i].finished = 0;
                    }
                }
                sprintf(titre, "---- Qualification 2 ----\n");
                break;
            case 11:
                for (int i = 0; i < nbrVoiture; i++) {
                    if (!sorter[i].out_qualif2) {
                        sorter[i].finished = 0;
                    }
                }
                sprintf(titre, "---- Qualification 3 ----\n");
                break;
        }
        int finished = 0;
        while (!finished) {
            usleep(1000);
            for (int j = 0; j < nbrVoiture; j++) {
                car temp = rem(b);
                for (int k = 0; k < nbrVoiture; k++) {
                    if (temp.id == sorter[k].id) {
                        memcpy(&sorter[k], &temp, sizeof(car));
                    }
                }
            }
            int nbFinished = 0;
            for (int i = 0; i < nbrVoiture; i++) {
                if (sorter[i].finished) {
                    nbFinished++;
                }
            }
            if (param == 10) {
                qsort(sorter, nbrVoiture, sizeof(car), compare_qualification2);
            } else if (param == 11) {
                qsort(sorter, nbrVoiture, sizeof(car), compare_qualification3);
            } else {
                qsort(sorter, nbrVoiture, sizeof(car), compare_qualification);
            }

            if (nbFinished != nbrVoiture) {
                sleep(1);
                system("clear");
                printf("%s", titre);
                column();
                display(sorter);
                printf("\n");
                display_best_sectors(sorter);
            } else {
                sleep(1);
                system("clear");
                printf("%s", titre);
                column();
                display(sorter);
                printf("\n");
                display_best_sectors(sorter);
                sleep(1);

                switch (param){
                    case 0:
                    case 1:
                    case 2:
                        break;
                    case 3:
                        for(int p = 0; p < nbrVoiture; p++){
                            if (p >= 15){
                                sorter[p].out_qualif1 = 1;
                            }
                        }
                        break;
                    case 10:
                        for(int p = 0; p < nbrVoiture; p++){
                            if (p >= 10){
                                sorter[p].out_qualif2 = 1;
                            }
                        }
                        break;
                    case 11:
                        for(int p = 0; p < nbrVoiture; p++){
                            sorter[p].pos_grid = (p + 1);
                        }
                        qsort(sorter, nbrVoiture, sizeof(car), compare_qualification3);
                        grid(sorter);
                        break;
                    default:
                        return -1;
                }
                finished = 1;
            }
        }

    }

    if (shmdt(b) == -1) {
        perror("shmdt");
        return -1;
    }
    fflush(stdin);
    printf("Pour continuer, appuyer sur Enter ...\n\n");
    getchar();
    system("clear");
    return 0;
}

void menu(int nbrTour, int shmid){
    char type;
    int exit = 0;
    int gpOK = 0;
    do {
        system("clear");
        printf("BIENVENUE AU GRAND-PRIX\n\n");
        printf("1: Séance d'essais numéro 1.\n");
        printf("2: Séance d'essais numéro 2.\n");
        printf("3: Séance d'essais numéro 3.\n");
        printf("4: Séance de qualifications. \n");
        printf("5: Grand-Prix. \n");
        printf("9. Quitter le programme.\n");
        printf("\nFaites votre choix : ");
        fflush(stdin);
        type = getchar();
        getchar();
        fflush(stdin);

        switch(type) {
            case '1':
                run(0, shmid, nbrTour);
                break;
            case '2':
                run(1, shmid, nbrTour);
                break;
            case '3':
                run(2, shmid, nbrTour);
                break;
            case '4':
                run(3, shmid, nbrTour);
                run(10, shmid, nbrTour);
                run(11, shmid, nbrTour);
                gpOK = 1;
                break;
            case '5':
                if (!gpOK) {
                    printf("Veuillez d'abord lancer les qualifications avant le Grand-Prix \n\n");
                    break;
                }
                run(4, shmid, nbrTour);
                break;
            case '9':
                printf("\nLe programme va être fermé.\n\n");
                exit = 1;
                break;
            default:
                printf("\nChoix incorrect. Veuillez réessayer.\n");
        }

    } while(!exit);

}

int main(int argc, char  **argv) {
    if (argc < 2) {
        printf("Veuillez introduire le nombre de tours\n");
        return 0;
    }
    key_t key = ftok("/dev/null", 42);
    int shmid = shmget(key, sizeof(buffer), IPC_CREAT | 0666);
    if (shmid == -1) {
        printf("error shmget\n");
        return 0;
    }
    menu(atoi(argv[1]), shmid);
    sleep(1);
    buffer *b = shmat(shmid, NULL, 0);
    semctl(b->mutex, 0, IPC_RMID, NULL);
    shmdt(b);
    shmctl(shmid, IPC_RMID, NULL);
}