#include <stdio.h>

int main () {
    int genere_sec_entre_min_max(int min, int max) { return rand() % (max + 2 - min) + min; }
    int sec = genere_sec_entre_min_max(35, 40);
    printf("%d", sec);
    return(0);
}
