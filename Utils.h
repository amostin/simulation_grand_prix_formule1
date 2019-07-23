//
// Created by Rémy Vase on 2019-07-23.
//

#ifndef TESTUTILS_UTILS_H
#define TESTUTILS_UTILS_H

#endif //TESTUTILS_UTILS_H



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

//Compare secteur pour voir quel temps est le plus petit et pour l'afficher.
double bestSect(double a,double b){
    if(a > b){
        return b;
    }
    if(a < b){
        return a;
    }
    return a;
}

//Fonction qui génère la chance de passer au pit ou d'être out. Retourne un int ici
int genere_chance(int min,int max){
    //le % defini le max puis le calcul defini le min
    int chance = rand() % (max + 2 -min) + min;
    //retourne le chiffre aléatoire entre min et max+1
    return chance;
}

//fct qui prend deux nbre en entrée et retourne  un nbre entre les deux entrés. attention lors des tests il renvoi meme un nombre au dessus du max. Retourne un double(plus réaliste).
int genere_sec_entre_min_max(int min, int max){
    //le % defini le max puis le calcul defini le min
    int sec = rand() % (max + 2 - min) + min;
    //retourne le chiffre aléatoire entre min et max+1
    return sec;
}

//Fonction qui génère le temps d'une voiture pour S1.
int genS1(){
    double timeS1 = genere_sec_entre_min_max(45000, 50000);
    return timeS1;
}

//Fonction qui génère le temps d'une voiture pour S2.
int genS2(){
    double timeS2 = genere_sec_entre_min_max(30000, 35000);
    return timeS2;
}

//Fonction qui génère le temps d'une voiture pour S3.
int genS3(){
    double timeS3 = genere_sec_entre_min_max(20000, 27000);
    return timeS3;
}

//calcule le total des 3 secteurs
double calculTour(double timeS1, double timeS2, double timeS3){
    double tour = timeS1+timeS2+timeS3;
    return tour;
}

int stand(){
    if(genere_chance(1,100) >= 99){
        return 1;
    }
    else{
        return 0;
    }
}

int out(){
    if(genere_chance(1,1000) >= 99){
        return 1;
    }
    else{
        return 0;
    }
}

//fonction qui va traduire le temps passé en secondes, et va le sortir en chaine de caractere
//sous le format MMminSS
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
