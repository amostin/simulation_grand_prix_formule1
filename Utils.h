//
// Created by root on 24/07/19.
//

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


typedef struct Voiture{
    int id;
    int numTour;
    double s1;
    double s2;
    double s3;
    double tour;
    double bestour;
    int pit;
    int out;
    double total;
}Voiture[20];



//fct qui prend deux nbre en entrée et retourne  un nbre entre les deux entrés. attention lors des tests il renvoi meme un nombre au dessus du max. Retourne un double(plus réaliste).
int randomGenerator(int min, int max){
    //le % defini le max puis le calcul defini le min
    int sec = rand() % (max + 2 - min) + min;
    //retourne le chiffre aléatoire entre min et max+1
    return sec;
}



//calcule le total des 3 secteurs
double calculTour(double timeS1, double timeS2, double timeS3){
    double tour = timeS1+timeS2+timeS3;
    return tour;
}

int stand(){
    if(randomGenerator(1,100) >= 99){
        return 1;
    }
    else{
        return 0;
    }
}

int out(){
    if(randomGenerator(1,1000) >= 999){
        return 1;
    }
    else{
        return 0;
    }
}

//fonction qui va traduire le temps passé en secondes, et va le sortir en chaine de caractere
//sous le format MMminSSsmmm
char *timeFormat(int duree){
    int minutes = duree/60000;
    duree -= (minutes * 60000);
    int sec = duree/1000;
    duree -= sec * 1000;
    int milli = duree;

    static char minutesChar[30];
    char secondesChar[10];
    char millisecChar[10];

    sprintf(minutesChar, "%d", minutes);
    sprintf(secondesChar, "%d", sec);
    sprintf(millisecChar, "%d", milli);

    strcat(minutesChar, "min");
    strcat(minutesChar, secondesChar);
    strcat(minutesChar, "s");
    strcat(minutesChar, millisecChar);

    return minutesChar;
}


void affichage(Voiture f1[20]){
    printf("Num\t|");
    printf("S1\t|");
    printf("S2\t|");
    printf("S3\t|");
    printf("Tour\t\t|");
    printf("Meilleur tour\t|");
    printf("Numéro tour\t|");
    printf("Temps total\t|");
    printf("Stand\t|");
    printf("Sortie\n");
        for (int i = 0; i<20; i++) {
            printf("%d\t|", f1[i]->id);
            printf("%.3f\t|", f1[i]->s1 / (double)1000);
            printf("%.3f\t|", f1[i]->s2 / (double)1000);
            printf("%.3f\t|", f1[i]->s3 / (double)1000);
            printf("%s\t|" , timeFormat(f1[i]->tour));
            printf("%s\t|" , timeFormat(f1[i]->bestour));
            printf("%d\t\t|", f1[i]->numTour);
            printf("%s\t|", timeFormat(f1[i]->total));

            if (f1[i]->pit == 1) {
                printf("PIT\t|");
            } else {
                printf("---\t|");
            }

            if (f1[i]->out == 1) {
                printf("DNF\t\n");
            } else {
                printf("---\t\n");
            }

        }

}

void grid(Voiture f1[20]){
    int place = 1;
    printf("============GRID============\n");
    printf("|                          |\n");
    for (int i; i<20; i++) {
        if (i % 2 == 0) {
            if (f1[i]->id / 10 < 1) {
                printf("|\t[%d ]\t\t   |  %d\n", f1[i]->id, place);
                printf("|\t[  ]\t\t   |\n");
                printf("|\t[  ]\t\t   |\n");
            } else {
                printf("|\t[%d]\t\t   |  %d\n", f1[i]->id, place);
                printf("|\t[  ]\t\t   |\n");
                printf("|\t[  ]\t\t   |\n");
            }
            place++;
        } else {
            if (f1[i]->id / 10 < 1) {
                printf("|\t\t[%d ]\t   |  %d\n", f1[i]->id, place);
                printf("|\t\t[  ]\t   |\n");
                printf("|\t\t[  ]\t   |\n");
            } else {
                printf("|\t\t[%d]\t   |  %d\n", f1[i]->id, place);
                printf("|\t\t[  ]\t   |\n");
                printf("|\t\t[  ]\t   |\n");
            }
            place++;
        }
    }

}

void podium(Voiture f1[20]){
    printf("=========FIN==========\n");
    printf("          %d          \n", f1[0]->id);
    printf("       |‾‾‾‾‾|        \n");
    if (f1[1]->id / 10 < 1) {
        printf("    %d  | [1] |  ", f1[1]->id);
    } else {
        printf("    %d | [1] |  ", f1[1]->id);
    }
    printf("%d   \n", f1[2]->id);
    printf(" |‾‾‾‾‾|     |‾‾‾‾‾|\n");
    printf(" | [2] |     | [3] |\n");
}