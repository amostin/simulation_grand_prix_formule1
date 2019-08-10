//
// Created by athos on 3/08/19.
//

#ifndef F1_PROJECT_UTILS_H
#define F1_PROJECT_UTILS_H

typedef struct Voiture
{
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
    int finished;
} voiture;

typedef struct Buffer
{
    voiture tab[100];
    int size;
    int maxsize;
    int last;
    int first;
    int mutex;
} buffer;

//fct qui prend deux nbre en entrée et retourne  un nbre entre les deux entrés. attention lors des tests il renvoi meme un nombre au dessus du max. Retourne un double(plus réaliste).
int randomGenerator(int min, int max)
{
    //le % defini le max puis le calcul defini le min
    int sec = rand() % (max + 2 - min) + min;
    //retourne le chiffre aléatoire entre min et max+1
    return sec;
}

//calcule le total des 3 secteurs
double calculTour(double timeS1, double timeS2, double timeS3)
{
    double tour = timeS1 + timeS2 + timeS3;
    return tour;
}

int stand()
{
    if (randomGenerator(1, 100) >= 99)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int out()
{
    if (randomGenerator(1, 1000) >= 999)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char *timeFormat(int duree)
{
    int minutes = duree / 60000;
    duree -= (minutes * 60000);
    int sec = duree / 1000;
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

void affichage(voiture f1[20])
{
    for (int i=0; i<20; i++)
    {
        printf("%d\t|", f1[i].id);
        printf("%.3f\t|", f1[i].s1 / (double)1000);
        printf("%.3f\t|", f1[i].s2 / (double)1000);
        printf("%.3f\t|", f1[i].s3 / (double)1000);
        printf("%s\t|", timeFormat(f1[i].tour));
        printf("%s\t|", timeFormat(f1[i].bestour));
        printf("%d\t\t|", f1[i].numTour);
        printf("%s\t|", timeFormat(f1[i].total));

        if (f1[i].pit == 1)
        {
            printf("PIT\t|");
        }
        else
        {
            printf("---\t|");
        }

        if (f1[i].out == 1)
        {
            printf("DNF\t\n");
        }
        else
        {
            printf("---\t\n");
        }
    }

}

void column()
{
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
}

void sem_lock(int sem_id, int sem_channel){
    struct sembuf op;
    op.sem_num = sem_channel;
    op.sem_op = -1;
    op.sem_flg =  0;
    semop(sem_id, &op, 1);
}

void sem_unlock(int sem_id, int sem_channel){
    struct sembuf op;
    op.sem_num = sem_channel;
    op.sem_op = 1;
    op.sem_flg = IPC_NOWAIT;
    semop(sem_id, &op, 1);
}

void sem_reset(int sem_id, int sem_channel){
    semctl(sem_id, sem_channel, SETVAL, 1);
}

int init_buff(buffer *b)
{
    b->size = 0;
    b->maxsize = 100;
    b->last = -1;
    b->first = -1;
    key_t sem_mutex_key = ftok("/dev/null", 43);
    b->mutex = semget(sem_mutex_key, 1, IPC_CREAT | 0666);
    sem_reset(b->mutex, 0);
    return 0;
}

int init_voiture(voiture *v, int id)
{

    v->id = id;
    v->numTour = 0;
    v->s1 = -1;
    v->s2 = -1;
    v->s3 = -1;
    v->tour = 0;
    v->bestour = -1;
    v->pit = -1;
    v->out = -1;
    v->total = 0;
    v->finished = 0;
    return 0;
}

int insert(buffer *b, voiture *v, double tempsCourse)
{

    v->s1 = randomGenerator(45000, 50000);
    v->s2 = randomGenerator(30000, 35000);
    v->s3 = randomGenerator(25000, 30000);

    v->tour = calculTour(v->s1, v->s2, v->s3);
    if (v->bestour == -1)
    {
        v->bestour = v->tour;
    }
    else
    {
        if (v->tour < v->bestour)
        {
            v->bestour = v->tour;
        }
    }
    (v->numTour)++;
    v->total += v->tour;
    v->pit = stand();
    if (v->pit == 1)
    {
        v->s3 += randomGenerator(10000, 15000);
    }
    v->out = out();
    if (v->out) {
        v->finished = 1;
    }

    if (tempsCourse != 0){
        if (v->total >= tempsCourse) {
            v->finished = 1;
        }
    }

    sem_lock(b->mutex, 0);
    b->last = (b->last + 1) % (b->maxsize);
    b->size++;
    b->tab[b->last] = (*v);
    sem_unlock(b->mutex, 0);
    return 0;
}

voiture rem(buffer *b)
{
    voiture ret;
    sem_lock(b->mutex, 0);
    ret = b->tab[(b->first)];
    if (b->first == b->last)
    {
        b->first = b->last = 0;
    }
    else
    {
        b->first = (b->first + 1) % (b->maxsize);
    }
    b->size--;
    sem_unlock(b->mutex, 0);

    return ret;
}

int compare_qualification(const void * a, const void * b)
{
    voiture *voitureA = (voiture *)a;
    voiture *voitureB = (voiture *)b;

    double bestA = voitureA->bestour;
    double bestB = voitureB->bestour;
    if (bestA > bestB) {
        return 1;
    } else if (bestA < bestB) {
        return -1;
    } else {
        return 0;
    }

    return (voitureA->bestour - voitureB->bestour);
}

int compare_race(const void *a, const void *b)
{
    voiture *voitureA = (voiture *)a;
    voiture *voitureB = (voiture *)b;

    if (voitureA->out && !voitureB->out) {
        return 1;
    } else if (!voitureA->out && voitureB->out) {
        return -1;
    } else {
        double tempsMA = (voitureA->total/voitureA->numTour);
        double tempsMB = (voitureB->total/voitureB->numTour);
        if (tempsMA > tempsMB) {
            return 1;
        } else if (tempsMA < tempsMB) {
            return -1;
        } else {
            return 0;
        }
    }
}

void grid(voiture f1[20]){
    int place = 1;
    printf("============GRID============\n");
    printf("|                          |\n");
    for (int i = 0; i<20; i++) {
        if (i % 2 == 0) {
            if (f1[i].id / 10 < 1) {
                printf("|\t[%d ]\t\t   |  %d\n", f1[i].id, place);
                printf("|\t[  ]\t\t   |\n");
                printf("|\t[  ]\t\t   |\n");
            } else {
                printf("|\t[%d]\t\t   |  %d\n", f1[i].id, place);
                printf("|\t[  ]\t\t   |\n");
                printf("|\t[  ]\t\t   |\n");
            }
            place++;
        } else {
            if (f1[i].id / 10 < 1) {
                printf("|\t\t[%d ]\t   |  %d\n", f1[i].id, place);
                printf("|\t\t[  ]\t   |\n");
                printf("|\t\t[  ]\t   |\n");
            } else {
                printf("|\t\t[%d]\t   |  %d\n", f1[i].id, place);
                printf("|\t\t[  ]\t   |\n");
                printf("|\t\t[  ]\t   |\n");
            }
            place++;
        }
    }

}

void podium(voiture f1[20]){
    printf("=========FIN==========\n");
    printf("          %d          \n", f1[0].id);
    printf("       |‾‾‾‾‾|        \n");
    if (f1[1].id / 10 < 1) {
        printf("    %d  | [1] |  ", f1[1].id);
    } else {
        printf("    %d | [1] |  ", f1[1].id);
    }
    printf("%d   \n", f1[2].id);
    printf(" |‾‾‾‾‾|     |‾‾‾‾‾|\n");
    printf(" | [2] |     | [3] |\n");
}

#endif //F1_PROJECT_UTILS_H