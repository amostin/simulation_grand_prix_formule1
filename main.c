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

// variable globale pour pouvoir changer changer l'intervalle facilement
int minimum = 35;
int maximum = 40;
//compteur pour les differentes voitures
int num = 0;
//des int sont crees comme compteur pour les arrets ou sortie de route
int arrets = 0;
int sortie = 0;
//int pour la valeur original du meilleur temps (facilite la comparaison)
int bestour = 999;
//on initialise le numero du tour
int numTour = 1;
//on defini la limite de tour ici
int nbrTour = 45;
//on initialise un int pour gérer le temps total
int tempsTotal;



//fonction qui va traduire le temps passé en secondes, et va le sortir en chaine de caractere
//sous le format MMminSS
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

//calcule le total des 3 secteurs
int calculTour(int s1, int s2, int s3){
    int tour = s1+s2+s3;
    return tour;
}

//fct qui prend deux nbre en entrée et retourne  un nbre entre les deux entrés. attention lors des tests il renvoi meme un nombre au dessus du max
int genere_sec_entre_min_max(int min, int max) {
    //le % defini le max puis le calcul defini le min
    int sec = rand() % (max + 2 - min) + min;
    //retourne le chiffre aléatoire entre min et max+1
    return sec;
}

void affiche(){

    int s1 = genere_sec_entre_min_max(minimum, maximum);
    int s2 = genere_sec_entre_min_max(minimum, maximum);
    int s3 = genere_sec_entre_min_max(minimum, maximum);

    int pit = genere_sec_entre_min_max(1, 10);
    int out = genere_sec_entre_min_max(1, 20);

    //je veux calculer s1+s2+s3 et retourner le resultat
    int tour = calculTour(s1, s2, s3);

    //si la voiture s'arrete, on incrémente le int "arrets"
    if(pit == 4){
        arrets += 1;
        tour = tour + genere_sec_entre_min_max(10, 20);
    }

    //si la voiture sort de la route, on passe le int "sortie" a 1
    if(out == 2){sortie = 1;
    } else {sortie = 0;}



    //on enregistre ici le meilleur temps
    if (tour <= bestour){bestour = tour;}

    //on calcule le temps total
    tempsTotal += tour;

    //petite condition pour eviter le decalage avec les numeros de voitures
    if (num/10 < 1) {printf("%d  |", num);}
    else {printf("%d |", num);}

    printf("%d|%d|%d|", s1, s2, s3);

    //petite condition pour eviter le decalage sur le temps du tour
    if (strlen(timeFormat(tour)) == 6) {printf("%s|", timeFormat(tour));}
    else if (strlen(timeFormat(tour)) < 6) {printf("%s |", timeFormat(tour));}

    //petite condition pour eviter le decalage sur le meilleur temps
    if (strlen(timeFormat(bestour)) == 6) {printf("%s |", timeFormat(bestour));}
    else if (strlen(timeFormat(bestour)) < 6) {printf("%s  |", timeFormat(bestour));}

    printf("%d  |%d  |", arrets, sortie);

    //petite condition pour eviter le decalage avec les nombres de tours
    if (numTour/10 < 1) {printf("%d      |", numTour);}
    else {printf("%d     |", numTour);}



    printf("%s\n", timeFormat(tempsTotal));
}


/* La fonction father_process effectue les actions du processus père */
void father_process(int child_pid){

    //on dit ici que c'est le père qui va afficher les colonnes pour chacun des fils
    char titres_colonnes[] = "num|s1|s2|s3|tour  |bestour|pit|out|numTour|Tot\n";
    char separateur_titres_valeurs[] = "---|--|--|--|------|-------|---|---|-------|---\n";

    printf("\n%s", titres_colonnes);
    printf("%s", separateur_titres_valeurs);

}

/* La fonction child_process effectue les actions du processus fils */
void child_process(void){
    //on initialise le random pour chaque process
    srand(getpid());

    //on détermine pour combien de tour le child va s'executer
    for(int i = 0; i < nbrTour; i++) {
        //on vérifie si la voiture n'est pas sortie de la route
        if (sortie == 0) {
            affiche();
            numTour++;
        } else if (sortie == 1) {

            printf("La voiture est sortie de la route au tour numéro %d\n", numTour - 1);
            exit(0);
        }

    }
}


int main () {
    //ici on détermine combien de fils (de voitures) vont être dupliqués
    for (int i=0; i<20; i++) {
        pid_t pid;
        pid = fork();

        sleep(2);

        num++;

        //on vérifie qu'il n'y a pas d'erreur lors du fork
        while ((pid == -1) && (errno == EAGAIN));

        //ici on est dans le fils
        if (pid == 0) {

            child_process();
            exit(0);
        //ici on est dans le père
        } else {

            father_process(pid);
            sleep(1);

        }
    }
}
