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
//Pour éviter implicit declaration of function invalid in C99
//int genere_sec_entre_min_max(int min, int max);
//fct qui prend deux nbre en entrée et retourne  un nbre entre les deux entrés. attention lors des tests il renvoi meme un nombre au dessus du max
int genere_sec_entre_min_max(int min, int max) {
    //un temps aléatoire
    //time_t t;
    //generation d'un nouveau nbre aleatoire parce que sinon ya que le premier qui est aleatoire puis le reste est le meme
    //srand((unsigned) time(&t));
    //le % defini le max puis le calcul defini le min
    int sec = rand() % (max + 2 - min) + min;
    //affiche le nombre contenu dans sec
    //printf("%d", sec);
    //retourne le chiffre aléatoire entre min et max
    return sec;
}

/* La fonction create_process duplique le processus appelant et retourne
   le PID du processus fils ainsi créé */
pid_t create_process(void)
{
    /* On crée une nouvelle valeur de type pid_t */
    pid_t pid;

    /* On fork() tant que l'erreur est EAGAIN */
    do {
        pid = fork();
    } while ((pid == -1) && (errno == EAGAIN));

    /* On retourne le PID du processus ainsi créé */
    return pid;
}

/* La fonction child_process effectue les actions du processus fils */
void child_process(void)
{
    //on initialise le random pour chaque process
    srand(getpid());
    printf(" Nous sommes dans le fils !\n"
           " Le PID du fils est %d.\n"
           " Le PPID du fils est %d.\n", (int) getpid(), (int) getppid());
    //laisse le temps pour kill pid dans un autre terminal jle laisse au cas où ça serait utile
    //sleep(20);
    /*if (genere_sec_entre_min_max(minimum, maximum) > maximum){
        printf("Secteur 1: %d\n", (genere_sec_entre_min_max(minimum, maximum)-1));
    } else if (genere_sec_entre_min_max(minimum, maximum) < minimum){
        printf("Secteur 1: %d\n", (genere_sec_entre_min_max(minimum, maximum)+1));
    } else {
        printf("Secteur 1: %d\n", genere_sec_entre_min_max(minimum, maximum));
    }*/
    printf("Secteur 1: %d\n", genere_sec_entre_min_max(minimum, maximum));
    printf("Secteur 2: %d\n", genere_sec_entre_min_max(minimum, maximum));
    printf("Secteur 3: %d\n", genere_sec_entre_min_max(minimum, maximum));
}

/* La fonction father_process effectue les actions du processus père */
void father_process(int child_pid)
{
    //indique l'etat si error ou terminaison normale
    int status;
    //on initialise le random pour chaque process
    srand(getpid());

    printf(" Nous sommes dans le père !\n"
           " Le PID du fils est %d.\n"
           " Le PID du père est %d.\n", (int) child_pid, (int) getpid());
    printf("Secteur 1: %d\n", genere_sec_entre_min_max(minimum, maximum));
    printf("Secteur 2: %d\n", genere_sec_entre_min_max(minimum, maximum));
    printf("Secteur 3: %d\n", genere_sec_entre_min_max(minimum, maximum));


    if (wait(&status) == -1) {perror("wait :");exit(EXIT_FAILURE);}
    if (WIFEXITED(status)) {printf(" Terminaison normale du processus fils.\n Code de retour : %d.\n", WEXITSTATUS(status));}
    if (WIFSIGNALED(status)) {printf(" Terminaison anormale du processus fils.\n Tué par le signal : %d.\n", WTERMSIG(status));}
}

int main(void)
{
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