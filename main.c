#include <stdio.h>
#include "utilsProjet.h"
#include <ctype.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <string.h>





void father_process(int child_pid) {

    printf("papa dit yo\n");
}


void child_process(){

    printf("fils dis ya\n");
}


int main () {


    /* SHARED MEMORY */

    int shmid;
    //char shm[];
    key_t key;
    key = 5678;

    struct shmid_ds *buf = NULL;

    char phrase_a_partager[] = "je suis écrit par le pere";

    if ((shmid = shmget(key, sizeof(phrase_a_partager), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if (shmat(shmid, NULL, 0) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    if (shmctl(shmid, IPC_STAT , buf) == -1) {
        perror("shmat");
        exit(1);
    }


    /* FORK */

    pid_t pid;
    pid = fork();

    sleep(2);


    while ((pid == -1) && (errno == EAGAIN));

    //ici on est dans le fils
    if (pid == 0) {
        child_process();
        exit(0);

        //ici on est dans le père
    } else {
        father_process(pid);
        sleep(2);

    }

}