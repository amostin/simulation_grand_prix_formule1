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

            course = shmat(shmid, 0, 0);

            if (course == (Voiture *)-1) {
                perror("shmat");
                exit(1);
            }
            course[i]->id = ID[i];
            course[i]->s1 = genS1();
            course[i]->s2 = genS2();
            course[i]->s3 = genS3();
            course[i]->tour = calculTour(course[i]->s1, course[i]->s2, course[i]->s3);
            printf("%d\n", course[i]->id);
            printf("%.3f\n", (course[i]->s1)/(double)1000);
            printf("%.3f\n", (course[i]->s2)/(double)1000);
            printf("%.3f\n", (course[i]->s3)/(double)1000);
            printf("%s\n" , timeFormat(course[i]->tour));



            exit(0);
        } else {

            sleep(1);
        }
    }
}



