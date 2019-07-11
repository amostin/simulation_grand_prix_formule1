# RETROSPECTIVE VERSION 1
## Combien de temps passé sur la version 1 ?
* *Toute session confondues:* `1 jour 10 heure 45 minute 19 seconde` dans la période du `Jul 07 2019 16:37:23` au `Jul 10 2019 13:23:07` c'est à dire en `4` jours.
### 1er jour: 
* `Projects`:
   * 8 juillet 01:25 #5
   * 8 juillet 13:00 #12 
   * 8 juillet 21:50 #13
* `DailyScrum`:
  * Appris gihub branche, projects,..
  * Backlog os tp fini
  * Installer clion
  * Fct random 
  * fct affichage 

### 2eme jour: 
* `Projects`:
   * 9 juillet 03:54 #14 
   * 9 juillet 16:37 #19 
   * 9 juillet 14:30 #15  
* `DailyScrum`:
  * Calcul tour
  * Conv sec minsec
  * Ecrire fichier
  * Gerer argc argv

### 3eme jour: 
* `Projects`:
   * 10 juillet 03:00 #20
   * 10 juillet 04:00 #21 
   * 10 juillet 05:00 #22 
* `DailyScrum`:
  * Verifier les commentaires
  * Ecrire nouveau backlog
  * Ecrire nouveau readme
  * Merge version1 et master
  * Inviter les contributeurs
  * Faire les forks?

## Objectif
### Quel est l'Objectif attendu ?
> Pas de tri, ni de shmem ou sem. On veut juste des temps bien affichés pour une seule voiture.
* générer s1, s2, s3, (s1+s2+s3) pit out
* les convertir au format human readable
* les afficher dans un tableau
* rendre le tableau dynamique pour afficher les résultat dune seule voiture
* stocker les résultat

### Objectif atteint ?
* OUI, En plus on à atteint des objectifs imprévus:
  * être à l'aise avec github
  * être à l'aise avec l'IDE

## OUTILS
### GITHUB
> **Branche:** J'ai défini la structure de l'arbre tel qu'il a un tronc `master`, des branches `version` qui ont des branches `nom_de_la_fonction`.
> * **master**: c’est les fichiers qui reprennent que les versions reviewée completement. Avant de merge, on discute pour voir si il y à encore des éléments à revoir et on documente un maximum.
> *  **version X**: c’est la Xème version sur laquelle on veut chaque fonctionnalité proprement écrite. C’est donc sur celle la qu’on crée des branche et qu’on les merge.
> * **username-nom_fc**t: Pour chaque fonctionnalité, on crée une branche avec une pull request qui précise le résultat attendu pour merge. On travaille dans la branche puis on demande des reviews pour merge avec version. 

> ⚠️ Ajouter les cartes dans les tableaux `Projects` (voir plus bas)
> --> J'ai l'habitude d'aller regarder dans `insight` dans `network`

> **Pull Request:** Il faut en créer une directement quand on commence à travailler sur un code pour que les contributeurs puisse interagir et collaborer. Avec le sytème de Kaban automatique, toutes les pull request sont des cartes qui sont mise dans la colonne `en progression` du tableau `avancement du projet` à condition qu'on sélectionne le tableau dans la sidebar de la pull request. Si on n'a pas sélectionné le tableau, on peut toujours aller dans `Projects` et drag drop la carte qui par contre est d'office en suggestion si il s'agit d'une pull request.

> **Issues:** Il faut en créer une directement quand on commence à bloquer trop longtemps sur un code pour que les contributeurs puisse interagir et collaborer. Avec le sytème de Kaban automatique, toutes les Issues sont des cartes qui sont mise dans la colonne `à faire` du tableau `avancement du projet` et `besoin de tri` dans `Gestion des bugs` à condition qu'on sélectionne le/les tableau dans la sidebar de l'Issue. Si on n'a pas sélectionné le tableau, on peut toujours aller dans `Projects` et drag drop la carte qui par contre est d'office en suggestion si il s'agit d'une Issue.

> **Merge:** On merge ce qu'on veut sur les branches commençant par un username. On ne merge que des codes fonctionels, testés et commenté sur version et enfin on ne merge aucune version tant que le groupe n'est pas d'accord sur la fusion. Les merges sont aussi des cartes qui viennent se positionner dans `Fini` pour que nous puissions observer l'avancement du projet facilement. (Les issues aussi viennent dans `Fini` jpense)
> --> *si on ferme pas la branche* il y aura juste le nom qui sera encore affiché sur l'arbre dans `network` dans `insight`

> **Projects:** J'ai crée deux tableaux qui vise à nous synchroniser et nous donner une vision d'ensemble.
> * Avancement du projet:

> à faire|en progression|en validation|fini
> -------------|---|----|---
>eventuel bug|pull request|pull request??|merge

> * Gestion des bugs:

> à trier|haute importance|faible importance|fini
> -------------|---|----|---
>eventuel bugz|bugz|bugz|merge?
### GOOGLE DRIVE - DOCS etc.
> **JournalDeBord:** C'est un fichier google docs qui m'aide surtout à commencer un projet car je note ce que je compte faire puis je le fais et je commente avec screenshot ou code pour garder une petite trace de mes reflexions sans devoir les structurer

> **Backlog:** C'est un fichier qui vise à décomposer un problème complexe en tâches faisable. Il respecte la structure suivante: 

>  :octocat:  |   :octocat: | :octocat: 
> ---------|-------------|-----------
> **Rapport d'avancement**|Cette section est dépendante du release backlog car elle contient la liste des chose à faire pour une version mais de façon encore plus décomposée. | 👍 
> **Sprint Backlog**|Cette section est dépendante du release backlog car elle contient la liste des caractéristiques de la version que l'on veut produire. C'est, en général, de cette section que proviennent le nom des différentes branches de la version en cours.| :arrow_heading_up:
> **Release Backlog**|Cette section est dépendante du product backlog car elle contient la liste du product que l'on va décomposer en version avec un bref cadre des attentes à satisfaire à la fin de chaque version. Elle est pourtant écrite au dessus car nous voulons mettre les infos les plus simple au début du doc pour y accéder facilement.| :arrow_heading_up:
> **Product Backlog**|C'est la premiere section créée. On y insère les infos globales pour déjà former une liste des attentes qu'il faudra satisfaire. Il s'agit ici de se mettre dans la peau du client et visualiser le résultat attendu: cela aidera à sélectionner les priorités !| :arrow_heading_up:

> :warning: ***Nous voulons mettre les infos les plus simple au début du doc pour y accéder facilement et les plus complexe à la fin pour quand même pouvoir y jeter un coup d'oeil, histoire de vérifier qu'on suit bien la vision du projet.***

> **DailyScrum:** C'est un fichier que je rempli tout les matins en répondant aux questions:
> * Qu'ai-je fais hier ?
> * Que vais-je faire aujourd'hui ?
> * Qu'est-ce qui me bloque ?

> **Amélioration:** C'est un fichier dans lequel j'écrit toute mes idées d'amélioration.
### DISCORD
> **Horodateur:** Mon bot enregistre le debut et la fin de chaque session de travail pour pouvoir recup les stat par après (maintenant typiquement)
> **DailyScrum:** Mon bot enregistre les taches du jour et me montrera la diff entre ce que j'avais prévu ajd et ce que j'ai effectivement fait hier pour à chaque fois pouvoir rectifier ses estimations
