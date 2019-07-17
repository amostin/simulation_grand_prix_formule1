#include <stdio.h>
#include "utilsProjet.h"
#include <ctype.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <string.h>




int tabNum[21] = {0, 44, 77, 5, 7, 3, 33, 11, 31, 18, 35, 27, 55, 10, 28, 8, 20, 2, 14, 9, 16};
int compteur = 0;
int nbrTour = 15;
int numTour = 0;

int listVoiture[2][20];


void father_process(int child_pid) {
    int shmid;
    char *shm;
    key_t key;
    key = 5678;

    if ((shmid = shmget(key, sizeof(listVoiture), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    /*for (int i=0; i<20; i++) {
        printf("%d", listVoiture[i][0]);
    }*/
}


void child_process(){
    int arret = 0;
    int sortie = 0;
    structVoiture car = {0,0,0,0,0,0,999,0,0,0};
    int shmid;
    key_t key;
    char *shm;
    key = 5678;

    srand(getpid());

    if ((shmid = shmget(key, sizeof(listVoiture), 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    while (numTour != nbrTour)
        //on vérifie si la voiture n'est pas sortie de la route
        if (car.out == 0) {

            car.id = getpid();
            car.num = tabNum[compteur];
            car.s1 = genere_sec_entre_min_max(35, 40);
            car.s2 = genere_sec_entre_min_max(35, 40);
            car.s3 = genere_sec_entre_min_max(35, 40);

            arret = genere_sec_entre_min_max(1, 20);
            if (arret == 4) {
                car.pit += 1;
            }

            sortie = genere_sec_entre_min_max(1, 20);
            if (sortie == 2) {
                car.out = 1;
            } else {
                car.out = 0;
            }

            car.tour = calculTour(car.s1, car.s2, car.s3);

            if (car.tour <= car.bestour) {
                car.bestour = car.tour;
            }

            car.total += car.tour;



            printf("%d|", car.id);
            printf("%d|", car.num);
            printf("%d|", car.s1);
            printf("%d|", car.s2);
            printf("%d|", car.s3);
            printf("%s|", timeFormat(car.tour));
            printf("%s|", timeFormat(car.bestour));
            printf("%d|", car.pit);
            printf("%d|", car.out);
            printf("%s|", timeFormat(car.total));
            printf("Numero de tour : %d\n", numTour + 1);

            numTour++;
        } else if (car.out == 1) {
            sleep(1);
            printf("La voiture %d est sortie de la route au tour numéro %d\n", car.num, numTour);
            printf("-------------------------------------------------------------------------------------------------------\n");
            exit(0);
        }






}


int main () {
    for (int i=0; i<5; i++) {

        pid_t pid;
        pid = fork();
        compteur++;
        sleep(2);

        //num++;

        //on vérifie qu'il n'y a pas d'erreur lors du fork
        while ((pid == -1) && (errno == EAGAIN));

        //ici on est dans le fils
        if (pid == 0) {
            //memcpy(&listVoiture[i][0], getpid());
            //printf("%d\n", listVoiture[i][0]);
            //printf("%d\n", getpid());
            child_process();

            printf("-------------------------------------------------------------------------------------------------------\n");

            exit(0);
            //ici on est dans le père
        } else {
            //printf("%d\n", listVoiture[i][0]);
            father_process(pid);
            sleep(2);

        }
    //}for (int i = 0; i<sizeof(tabNum); i++) {

    }
}
