//lib utile au printf()
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
    //un temps aléatoire
    time_t t;
    //generation d'un nouveau nbre aleatoire parce que sinon ya que le premier qui est aleatoire puis le reste est le meme
    srand((unsigned) time(&t));
    //le % defini le max puis le calcul defini le min
    int sec = rand() % (max + 2 - min) + min;
    //affiche le nombre contenu dans sec
    printf("%d", sec);
    //retourne le chiffre aléatoire entre min et max
    return sec;
}

int main () {

    //Je veux afficher:
    //name|s1|s2|s3|tour|bestour|pit|out
    //----|--|--|--|----|-------|---|---
    //22|38|37|41|116|105|no|no

    int name = genere_sec_entre_min_max(10, 22);
    int s1 = genere_sec_entre_min_max(35, 40);
    int s2 = genere_sec_entre_min_max(35, 40);
    int s3 = genere_sec_entre_min_max(35, 40);
    int tour = genere_sec_entre_min_max(105, 123);
    int bestour = genere_sec_entre_min_max(105, 110);

    printf("name|s1|s2|s3|tour|bestour|pit|out\n");
    printf("----|--|--|--|----|-------|---|---\n");
    printf("%d  |%d|%d|%d|%d |%d    |no |no ", name, s1, s2, s3, tour, bestour);

    //retourne un chiffre car c'est ce que prédit le int devant main()
    return(0);
}
