# RETROSPECTIVE VERSION 2
## Combien de temps passé sur la version 2 ?
* du `Jul 11 2019 ` au `Jul 15 2019 ` c'est à dire en `5` jours.
### 1er jour: 
* `Projects`:
   * 11 juillet #25
   * 11 juillet #26
   * 11 juillet #27
* `DailyScrum`:
  * Readme f1
  * Backlog version 2 f1
  * Invit hymed et adrien


### 2eme jour: 
* `Projects`:
   * 12 juillet #30 
* `DailyScrum`:
  * Os théorie tuto jusqua process
  * Initiation à la gestion de projet à travers github et ses différents outils.

### 3eme jour: 
* `Projects`:
   * 13 juillet #31
   * 13 juillet #33
* `DailyScrum`:
  * Appris thread et tube en c
  * Test fork, ya bug

### 4eme jour: 
* `Projects`:
   * 14 juillet #35
   * 14 juillet #36
   * 14 juillet #38

* `DailyScrum`:
  * affiche un nbre dans pere et fils
  * affiche un nbre different dans pere et fils
  * affiche toute les stat pour chacune des deux voitures

### 5eme jour: 
* `Projects`:
   * 15 juillet #41
* `DailyScrum`:
  * Affiche les 20 voitures
  * Update backlog, rapport avancement et retrospective


## Objectif
### Quel est l'Objectif attendu ?
*Les 20 processus "voiture" qui affichent leurs stat respectif*


### Objectif atteint ?
***OUI***

***NOUS AVIONS ESTIME LA DUREE DE LITERATION A 8 JOURS ET NOUS AVONS REUSSIS EN 5 PETITS JOURS***

* Nous avons du nous rappeler le mecanisme du fork
* Nous avons implementé un fork de test
* Nous avons inséré le code daffichage des stat dans les 2 process créé
* Nous avons mis en place un mécanisme qui nous permet dafficher tout les tour de chaque voiture 

Ambroise pensait à ceci: 

num|s1|s2|s3|tour  |bestour|pit|out|numTour|Tot
---|--|--|--|------|-------|---|---|-------|---
1  |35|41|37|1min53|1min53 |0  |0  |1      |1min53
2  |38|40|38|1min56|1min56 |0  |0  |1      |1min56
3  |38|40|37|1min55|1min55 |0  |0  |1      |1min55
4  |38|35|41|1min54|1min54 |0  |0  |1      |1min54
5  |40|35|39|1min54|1min54 |0  |0  |1      |1min54
... JUSQUA 20

***Mais nous nous sommes rendu compte que cela nous amenerais des problèmes complexe prématurément. Nous prenons soin de construire le projet en version et cette représentation correspond plutôt à l'affichage final que l'affichage de test de 20 voiture sans aucun tri ni autre fonctionnalités particulière***

## OUTILS
### GITHUB
> **Branche:** J'ai défini la structure de l'arbre tel qu'il a un tronc `master`, des branches `version` qui ont des branches `nom_de_la_fonction`.

***EDIT: Au début ça prend du temps pour s'accomoder mais une fois que c'est fait, cela nous est grandement utile pour coopérer à distance***
> * **master**: c’est les fichiers qui reprennent que les versions reviewée completement. Avant de merge, on discute pour voir si il y à encore des éléments à revoir et on documente un maximum.

***EDIT: Nous n'utilisons la branche master seulement pour y mettre du code propre et cela fonctionne bien pour le moment***
> *  **version X**: c’est la Xème version sur laquelle on veut chaque fonctionnalité proprement écrite. C’est donc sur celle la qu’on crée des branche et qu’on les merge.

***EDIT: Nous avons l'habitude d'avoir au moins une pull request correspondant a la version actuelle sur laquelle nous travaillons. Nous y définissons l'objectif pour pouvoir merge cette branche et passer à la prochaine version. Avant de la merge, nous discutons sur l'avancement du projet, notre méthodologie, etc.***
> * **username-nom_fc**t: Pour chaque fonctionnalité, on crée une branche avec une pull request qui précise le résultat attendu pour merge. On travaille dans la branche puis on demande des reviews pour merge avec version. 

***EDIT: Nous n'avons aucun mal à suivre cette structure et nous avons même du plaisir à la suivre car elle nous permet de nous focaliser sur *une fonctionnalité à la fois*.***
> ⚠️ Ajouter les cartes dans les tableaux `Projects` (voir plus bas)
> --> J'ai l'habitude d'aller regarder dans `insight` dans `network`

***EDIT: L'ajout de carte est une très bonne habitude car elle nous permet, à la fin d'une itération, de voir notre progression sous forme de petites entités qui sont "les brique des notre mur"***
> **Pull Request:** Il faut en créer une directement quand on commence à travailler sur un code pour que les contributeurs puisse interagir et collaborer. Avec le sytème de Kaban automatique, toutes les pull request sont des cartes qui sont mise dans la colonne `en progression` du tableau `avancement du projet` à condition qu'on sélectionne le tableau dans la sidebar de la pull request. Si on n'a pas sélectionné le tableau, on peut toujours aller dans `Projects` et drag drop la carte qui par contre est d'office en suggestion si il s'agit d'une pull request.

