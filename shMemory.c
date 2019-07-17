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

#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSZ 1024

int compteurVoiture=5;
int cpt = 0;


void father_process(int child_pid) {

    int shmid;
    key_t key;
    char *shm, *s;

    key = 5678;

    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    for (s = shm; *s != NULL; s++)
        putchar(*s);
    putchar('\n');

    *shm = '*';

    exit(0);
}

void child_process() {
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    key = 5678;

    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }



    s = shm;

    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = NULL;

    while (*shm != '*')
        sleep(1);

    exit(0);
}

int main() {
       pid_t pid;
       pid = fork();


       sleep(2);

       while ((pid == -1) && (errno == EAGAIN));

       if (pid == 0) {
           child_process();
           cpt++;
           exit(0);
       } else {
           father_process(pid);
           sleep(1);
       }
}

