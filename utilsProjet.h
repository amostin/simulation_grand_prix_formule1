//
// Created by root on 16/07/19.
//

/*#ifndef STRUCTURE_UTILSPROJET_H
#define STRUCTURE_UTILSPROJET_H

#endif //STRUCTURE_UTILSPROJET_H*/

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


typedef struct structVoiture {
    int id;
    int num;
    int s1;
    int s2;
    int s3;
    int tour;
    int bestour;
    int pit;
    int out;
    int total;
}structVoiture;

structVoiture *voitures;

int genere_sec_entre_min_max(int min, int max) {
    //le % defini le max puis le calcul defini le min
    int sec = rand() % (max + 2 - min) + min;
    //retourne le chiffre aléatoire entre min et max+1
    return sec;
}

int calculTour(int s1, int s2, int s3){
    int tour = s1+s2+s3;
    return tour;
}

char *timeFormat(int duree) {
    int minutes = duree/60;
    duree -= minutes * 60;

    static char minutesChar[30];
    char secondesChar[10];

    sprintf(minutesChar, "%d", minutes);
    sprintf(secondesChar, "%d", duree);

    strcat(minutesChar, "min");
    strcat(minutesChar, secondesChar);

    return minutesChar;
}