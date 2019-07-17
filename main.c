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

    struct shmid_ds shmid_ds, *buf;
    buf = & shmid_ds;

    /* ACCES EN LECTURE */
    printf ("\nThe USER ID = %d\n", buf->shm_perm.uid);

}


void child_process(){

    printf("fils dis ya\n");

    struct shmid_ds shmid_ds, *buf;
    buf = & shmid_ds;
    int nbre_a_partager = 1248;

    /* ACCES EN ECRITURE */

    buf->shm_perm.uid = nbre_a_partager;
}


int main () {
    /* SHARED MEMORY */

    int shmid;
    key_t key;
    key = 5678;

    struct shmid_ds shmid_ds, *buf;
    buf = & shmid_ds;

    //char phrase_a_partager[] = "je suis écrit par le pere";
    int nbre_a_partager = 1248;


    //On crée le segment de memoire qui est identidié par shmid
    if ((shmid = shmget(key, sizeof(nbre_a_partager), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    //on s'attache au segment pour après pouvoir le manipuler
    shmat(shmid, NULL, 0);

    /* on essaie d'acceder au seg de mem partagée et on indique erreur si ya */
    if (shmctl(shmid, IPC_STAT , buf) == -1) {
        perror("acces a shared mem : ");
        exit(1);
    }

    /* ACCES EN LECTURE */

    printf ("\nThe USER ID = %d\n", buf->shm_perm.uid);
    printf ("The GROUP ID = %d\n",buf->shm_perm.gid);
    printf ("The creator's ID = %d\n",buf->shm_perm.cuid);
    printf ("The creator's group ID = %d\n",buf->shm_perm.cgid);
    printf ("The operation permissions = 0%o\n",buf->shm_perm.mode);
    printf ("The slot usage sequence\n");
    //printf ("number = 0%x\n",buf->shm_perm.seq);
    //printf ("The key= 0%x\n",buf->shm_perm.key);
    //printf ("The segment size = %d\n",buf->shm_segsz);
    printf ("The pid of last shmop = %d\n", buf->shm_lpid);
    printf ("The pid of creator = %d\n", buf->shm_cpid);
    //printf ("The current # attached = %d\n",buf->shm_nattch);
    printf ("The last shmat time = %ld\n",buf->shm_atime);
    printf ("The last shmdt time = %ld\n",buf->shm_dtime);
    printf ("The last change time = %ld\n", buf->shm_ctime);






    /* détachement du segment */

    if (shmctl(shmid, IPC_RMID, (struct shmid_ds *) NULL) == -1) {
        perror("detachement : ");
        exit(1);
    }

    /*Lock the shared memory segment*/

    if (shmctl(shmid, SHM_LOCK, (struct shmid_ds *) NULL) == -1) {
        perror("lock : ");
        exit(1);
    }

    /*Unlock the shared memory segment.*/

    if (shmctl(shmid, SHM_UNLOCK, (struct shmid_ds *) NULL) == -1) {
        perror("lock : ");
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