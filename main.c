//lib utile au printf() et à la struct FILE
#include <stdio.h>
//lib utile au time()
#include <time.h>
//lib utile au srand()
#include <stdlib.h>
//utile au sleep()
#include <unistd.h>
//utile au strlen, strcat
#include <string.h>

//compteur pour les differentes voitures
int num = 1;
//num = num + 1; il faudra placer cette ligne lorsqu'on créera nos 20 voitures

//des int sont crees comme compteur pour les arrets ou sortie de route
int arrets = 0;
int sortie = 0;

//int pour la valeur original du meilleur temps (facilite la comparaison)
int bestour = 999;

//on initialise le numero du tour
int numTour = 1;
//on defini la limite de tour ici
int nbrTour = 15;

//on initialise un int pour gérer le temps total
int tempsTotal;




    //fct qui prend deux nbre en entrée et retourne  un nbre entre les deux entrés. attention lors des tests il renvoi meme un nombre au dessus du max
    int genere_sec_entre_min_max(int min, int max) {
        //pour etre sur que ça genere un temps different
        sleep(1);
        //un temps aléatoire pas si aléatoire
        time_t t;
        //generation d'un nouveau nbre aleatoire parce que sinon ya que le premier qui est aleatoire puis le reste est le meme
        srand((unsigned) time(&t));
        //le % defini le max puis le calcul defini le min
        int sec = rand() % (max + 2 - min) + min;
        //affiche le nombre contenu dans sec
        //printf("%d", sec);
        //retourne le chiffre aléatoire entre min et max
        return sec;
    }

    //calcule le total des 3 secteurs
    int calculTour(int s1, int s2, int s3){
        int tour = s1+s2+s3;
        return tour;
    }

    void ecrit_classement_final(char valeurs_string[]){

        FILE* fichier = NULL;

        fichier = fopen("../test.md", "w+");

        if (fichier != NULL) {
            // On l'écrit dans le fichier
            fprintf(fichier, "%s", valeurs_string);
            fclose(fichier);
            //printf("apres ecriture");
        }
        else { printf("\n on a pas su ouvrir le fichier!");}
    }

    char string_pour_fichier(char titres_colonnes[], char separateur_titres_valeurs[], int name, int s1, int s2, int s3, int tour, int bestour){
        //le tableau qui va contenir la chaine a ecrire dans le fichier
        char valeurs_string[1000];
        //fonction qui concatene les nombres dans une chaine avec les separateurs
        sprintf(valeurs_string, "%s%s%d  |%d|%d|%d|%d |%d    |no |no \n", titres_colonnes, separateur_titres_valeurs, name, s1, s2, s3, tour, bestour);
        ecrit_classement_final(valeurs_string);
        //printf("%s", valeurs_string);
    }


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

    //affiche les titres des colonnes avec separatuers et insere des valeurs dedans
    void affiche(){
        //Je veux afficher:
        //name|s1|s2|s3|tour|bestour|pit|out
        //----|--|--|--|----|-------|---|---
        //22|38|37|41|116|105|no|no
        char titres_colonnes[] = "num|s1|s2|s3|tour  |bestour|pit|out|numTour|Tot\n";
        char separateur_titres_valeurs[] = "---|--|--|--|------|-------|---|---|-------|---\n";


        int s1 = genere_sec_entre_min_max(35, 40);
        int s2 = genere_sec_entre_min_max(35, 40);
        int s3 = genere_sec_entre_min_max(45, 50);

        int pit = genere_sec_entre_min_max(1, 10);
        int out = genere_sec_entre_min_max(1, 20);

        //si la voiture s'arrete, on incrémente le int "arrets"
        if(pit == 4){arrets += 1;}

        //si la voiture sort de la route, on passe le int "sortie" a 1
        if(out == 2){sortie = 1;}
        else {sortie = 0;}

        //je veux calculer s1+s2+s3 et retourner le resultat
        int tour = calculTour(s1, s2, s3);

        //on enregistre ici le meilleur temps
        if (tour <= bestour){
            bestour = tour;
        }

        //on calcule le temps total
        tempsTotal += tour;

        printf("%s", titres_colonnes);
        printf("%s", separateur_titres_valeurs);

        printf("%d  |%d|%d|%d|", num, s1, s2, s3);

        //petite condition pour eviter le decalage sur le temps du tour
        if (strlen(timeFormat(tour)) == 6) {
            printf("%s|", timeFormat(tour));
        } else if (strlen(timeFormat(tour)) < 6) {
            printf("%s |", timeFormat(tour));
        }

        //petite condition pour eviter le decalage sur le meilleur temps
        if (strlen(timeFormat(bestour)) == 6) {
            printf("%s |", timeFormat(bestour));
        } else if (strlen(timeFormat(bestour)) < 6) {
            printf("%s  |", timeFormat(bestour));
        }

        printf("%d  |%d  |", arrets, sortie);

        //petite condition pour eviter le decalage avec les nombres de tours
        if (numTour/10 < 1) {
            printf("%d      |", numTour);
        } else {
            printf("%d     |", numTour);
        }

        printf("%s\n", timeFormat(tempsTotal));

        string_pour_fichier(titres_colonnes, separateur_titres_valeurs, num, s1, s2, s3, tour, bestour);
    }



int main (int argc, char *argv[]) {
    //petit rappel argc argv comme ça on sais comment gerer les parametre du programme quand on en aura besoin
    if (argc == 1){printf("Le seul argument est le: %s", argv[argc-1]); return 69;}
    else if (argc == 2){printf("Le premier argument est le: %s\nLe deuxieme est: %s", argv[0], argv[1]); return 70;}

    //on affiche 5 tableau different sans quon ai l'impression qu'il s'efface et se réaffiche

    for(numTour= 1; numTour <= nbrTour; numTour++){
        //regex. equivalent de clear pour refresh la console
        if (sortie == 0) {
            printf("\e[1;1H\e[2J");
            affiche();
        } else if (sortie == 1) {
            printf("Sortie de route de la voiture \n");
            return(0);
        }
    }
    printf("Fin de la course\n");

    //retourne un chiffre car c'est ce que prédit le int devant main()
    return(0);
}
