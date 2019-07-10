//lib utile au printf() et à la struct FILE
#include <stdio.h>
//lib utile au time()
#include <time.h>
//lib utile au srand()
#include <stdlib.h>
//utile au sleep()
#include <unistd.h>

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

        void convert_sec_min(int sec){
            int combien_de_minute_dans_sec = sec/60;
            sec -= combien_de_minute_dans_sec*60;

            printf("%d min %d sec\n", combien_de_minute_dans_sec, sec);
        }

        void genere_et_affiche_valeur(){

            //on affiche 5 tableau different sans quon ai l'impression qu'il s'efface et se réaffiche
            for(int i = 0; i < 3; i++) {
                int name = 1;
                int s1 = genere_sec_entre_min_max(35, 40);
                int s2 = genere_sec_entre_min_max(35, 40);
                int s3 = genere_sec_entre_min_max(35, 40);

                int tour = calculTour(s1, s2, s3);
                int bestour =  calculTour(s1, s2, s3);
                //convert_sec_min(tour);
                int pit = genere_sec_entre_min_max(1, 10);
                int out = genere_sec_entre_min_max(1, 20);

                //proba pit 1/10, out 1/20
                if(pit == 4){pit = 1;}
                else {pit = 99;}
                if(out == 15){out = 1;}
                else {out = 99;}

                printf("%d  |%d|%d|%d|%d |%d    |%d |%d \n", name, s1, s2, s3, tour, bestour, pit, out);
            }
        }

    //affiche les titres des colonnes avec separatuers et insere des valeurs dedans
    void affiche_titre(){
        //Je veux afficher:
        //name|s1|s2|s3|tour|bestour|pit|out
        //----|--|--|--|----|-------|---|---
        //22|38|37|41|116|105|no|no

        char titres_colonnes[] = "name|s1|s2|s3|tour|bestour|pit|out\n";
        char separateur_titres_valeurs[] = "----|--|--|--|----|-------|---|---\n";

        printf("%s", titres_colonnes);
        printf("%s", separateur_titres_valeurs);

        genere_et_affiche_valeur();

        //string_pour_fichier(titres_colonnes, separateur_titres_valeurs, name, s1, s2, s3, tour, bestour);
    }

int main (int argc, char *argv[]) {
    //petit rappel argc argv comme ça on sais comment gerer les parametre du programme quand on en aura besoin
    if (argc == 1){printf("Le seul argument est le: %s", argv[argc-1]); return 69;}
    else if (argc == 2){printf("Le premier argument est le: %s\nLe deuxieme est: %s", argv[0], argv[1]); return 70;}

    //regex. equivalent de clear pour refresh la console
    printf("\e[1;1H\e[2J");
    affiche_titre();


    //retourne un chiffre car c'est ce que prédit le int devant main()
    return(0);
}
