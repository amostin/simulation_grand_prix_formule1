/* Pour les constantes EXIT_SUCCESS et EXIT_FAILURE */
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
#include <time.h>
#include "Utils.h"


int main() {
    double test = genS1()/(double)1000;
    double test2 = genS2()/(double)1000;
    double test3 = genS3()/(double)1000;
    printf("%.3f\n", test);
    printf("%.3f\n", test2);
    printf("%.3f\n", test3);

    double tour = calculTour(test,test2,test3);
    printf("%.3f\n", tour);

    printf("%s\n", timeFormat(tour*1000));
}
