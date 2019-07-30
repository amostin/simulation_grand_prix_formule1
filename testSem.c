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
#include <semaphore.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/shm.h>
#include "../../../usr/include/zconf.h"




int ID[20] = {44, 77, 5, 7, 3, 33, 11, 31, 18, 35, 27, 55, 10, 28, 8, 20, 2, 14, 9, 16};
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
}voiture;


typedef struct Buffer{
    int shmid_buffer;
    int size;
    int maxsize;
    int last;
    int first;
    sem_t mutex;
    sem_t full;
    sem_t empty;
}buffer;

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

int init_buff(buffer *b, key_t key){
    b->shmid_buffer = shmget(key, 20*sizeof(voiture), IPC_CREAT | 0666);
    b->size = -1;
    b->maxsize = 20;
    b->last = -1;
    b->first = -1;
    sem_init(&(b->mutex), 0, 1);
    sem_init(&(b->full), 0, 0);
    sem_init(&(b->empty), 0, 20);
    return 0;
}

int init_voiture(voiture *v, int id){

    v->id = id;
    v-> numTour  = 0;
    v -> s1 = -1;
    v-> s2 = -1;
    v-> s3 = -1;
    v-> tour = 0;
    v-> bestour = -1;
    v-> pit = -1;
    v->  out = -1;
    v-> total = 0;
    return 0;
}

int insert(buffer *b, voiture *v) {

    v->s1 = randomGenerator(45000, 50000);
    v->s2 = randomGenerator(30000, 35000);
    v->s3 = randomGenerator(25000, 30000);

    v->tour = calculTour(v->s1, v->s2, v->s3);
    if(v->bestour == -1)
    {
        v->bestour = v->tour;
    }
    else
    {
        if(v->tour < v->bestour)
        {
            v->bestour = v->tour;
        }
    }
    (v->numTour)++;
    v->total += v->tour;
    v->pit = stand();
    v->out = out();

    sem_wait(&b->empty);
    sem_wait(&b->mutex);
    voiture *tab = shmat(b->shmid_buffer, 0, 0);
    b->last = (b->last + 1) % b->maxsize;
    b->size++;
    tab[b->last] = *v;
    sem_post(&b->mutex);
    sem_post(&b->full);
    return 0;

}

voiture rem(buffer *b){
    voiture ret;

    sem_wait(&b->full);
    sem_wait(&b->mutex);
    voiture *tab = shmat(b->shmid_buffer, 0, 0);
    ret = tab[b->first];
    b->first = (b->first + 1) % b->maxsize;
    b->size--;
    sem_post(&b->mutex);
    sem_post(&b->empty);
    return ret;
}

int main() {
    //mémoire partagé pour la structure buffer
    key_t key2 = 2048;
    int shmid = shmget(key2, sizeof(buffer), IPC_CREAT | 0666);
    buffer *b  = shmat(shmid, 0, 0);
    //On initialise la structure buffer
    buffer bHelper;
    key_t key;
    key = 4000;
    init_buff(&bHelper,key);
    //on remplis la mémoire partagé ave le buffer
    *b = bHelper;
    //on initialise les voitures
    voiture vtab[10] ;
    for(int i = 0; i <10 ; i++){
        init_voiture(&vtab[i], ID[i]);
    }


    for (int i=0; i<10; i++) {

        pid_t pid;
        pid = fork();

        if (pid == 0) {
            srand(getpid());
            buffer *b2 = shmat(shmid,0,0);

            insert(b2, &vtab[i]);

            insert(b2, &vtab[i]);
            exit(0);

        }
        else {
            //printf("je suis le pere : %d\n", getpid());
            //waitpid(0, 0, 0);
            usleep(500);
            //sleep(1);
            voiture *temp = shmat(b -> shmid_buffer, 0, 0);
            printf("%d\n", temp[i].id);
            printf("%.3f\n", temp[i].s1);
            printf("%.3f\n", temp[i].s2);
            printf("%.3f\n", temp[i].s3);
            printf("%.3f\n", temp[i].tour);
            printf("%d\n", temp[i].numTour);
            printf("=================\n");
            }

        }
    /*voiture *temp = shmat(b -> shmid_buffer, 0, 0);
    for (int i=0; i<10; i++) {
        printf("%d\n", temp[i].id);
        printf("%.3f\n", temp[i].s1);
        printf("%.3f\n", temp[i].s2);
        printf("%.3f\n", temp[i].s3);
        printf("%.3f\n", temp[i].tour);
        printf("%d\n", temp[i].numTour);
        printf("=================\n");
    }*/
    return 0;
}