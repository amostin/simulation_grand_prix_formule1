//lib utile au printf()
#include <stdio.h>
//lib utile au time()
#include <time.h>
//lib utile au srand()
#include <stdlib.h>

int main () {
    //un temps aléatoire
    time_t t;
    //generation d'un nouveau nbre aleatoire parce que sinon ya que le premier qui est aleatoire puis le reste est le meme
    srand((unsigned) time(&t));
    //fct qui prend deux nbre en entrée et retourne  un nbre entre les deux entrés
    int genere_sec_entre_min_max(int min, int max) { return rand() % (max + 2 - min) + min; }
    //sec contient un chiffre entre 35 et 40
    int sec = genere_sec_entre_min_max(35, 40);
    //affiche le nombre contenu dans sec
    printf("%d", sec);
    //retourne un chiffre car c'est ce que prédit le int devant main()
    return(0);
}
