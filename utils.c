#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "utils.h"



int random_generator(int min, int max) {
    int sec = rand() % (max + 2 - min) + min;
    return sec;
}

double calculate_lap(double timeS1, double timeS2, double timeS3) {
    double tour = timeS1 + timeS2 + timeS3;
    return tour;
}

int stand() {
    if (random_generator(1, 100) >= 99) {
        return 1;
    }
    else {
        return 0;
    }
}

int out() {
    if (random_generator(1, 1000) >= 999) {
        return 1;
    }
    else {
        return 0;
    }
}

char *time_format(int duree) {
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

void display(car f1[20]) {
    for (int i=0; i<20; i++) {
        printf("%d\t|", f1[i].id);
        printf("%.3f\t|", f1[i].s1 / (double)1000);
        printf("%.3f\t|", f1[i].s2 / (double)1000);
        printf("%.3f\t|", f1[i].s3 / (double)1000);
        printf("%s\t|", time_format(f1[i].lap));
        printf("%s\t|", time_format(f1[i].best_lap));
        printf("%d\t\t|", f1[i].num_lap);
        printf("%s\t|", time_format(f1[i].total));

        if (f1[i].pit == 1) {
            printf("PIT\t|");
        }
        else {
            printf("---\t|");
        }

        if (f1[i].out == 1) {
            printf("DNF\t\n");
        }
        else {
            printf("---\t\n");
        }
    }

}

void column() {
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

void sem_lock(int sem_id, int sem_channel) {
    struct sembuf op;
    op.sem_num = sem_channel;
    op.sem_op = -1;
    op.sem_flg =  0;
    semop(sem_id, &op, 1);
}

void sem_unlock(int sem_id, int sem_channel) {
    struct sembuf op;
    op.sem_num = sem_channel;
    op.sem_op = 1;
    op.sem_flg = IPC_NOWAIT;
    semop(sem_id, &op, 1);
}

void sem_reset(int sem_id, int sem_channel) {
    semctl(sem_id, sem_channel, SETVAL, 1);
}

int init_buff(buffer *b) {
    b->size = 0;
    b->maxsize = 100;
    b->last = 0;
    b->first = 0;
    key_t sem_mutex_key = ftok("/dev/null", 43);
    b->mutex = semget(sem_mutex_key, 1, IPC_CREAT | 0666);
    sem_reset(b->mutex, 0);
    return 0;
}

int init_voiture(car *v, int id) {
    v->id = id;
    v->num_lap = 0;
    v->s1 = -1;
    v->s2 = -1;
    v->s3 = -1;
    v->best_s1 = -1;
    v->best_s2 = -1;
    v->best_s3 = -1;
    v->lap = 0;
    v->best_lap = -1;
    v->pit = -1;
    v->out = -1;
    v->total = 0;
    v->finished = 0;
    v->out_qualif1 = 0;
    v->out_qualif2 = 0;
    v->pos_grid = 0;
    return 0;
}

int insert(buffer *b, car *v, double tempsCourse) {
    v->s1 = random_generator(45000, 50000);
    v->s2 = random_generator(30000, 35000);
    v->s3 = random_generator(25000, 30000);

    if (v->best_s1 == -1) {
        v->best_s1 = v->s1;
    }
    else {
        if (v->s1 < v->best_s1) {
            v->best_s1 = v->s1;
        }
    }

    if (v->best_s2 == -1) {
        v->best_s2 = v->s2;
    }
    else {
        if (v->s2 < v->best_s2) {
            v->best_s2 = v->s2;
        }
    }
    if (v->best_s3 == -1) {
        v->best_s3 = v->s3;
    }
    else {
        if (v->s3 < v->best_s3) {
            v->best_s3 = v->s3;
        }
    }
    v->lap = calculate_lap(v->s1, v->s2, v->s3);
    if (v->best_lap == -1) {
        v->best_lap = v->lap;
    }
    else {
        if (v->lap < v->best_lap) {
            v->best_lap = v->lap;
        }
    }
    (v->num_lap)++;
    v->total += v->lap;
    v->pit = stand();
    if (v->pit == 1) {
        v->s3 += random_generator(10000, 15000);
    }
    v->out = out();
    if (v->out) {
        v->finished = 1;
    }

    if (tempsCourse != 0) {
        if (v->total >= tempsCourse) {
            v->finished = 1;
        }
    }
    unsigned int waitT = (unsigned int)v->lap;
    usleep(waitT);
    sem_lock(b->mutex, 0);
    b->size++;
    b->tab[b->last] = (*v);
    b->last = (b->last + 1) % (b->maxsize);
    sem_unlock(b->mutex, 0);
    return 0;
}

car rem(buffer *b) {
    car ret;
    sem_lock(b->mutex, 0);
    ret = b->tab[(b->first)];
    init_voiture(&(b->tab[b->first]), 0);
    if (b->first == b->last) {
        b->first = b->last = 0;
    } else {
        b->first = (b->first + 1) % (b->maxsize);
    }
    b->size--;
    sem_unlock(b->mutex, 0);
    return ret;
}

int compare_qualification(const void * a, const void * b) {
    car *car_a = (car *)a;
    car *car_b = (car *)b;

    double bestA = car_a->best_lap;
    double bestB = car_b->best_lap;
    if (bestA > bestB) {
        return 1;
    } else if (bestA < bestB) {
        return -1;
    } else {
        return 0;
    }

}
int compare_qualification2(const void * a, const void * b) {
    car *car_a = (car *)a;
    car *car_b = (car *)b;

    double bestA = car_a->best_lap;
    double bestB = car_b->best_lap;
    int qualifA = car_a->out_qualif1;
    int qualifB = car_b->out_qualif1;
    if (qualifA > qualifB) {
        return 1;
    } else if (qualifA < qualifB){
        return -1;
    } else {
        if (bestA > bestB) {
            return 1;
        } else if (bestA < bestB) {
            return -1;
        } else {
            return 0;
        }
    }
}

int compare_qualification3(const void * a, const void * b) {
    car *car_a = (car *)a;
    car *car_b = (car *)b;

    double bestA = car_a->best_lap;
    double bestB = car_b->best_lap;
    int qualif2A = car_a->out_qualif2;
    int qualif2B = car_b->out_qualif2;
    int qualif1A = car_a->out_qualif1;
    int qualif1B = car_b->out_qualif1;
    if (qualif1A > qualif1B){
        return 1;
    } else if (qualif1A < qualif1B) {
        return -1;
    } else {
        if (qualif2A > qualif2B) {
            return 1;
        } else if (qualif2A < qualif2B){
            return -1;
        } else {
            if (bestA > bestB) {
                return 1;
            } else if (bestA < bestB) {
                return -1;
            } else {
                return 0;
            }
        }
    }

}

int compare_race(const void *a, const void *b) {
    car *car_a = (car *)a;
    car *car_b = (car *)b;

    if (car_a->out && !car_b->out) {
        return 1;
    } else if (!car_a->out && car_b->out) {
        return -1;
    } else {
        double tourA = car_a->num_lap;
        double tourB= car_b->num_lap;
        if (tourA > tourB) {
            return -1;
        } else if (tourA < tourB) {
            return 1;
        } else {
            double totalA = car_a->total;
            double totalB = car_b->total;
            if (totalA > totalB) {
                return 1;
            } else if (totalA < totalB) {
                return -1;
            } else {
                return 0;
            }
        }
    }
}

int compare_sector1(const void *a, const void *b) {
    car *car_a = (car *)a;
    car *car_b = (car *)b;

    return (car_a->best_s1 - car_b->best_s1);
}

int compare_sector2(const void *a, const void *b) {
    car *car_a = (car *)a;
    car *car_b = (car *)b;

    return (car_a->best_s2 - car_b->best_s2);
}

int compare_sector3(const void *a, const void *b) {
    car *car_a = (car *)a;
    car *car_b = (car *)b;

    return (car_a->best_s3 - car_b->best_s3);
}

void display_best_sectors(car tab[20]) {
    qsort(tab, 20, sizeof(car), compare_sector1);
    printf("Meilleur temps secteur 1 : %.3f | Pilote numéro %d\n", (tab[0].best_s1 / 1000), tab[0].id);
    qsort(tab, 20, sizeof(car), compare_sector2);
    printf("Meilleur temps secteur 2 : %.3f | Pilote numéro %d\n", (tab[0].best_s2 / 1000), tab[0].id);
    qsort(tab, 20, sizeof(car), compare_sector3);
    printf("Meilleur temps secteur 3 : %.3f | Pilote numéro %d\n", (tab[0].best_s3 / 1000), tab[0].id);

}



void grid(car f1[20]){
    int place = 1;
    printf(" ---------- GRID ----------\n");
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

void podium(car f1[20]){
    printf("-------- FIN ---------\n");
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

int file_erase()
{
    FILE* file = NULL;
    file = fopen("results.txt", "w");
    if (file != NULL)
    {
        fprintf(file, "Voici les résultats du Grand-Prix\n");
        fclose(file);
    } else {
        perror("open file");
    }
}


int file_print_essai1()
{
    FILE* file = NULL;
    file = fopen("results.txt", "a+");
    if (file != NULL)
    {
        fprintf(file, "\n------ ESSAIS 1 ------\n");
        fclose(file);
    } else {
        perror("open file");
    }
}

int file_print_essai2()
{
    FILE* file = NULL;
    file = fopen("results.txt", "a+");
    if (file != NULL)
    {
        fprintf(file, "\n------ ESSAIS 2 ------\n");
        fclose(file);
    } else {
        perror("open file");
    }
}

int file_print_essai3()
{
    FILE* file = NULL;
    file = fopen("results.txt", "a+");
    if (file != NULL)
    {
        fprintf(file, "\n------ ESSAIS 3 ------\n");
        fclose(file);
    } else {
        perror("open file");
    }

}

int file_print_qualif1()
{
    FILE* file = NULL;
    file = fopen("results.txt", "a+");
    if (file != NULL)
    {
        fprintf(file, "\n------ QUALIF 1 ------\n");
        fclose(file);
    } else {
        perror("open file");
    }

}

int file_print_qualif2()
{
    FILE* file = NULL;
    file = fopen("results.txt", "a+");
    if (file != NULL)
    {
        fprintf(file, "\n------ QUALIF 2 ------\n");
        fclose(file);
    } else {
        perror("open file");
    }

}

int file_print_qualif3()
{
    FILE* file = NULL;
    file = fopen("results.txt", "a+");
    if (file != NULL)
    {
        fprintf(file, "\n------ QUALIF 3 ------\n");
        fclose(file);
    } else {
        perror("open file");
    }

}

int file_print_race() {
    FILE *file = NULL;
    file = fopen("results.txt", "a+");
    if (file != NULL)
    {
        fprintf(file, "\n------ COURSE ------\n");
        fclose(file);
    } else {
        perror("open file");
    }

}




int file_print_column()
{
    FILE* file = NULL;
    file = fopen("results.txt", "a+");
    if (file != NULL)
    {
        fprintf(file,"Num\t|");
        fprintf(file,"S1\t|");
        fprintf(file,"S2\t|");
        fprintf(file,"S3\t|");
        fprintf(file,"Tour\t\t|");
        fprintf(file,"Meilleur tour\t|");
        fprintf(file,"Numéro tour\t|");
        fprintf(file,"Temps total\t|");
        fprintf(file,"Stand\t|");
        fprintf(file,"Sortie\n");
        fclose(file);
    } else {
        perror("open file");
    }


}
int file_print(car tab[20])
{
    FILE* file = NULL;
    file = fopen("results.txt", "a+");
    if (file != NULL)
    {
        for (int i = 0; i<20 ; i++)
        {
            fprintf(file, "%d\t|", tab[i].id);
            fprintf(file,"%.3f\t|", tab[i].s1 / (double)1000);
            fprintf(file,"%.3f\t|", tab[i].s2 / (double)1000);
            fprintf(file,"%.3f\t|", tab[i].s3 / (double)1000);
            fprintf(file,"%s\t|", time_format(tab[i].lap));
            fprintf(file,"%s\t|", time_format(tab[i].best_lap));
            fprintf(file,"%d\t\t|", tab[i].num_lap);
            fprintf(file,"%s\t|", time_format(tab[i].total));

            if (tab[i].pit == 1) {
                fprintf(file,"PIT\t|");
            }
            else {
                fprintf(file,"---\t|");
            }

            if (tab[i].out == 1) {
                fprintf(file,"DNF\t\n");
            }
            else {
                fprintf(file,"---\t\n");
            }
        }

        fclose(file);
    } else {
        perror("open file");
    }

}