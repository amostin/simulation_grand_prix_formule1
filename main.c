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

// variable globale pour pouvoir changer changer l'intervalle facilement
int minimum = 35;
int maximum = 40;
//compteur pour les differentes voitures
int num = 1;

//fct qui prend deux nbre en entrée et retourne  un nbre entre les deux entrés. attention lors des tests il renvoi meme un nombre au dessus du max
int genere_sec_entre_min_max(int min, int max) {
    //le % defini le max puis le calcul defini le min
    int sec = rand() % (max + 2 - min) + min;
    //retourne le chiffre aléatoire entre min et max+1
    return sec;
}

/* La fonction create_process duplique le processus appelant et retourne
   le PID du processus fils ainsi créé */
pid_t create_process(void){
    /* On crée une nouvelle valeur de type pid_t */
    pid_t pid;
    /* On fork() tant que l'erreur est EAGAIN */
    do {pid = fork();} while ((pid == -1) && (errno == EAGAIN));
    /* On retourne le PID du processus ainsi créé */
    return pid;
}

/* La fonction father_process effectue les actions du processus père */
void father_process(int child_pid){
    //indique l'etat si error ou terminaison normale
    int status;
    //on initialise le random pour chaque process
    srand(getpid());
    printf(" Nous sommes dans le père !\n");

    char titres_colonnes[] = "num|s1|s2|s3|tour  |bestour|pit|out|numTour|Tot\n";
    char separateur_titres_valeurs[] = "---|--|--|--|------|-------|---|---|-------|---\n";

    int s1 = genere_sec_entre_min_max(minimum, maximum);
    int s2 = genere_sec_entre_min_max(minimum, maximum);
    int s3 = genere_sec_entre_min_max(minimum, maximum);

    printf("%s", titres_colonnes);
    printf("%s", separateur_titres_valeurs);
    printf("%d  |%d|%d|%d|\n", num, s1, s2, s3);

    if (wait(&status) == -1) {perror("wait :");exit(EXIT_FAILURE);}
    if (WIFEXITED(status)) {printf(" Terminaison normale du processus fils.\n Code de retour : %d.\n", WEXITSTATUS(status));}
    if (WIFSIGNALED(status)) {printf(" Terminaison anormale du processus fils.\n Tué par le signal : %d.\n", WTERMSIG(status));}
}

/* La fonction child_process effectue les actions du processus fils */
void child_process(void){
    //on initialise le random pour chaque process
    srand(getpid());
    printf(" Nous sommes dans le fils !\n");

    char titres_colonnes[] = "num|s1|s2|s3|tour  |bestour|pit|out|numTour|Tot\n";
    char separateur_titres_valeurs[] = "---|--|--|--|------|-------|---|---|-------|---\n";

    num++;
    int s1 = genere_sec_entre_min_max(minimum, maximum);
    int s2 = genere_sec_entre_min_max(minimum, maximum);
    int s3 = genere_sec_entre_min_max(minimum, maximum);

    printf("%s", titres_colonnes);
    printf("%s", separateur_titres_valeurs);
    printf("%d  |%d|%d|%d|\n", num, s1, s2, s3);
}

int main(void){
    pid_t pid = create_process();

    switch (pid) {
        /* Si on a une erreur irrémédiable (ENOMEM dans notre cas) */
        case -1:
            perror("fork");
            return EXIT_FAILURE;
            break;
            /* Si on est dans le fils */
        case 0:
            child_process();
            break;
            /* Si on est dans le père */
        default:
            father_process(pid);
            break;
    }

    return EXIT_SUCCESS;
}