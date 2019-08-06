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
} voiture;

typedef struct Buffer
{
    voiture tab[100];
    int size;
    int maxsize;
    int last;
    int first;
    sem_t mutex;
    sem_t full;
    sem_t empty;
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
    for (int i=1; i<20; i++)
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

int init_buff(buffer *b)
{
    b->size = 0;
    b->maxsize = 100;
    b->last = -1;
    b->first = -1;
    sem_init(&(b->mutex), 1, 1);
    sem_init(&(b->full), 1, 0);
    sem_init(&(b->empty), 1, 100);
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
    return 0;
}

int insert(buffer *b, voiture *v)
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
    v->out = out();

    sem_wait(&(b->empty));
    sem_wait(&(b->mutex));
    if (b->first == -1)
    {
        b->first = 0;
    }
    b->last = (b->last + 1) % (b->maxsize);
    b->size++;
    b->tab[b->last] = (*v);
    sem_post(&(b->mutex));
    sem_post((&b->full));
    return 0;
}

voiture rem(buffer *b)
{
    voiture ret;
    sem_wait(&(b->full));
    sem_wait(&(b->mutex));
    ret = b->tab[(b->first)];
    if (b->first == b->last)
    {
        b->first = b->last = -1;
    }
    else
    {
        b->first = (b->first + 1) % (b->maxsize);
    }
    b->size--;
    sem_post(&(b->mutex));
    sem_post(&(b->empty));
    return ret;
}

#endif //F1_PROJECT_UTILS_H
