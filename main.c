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

    int shmid;
    key_t key;
    key = 5678;
    struct shmid_ds shmid_ds, *buf;
    buf = & shmid_ds;
    int nbre_a_partager = 1248;
    if ((shmid = shmget(key, sizeof(nbre_a_partager), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    shmat(shmid, NULL, 0);

    /* ACCES EN LECTURE */

}


void child_process(){

    printf("fils dis ya\n");


}


int main () {
    /* SHARED MEMORY */

    /* variable qui contiendra l'id du segment de memoire paratgée */
    int shmid;
    key_t key;
    key = 5678;
    //structVoiture *buf;


    structVoiture *shm;

    structVoiture car = {0,0,0,0,0,0,999,0,0,0};
    shm = &car;

    int nbre_a_partager = 163264;
    if ((shmid = shmget(key, sizeof(int), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    shmat(shmid, NULL, 0);

    /* ACCES EN ECRITURE */
    shm->id = nbre_a_partager;

    /* TEST */
    printf ("The voiture.id = %d\n",shm->id);





    /*
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
*/





    /* déstruction du segment */

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

        shmat(shmid, NULL, 0);

        /* ACCES EN LECTURE */
/*
        printf("\nprocess main a la fin execution\n");
        printf ("\nThe USER ID = %d\n", buf->shm_perm.uid);
        printf ("The last shmdt time = %ld\n",buf->shm_dtime);
*/
    }

}