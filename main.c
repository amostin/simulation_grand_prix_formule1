/* Pour les constantes EXIT_SUCCESS et EXIT_FAILURE */
#include <stdlib.h>
/* Pour fprintf() */
#include <stdio.h>
/* Pour fork() */
#include <unistd.h>
/* Pour perror() et errno */
#include <errno.h>
/* Pour le type pid_t */
#include <sys/types.h>
/* Pour wait() */
#include <sys/wait.h>
//utile au strcat()
#include <string.h>
#include <time.h>
#include <sys/shm.h>
#include "Utils.h"


int main() {
    int ID[20] = {44, 77, 5, 7, 3, 33, 11, 31, 18, 35, 27, 55, 10, 28, 8, 20, 2, 14, 9, 16};

    int shmid;
    key_t key;
    key = 5678;

    Voiture *course;

    shmid = shmget(key, 20*sizeof(Voiture), IPC_CREAT|666);

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    course = shmat(shmid, 0, 0);

    if (course == (Voiture *)-1) {
        perror("shmat");
        exit(1);
    }



    for (int i=0; i<20; i++) {
        pid_t pid;
        pid = fork();

        if (pid == 0) {
            srand(getpid());

            int cptTour = 1;

            course = shmat(shmid, 0, 0);

            if (course == (Voiture *)-1) {
                perror("shmat");
                exit(1);
            }
            course[i]->id = ID[i];
            course[i]->s1 = randomGenerator(45000, 50000);
            course[i]->s2 = randomGenerator(30000, 35000);
            course[i]->s3 = randomGenerator(25000, 30000);
            course[i]->tour = calculTour(course[i]->s1, course[i]->s2, course[i]->s3);
            course[i]->bestour = 299999.00;
            if (course[i]->tour < course[i]->bestour) {
                course[i]->bestour = course[i]->tour;
            }
            course[i]->numTour = cptTour;
            cptTour++;
            course[i]->total += course[i]->tour;
            course[i]->pit = stand();
            course[i]->out = out();

            if (shmdt(course) == -1) {
                perror("shmdt");
                exit(1);
            }

            exit(0);


        } else {

            sleep(1);
        }
    }
    affichage(course);
    grid(course);
    podium(course);
    shmctl(shmid, IPC_RMID, NULL);
}