***EDIT: Nous créons systématiquement une pull request dès la création d'une nouvelle branche pour garder à l'esprit que nous voulons fusionner au plus vite avec la branche mère et aussi surtout pour pouvoir alimenter la discution de screenshot, historique de commit, commentaire, reflexion et toute sorte d'informations concernant la branche (la fonctionnalité)***
> **Issues:** Il faut en créer une directement quand on commence à bloquer trop longtemps sur un code pour que les contributeurs puisse interagir et collaborer. Avec le sytème de Kaban automatique, toutes les Issues sont des cartes qui sont mise dans la colonne `à faire` du tableau `avancement du projet` et `besoin de tri` dans `Gestion des bugs` à condition qu'on sélectionne le/les tableau dans la sidebar de l'Issue. Si on n'a pas sélectionné le tableau, on peut toujours aller dans `Projects` et drag drop la carte qui par contre est d'office en suggestion si il s'agit d'une Issue.

***EDIT: Nous ne sommes pas vraiment encore familier avec le système des issues.***
> **Merge:** On merge ce qu'on veut sur les branches commençant par un username. On ne merge que des codes fonctionels, testés et commenté sur version et enfin on ne merge aucune version tant que le groupe n'est pas d'accord sur la fusion. Les merges sont aussi des cartes qui viennent se positionner dans `Fini` pour que nous puissions observer l'avancement du projet facilement. (Les issues aussi viennent dans `Fini` jpense)
> --> *si on ferme pas la branche* il y aura juste le nom qui sera encore affiché sur l'arbre dans `network` dans `insight`

***EDIT: les merge représentent la vraie valeur de notre projet. C'est ce que nous avons appris jsuqu'a maintenant.***
> **Projects:** J'ai crée deux tableaux qui vise à nous synchroniser et nous donner une vision d'ensemble.
> * Avancement du projet:

> à faire|en progression|en validation|fini
> -------------|---|----|---
>eventuel bug|pull request|pull request??|merge

> * Gestion des bugs:

> à trier|haute importance|faible importance|fini
> -------------|---|----|---
>eventuel bugz|bugz|bugz|merge?

***EDIT: Pour le moment l'onglet Projects ne nous est utile quasi que pour voir l'avancement du projet et pouvoir entreprendre plus facilement une réflexion rétrospective sur le travail fourni***
### GOOGLE DRIVE - DOCS etc.
> **JournalDeBord:** C'est un fichier google docs qui m'aide surtout à commencer un projet car je note ce que je compte faire puis je le fais et je commente avec screenshot ou code pour garder une petite trace de mes reflexions sans devoir les structurer

***EDIT: Effectivement, maintenant que je comprend mieux github, je l'utilise comme journal de bord ou mes commits sont mes tests et dans la pull request je met mes reflexion etc.***
> **Backlog:** C'est un fichier qui vise à décomposer un problème complexe en tâches faisable. Il respecte la structure suivante: 

>  :octocat:  |   :octocat: | :octocat: 
> ---------|-------------|-----------

***EDIT: Nous ne consultons pas très souvent ce fichier mais il nous est d'une aide précieuse lors du passage d'une version à l'autre pour organiser les itérations.***
> **Rapport d'avancement**|Cette section est dépendante du release backlog car elle contient la liste des chose à faire pour une version mais de façon encore plus décomposée. | 👍 

***EDIT: J'ai décidé de déplacer cette partie dans un fichier à part car ce rapport est une liste brouillon de chose à faire et principalement faite. Non pas une infos pertinente concernant le futur du projet***
> **Sprint Backlog**|Cette section est dépendante du release backlog car elle contient la liste des caractéristiques de la version que l'on veut produire. C'est, en général, de cette section que proviennent le nom des différentes branches de la version en cours.| :arrow_heading_up:

***EDIT: Je n'ai pas eu une estimation réaliste de cette itéaration. Je pensais que nous devions traiter obligatoirement les fork, mem partagée et semaphore en même temps alors que la première étape ètait déjà de simplement avoir 20 processus. Et puis seulement traiter les infos renvoyées par ces processus***
> **Release Backlog**|Cette section est dépendante du product backlog car elle contient la liste du product que l'on va décomposer en version avec un bref cadre des attentes à satisfaire à la fin de chaque version. Elle est pourtant écrite au dessus car nous voulons mettre les infos les plus simple au début du doc pour y accéder facilement.| :arrow_heading_up:
> **Product Backlog**|C'est la premiere section créée. On y insère les infos globales pour déjà former une liste des attentes qu'il faudra satisfaire. Il s'agit ici de se mettre dans la peau du client et visualiser le résultat attendu: cela aidera à sélectionner les priorités !| :arrow_heading_up:

> :warning: ***Nous voulons mettre les infos les plus simple au début du doc pour y accéder facilement et les plus complexe à la fin pour quand même pouvoir y jeter un coup d'oeil, histoire de vérifier qu'on suit bien la vision du projet.***

> **DailyScrum:** C'est un fichier que je rempli tout les matins en répondant aux questions:
> * Qu'ai-je fais hier ?
> * Que vais-je faire aujourd'hui ?
> * Qu'est-ce qui me bloque ?

***EDIT: Ceci m'est extremement utile. Je sais quoi faire, quand le faire et surtout comment ne pas stagner car je peut voir la différence entre ce que j'ai prévu aujourd'hui et ce que j'ai effectivement fait aujourd'hui***
> **Amélioration:** C'est un fichier dans lequel j'écrit toute mes idées d'amélioration.

***EDIT: Nous n'avons pas eu besoin d'un tel fichier jusqu'a maintenant***
### DISCORD
> **Horodateur:** Mon bot enregistre le debut et la fin de chaque session de travail pour pouvoir recup les stat par après (maintenant typiquement)
> **DailyScrum:** Mon bot enregistre les taches du jour et me montrera la diff entre ce que j'avais prévu ajd et ce que j'ai effectivement fait hier pour à chaque fois pouvoir rectifier ses estimations
