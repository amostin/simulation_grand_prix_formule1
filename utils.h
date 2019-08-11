//
// Created by athos on 3/08/19.
//

#ifndef _UTILS_H
#define _UTILS_H

typedef struct Car
{
    int id;
    int num_lap;
    double s1;
    double s2;
    double s3;
    double best_s1;
    double best_s2;
    double best_s3;
    double lap;
    double best_lap;
    int pit;
    int out;
    double total;
    int finished;
    int out_qualif1;
    int out_qualif2;
    int pos_grid;
} car;

typedef struct Buffer
{
    car tab[100];
    int size;
    int maxsize;
    int last;
    int first;
    int mutex;
} buffer;

int random_generator(int min, int max);

double calculate_lap(double timeS1, double timeS2, double timeS3);

int stand();

int out();

char *time_format(int duree);

void display(car f1[20]);

void column();

void sem_lock(int sem_id, int sem_channel);

void sem_unlock(int sem_id, int sem_channel);

void sem_reset(int sem_id, int sem_channel);

int init_buff(buffer *b);

int init_voiture(car *v, int id);

int insert(buffer *b, car *v, double tempsCourse);

car rem(buffer *b);

int compare_qualification(const void * a, const void * b);

int compare_qualification2(const void * a, const void * b);

int compare_qualification3(const void * a, const void * b);

int compare_race(const void *a, const void *b);

int compare_sector1(const void *a, const void *b);

int compare_sector2(const void *a, const void *b);

int compare_sector3(const void *a, const void *b);

void display_best_sectors(car tab[20]);

void grid(car f1[20]);

void podium(car f1[20]);

#endif
