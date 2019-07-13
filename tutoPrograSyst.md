# [Tutoriel Programmation Système](https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix/1513964-avant-propos)
## Définition: 
* [La programmation système sert à faire fonctionner le pc contrairement à la programmation d'application qui utilise seulement les fonctions du pc](https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix?status=published#/id/r-1514735)
 * *[La programmation système permet de créer des drivers, communiquer avec les périphériques, voire même créer un système d'exploitation !](https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix/1513964-avant-propos#/id/r-1514754)*
* On parle ici de couche logicielle et plus précisement de couche d'abstraction matérielle car les programmes de cette couche ont accès aux ressource matérielle du pc.
* C'est par le **noyau** qu'on passe pour demander (appels-système) des infos concernant les programmes de la couche d'abstraction matérielle.
## Première approche: *Les erreurs*
* Vu qu'on travaille avec l'os direct, on va faire face à beaucoupp d'erreur du coup la première étape est de gerer ces erreurs.
* ERRNO
    * utile quand on recoit -1 comme retour d'appel systeme (ça peut être autre que -1 voir doc appel sys)
    * Renvoi le code derreur (lié au descriptif string de l'erreur)
    * `#include <errno.h>`
    * `extern int errno;`
* perror("nomAppel")
    * renvoi nomAppel suivi du descriptif décrit par ERRNO
    * `#include <stdio.h>`
    * `if (fork() == -1) {perror("fork");}`
## PSEUDO-PARALELLISME
* Le micro-processeur va attribuer des ressources à plusieurs programmes en quelque millisecondes. Voila pourquoi user à l’impression que c’est effectué en même temps.
## UN PROGRAMME
C’est une suite d’instruction (statique) qui changent les valeurs des registre, de la pile, etc.
## UN PROCESSUS
C’est l’image des conséquences des instruction d’un programme à un certain moment (dynamique)
## PID: 
* n° de processus, unique dans le système (pour un moment donné)
* lors d’un fork, le père et le fils ont chacun un PID
* si on est dans le fils, le PID du père est le PPID
* Dans la table des processus: les PID (de 0 à 32768) sont attribué à la suite, mais après avoir atteint pid_max alors il recup les premiers process id mort entre temps
## ORGANISATION
Les programme initial lance le process (PID = 1) qui lance tout les autres (dont les démon qui tourne constamment pour offrir des services quand besoin est)
## ETAT
![etatProcess.PNG](etatProcess.PNG)
> zombie c’est quand le pere na pas fini
(du coup je sais que le pere peut lire son code avant le fils ce qui crée un zombie car le fils ne sais pas lire le retour du père ?)

* Dans la table des process, il y a un block (PCB) qui contient [les caractéristiques](https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix/1514339-les-processus#/id/r-1514901) utiles à la reprise de l'exécution d’un processus (d’un programme)
* `ps aux` sert a voir tout les process, détaillé, dont les démons du coup ya [ces infos](https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix/1514339-les-processus#/id/r-1514919)
## Création d'un nouveau processus
> :warning: PAS METTRE DE FORK DANS BOUCLE :warning:
* `#include <unistd.h>` indispensable pour la plupart des appels sys
* `fork()` 
  * Crée un process ayant le même code que l'appelant mais ayant une valeur de retour différente (0 pour le fils et PID du fils pour le père) ce qui permet d'executer des codes différents pour le père et le fils
    * alloue Control Block dans table process
    * copie PCB du père sauf PID et PPID
    * alloue PID au fils
    * associe code au p fils et attend que le fils demande la pile et seg donnée pour lui allouer
    * état du process = execution
      
  * Retourne pid_t qui est la valeur du pid si on des dans le fils (0) ou dans le pere (pid du fils) ou dans erreur (-1)
    * int
    * `#include <unistd.h>`
    * `#include <sys/types.h>`
    * `pid_t fork(void);`
    * `pid_t getpid(void);`
    * `pid_t getppid(void);`
    * `uid_t getuid(void);`
    * `gid_t getgid(void);`
  * [code complet](https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix/1514339-les-processus#/id/r-1514975)
  * [Résultat output](https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix/1514339-les-processus#/id/r-1514977)
  * `type nouvelle_variable = (type) ancienne_variable;` type pid_t pas affichable avec printf donc on converti pour pouvoir afficher avec "%d"
### Les processus peuvent se terminer de deux façon
1. `return` dans le main
2. `void exit(status);` qui permet de quitter le programme n'importe quand

**à la fin du programme `return` ou `exit()` on peut executer encore du code**
* `int atexit(void (*function) (void));` 
  * renvoi -1 si fct fail ou 0 si réussite
  * on peut enchainer les appel a atexit() et le retour des fct seront affichée en ordre inverse
* `int on_exit(void (*function) (int, void *), void *arg);`
  * renvoi -1 si fct fail ou 0 si réussite
  * 1er arg cest le code de retour correspondant a la terminsaison
  * 2eme arg est l'argument à passer à la fonction de terminaison (datas classment final ?)
## Synchronisation entre père et fils
* `pid_t wait(int *status);`
* renvoi PID du fils fini ou -1 si erreur
* bloque le père qui appelle tant que le fils na pas fini
* :warning: il faut mettre autant de `wait()` qu'il y a de fils
* [Dernier code complet](https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix/1514339-les-processus#/id/r-1515141) à ce moment je suis sensé savoir faire tourner deux voitures synchronisée et protegée des erreurs
## Rappel args je vais pas m'y attarder
## PATH
* contient les chemin vers excutable/script qui permet d'executer la commande
* `echo $Path`
> Je pense pas que c'est super utile malgré que ça permet de trouver les executable je vois pas pourquoi je devrais recup home ou pwd ou shell
## exec()
* `int execv(const char *path, char *const argv[]);`
* utile à changer le code source d'un programme (avec args) sans changer le PID
* [code complet](https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix/1514464-executer-un-programme#/id/r-1515257) qui sert à faire tourner le process fils qui analyse le disque et le pere qui affiche le texte qui confirme que c'est ok
## system()
* :warning: ***A NE JAMAIS UTILISER CAR FAILLE DE SECURITE IMPORTANTE***
* `int system(const char *command);`
* utile à changer le code source d'un programme (***sans*** args) sans changer le PID
### THREAD
> *Le thread principal* execute le main()
* C'est un processus mais en plus rapide et moins compliqué
* `#include <pthread.h>`
* `int pthread_create(pthread_t * thread, pthread_attr_t * attr, void *(*start_routine) (void *), void *arg);`
* `void pthread_exit(void *ret);`
* `int pthread_join(pthread_t th, void **thread_return);`
## MUTEX
> Si deux thread veulent acceder à la même *variable* (dans la mémoire partagée), il faut définir l'ordre de passage.
* le *muex* est une variable qui verouille la mem partagée
  * état `disponible`
  * état `verouillé`
  * Pour ces état doivent être accessible de n'importe où dans le programme donc on crée une struct:
  ```C
  typedef struct data {
    int var; //var glob ?
    pthread_mutex_t mutex; //verrouillé ou dispo
    } data;
  ```
  * Initialisation: `data new_data; new_data.mutex = PTHREAD_MUTEX_INITIALIZER;`
  * Verrou du matux: `int pthread_mutex_lock(pthread_mutex_t *mut);`
  * Deverrou: `int pthread_mutex_unlock(pthread_mutex_t *mut);`
  * Destruction mutex: `int pthread_mutex_destroy(pthread_mutex_t *mut);`
## CONDITIONS
* Défini *l'attente*. Qui s'arrete quand un autre thread valide la condition
* Initialisation: `pthread_cond_t nomCondition = PTHREAD_COND_INITIALIZER;`
* Attente grace au mutex: `int pthread_cond_wait(pthread_cond_t *nomCondition, pthread_mutex_t *nomMutex);`
* Réveil quand mutex libre: `int pthread_cond_signal(pthread_cond_t *nomCondition);`
* [code complet](https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix/1514567-les-threads#/id/r-1515355) Qui affiche un compteur qui augmente; en notifiant à chaque fois qu'on à depassé un seuil.
### COMMUNICATION INTER-PROCESSUS
## LES PIPES (tube)
* Canal de communication entre processus 
> il faut créer deux variable pour utiliser le tube: une qui lit et l'autre qui écrit dans le tube
* *L'entrée du tube* c'est celui qui écrit dans le tube
* *La sortie de tube* c'est celui qui lit dans le tube
* `int pipe(int descripteur[2]);` descripteur[0] = lecture, descripteur[1] = écriture
:warning: **Créer le tube avant le fork pour que les enfant ai accès au tube** :warning:
* ECRITURE: `ssize_t write(int entreeTube, const void *elementAEcrire, size_t nombreOctetsAEcrire);`
* LECTURE: `ssize_t read(int sortieTube, void *elementALire, size_t nombreOctetsALire);`
* FERMER (pour pas accès simultané au tube): `int close(int descripteur);`
* [code complet](https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix/1514724-les-tubes#/id/r-1515429) qui affiche toutes les étapes de la comm à travers le tube (fermeture entree sortie, pere envoi message, fils recoit et affiche)
### Lier le tube avec std in ou out au lieu de hardcoder l'es infos à lire ou écrire dans le code
* `int dup2(int ancienDescripteur, int nouveauDescripteur);`
### TUBES nommés
> On peut y acceder de partout dans le programme contrairement au tube simple qui établi un dialogue juste entre deux process
> :warning: le tube nommé est en fait un fichier 
> * renvoi -1 si fct fail ou 0 si réussite du errno peut [intervenir](https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix/1514724-les-tubes#/id/r-1515483)
* Création du fichers au nom et mode ouvertue 124:`int mkfifo (const char* nom, mode_t mode);`
  * exemple: 
  ```C
  if (mkfifo(("essai.fifo"), 0760) == -1)
  {
     fprintf(stderr, "Erreur de création du tube");
	  exit(EXIT_FAILURE);
  }
  ```
* Ouvrir le tube nommé: `int open (const char* cheminFichier, int options);`
  * exemple: `descripteur[1] = open("essai.fifo", O_WRONLY);`

## Écrivez deux programmes indépendants : un écrit un message dans un tube nommé, et l'autre le lit, puis l'affiche. Exécutez ces deux programmes en même temps.
* [code 1er prog](https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix/1514724-les-tubes#/id/r-1515508)
* [code 2eme prog](https://openclassrooms.com/fr/courses/1513891-la-programmation-systeme-en-c-sous-unix/1514724-les-tubes#/id/r-1515510)

> :point_right: Il nous reste encore à maîtriser les signaux, les sémaphores, et bien d'autres choses 
