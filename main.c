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
                
            //le % () defini le max on ajoute le min comme ça si on a 0 on a le min
            int sec = rand() % (max + 2 - min) + min;
                
            //affiche le nombre contenu dans sec
            //printf("%d", sec);
                
            //retourne le chiffre aléatoire entre min et max+1 inclus
            return sec;
        }

        //calcule le total des 3 secteurs
        int calculTour(int s1, int s2, int s3){
                
            int tour = s1+s2+s3;
            return tour;
        }
        
                //recoit la chaine contenant les titres, separateurs, name, s1, s2, etc.
                void ecrit_classement_final(char valeurs_string[]){

                    //on defini le pointeur du fichier sur NULL pour éviter les erreurs postérieures
                    FILE* fichier = NULL;

                    //on crée/écrase le fichier test.md 
                    fichier = fopen("../test.md", "w+");

                    //si l'ouverture du fichier s'est bien passée
                    if (fichier != NULL) {

                        // On l'écrit dans le fichier
                        fprintf(fichier, "%s", valeurs_string);
                        fclose(fichier);
                        //printf("apres ecriture");
                    }
                    else { printf("\n on a pas su ouvrir le fichier!");}
                }

        //on recoit titre, separateurs, name, etc. puis on enregistre tout dans une chaine pour l'envoyer à l'écriture du fichier
        char string_pour_fichier(char titres_colonnes[], char separateur_titres_valeurs[], int name, int s1, int s2, int s3, int tour, int bestour){
                
            //le tableau qui va contenir la chaine a ecrire dans le fichier
            char valeurs_string[1000];
                
            //fonction qui concatene les nombres dans une chaine avec les separateurs
            sprintf(valeurs_string, "%s%s%d  |%d|%d|%d|%d |%d    |no |no \n", titres_colonnes, separateur_titres_valeurs, name, s1, s2, s3, tour, bestour);
            
            //on appel l'écriture du fichier avec la chaine à écrire
            ecrit_classement_final(valeurs_string);
            //printf("%s", valeurs_string);
        }

        //recoit un nbre en seconde et affiche le nbre converti en min sec
        void convert_sec_min(int sec){
                
            //on recupere le nbre de fois que ya 60 dans le nbre de sec pour ne garder que les minutes
            int combien_de_minute_dans_sec = sec/60;
                
            //on recup la valeur des secondes en trop et en la soustrait au sec pour ne garder que les sec
            sec -= combien_de_minute_dans_sec*60;

            printf("%d min %d sec\n", combien_de_minute_dans_sec, sec);
        }

    //affiche les titres des colonnes avec separatuers et insere des valeurs dedans
    void affiche(){
            
        //Je veux afficher:
        //name|s1|s2|s3|tour|bestour|pit|out
        //----|--|--|--|----|-------|---|---
        //22|38|37|41|116|105|no|no
            
        // on construit la chaine contenant les titres 
        char titres_colonnes[] = "name|s1|s2|s3|tour|bestour|pit|out\n";
            
        // on construit le separateurs de ligne entre titre et valeur
        char separateur_titres_valeurs[] = "----|--|--|--|----|-------|---|---\n";
            
        //génération de nombres pour une voiture
        int name = 1;
        int s1 = genere_sec_entre_min_max(35, 40);
        int s2 = genere_sec_entre_min_max(35, 40);
        int s3 = genere_sec_entre_min_max(35, 40);
            
        //on calcule s1+s2+s3 
        int tour = calculTour(s1, s2, s3);
        int bestour =  calculTour(s1, s2, s3);
        int pit = genere_sec_entre_min_max(1, 10);
        int out = genere_sec_entre_min_max(1, 20);
            
        //on pose les probabilités d'avoir un pit ou un out
        //1/10 = 10% de chance d'avoir un pit
        if(pit == 4){pit = 1;}
        else {pit = 99;}
            
        //1/20 = 5% de chance d'être out
        if(out == 15){out = 1;}
        else {out = 99;}
            
        //test conversion
        //convert_sec_min(tour);
            
        //affiche les titres puis séparateurs puis les valeurs séparées
        printf("%s", titres_colonnes);
        printf("%s", separateur_titres_valeurs);
        printf("%d  |%d|%d|%d|%d |%d    |%d |%d \n", name, s1, s2, s3, tour, bestour, pit, out);

        //envoi les valeurs pour qu'elles soient stockée dans une chaine qui sera écrite dans n fichier
        string_pour_fichier(titres_colonnes, separateur_titres_valeurs, name, s1, s2, s3, tour, bestour);
    }

int main (int argc, char *argv[]) {
        
    //petit rappel argc argv comme ça on sais comment gerer les parametre du programme quand on en aura besoin
    if (argc == 1){printf("Le seul argument est le: %s", argv[argc-1]); return 69;}
    else if (argc == 2){printf("Le premier argument est le: %s\nLe deuxieme est: %s", argv[0], argv[1]); return 70;}

    //on affiche 5 tableau different sans quon ai l'impression qu'il s'efface et se réaffiche
    for(int i = 0; i < 5; i++){
        //regex. equivalent de clear pour refresh la console
        printf("\e[1;1H\e[2J");
        affiche();
    }

    //retourne un chiffre car c'est ce que prédit le int devant main()
    return(0);
}
