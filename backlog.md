# rapport d’avancement

- [x] J’ai créé un fichier qui reprend les demandes du client et me permet de les décomposer en tâches à faire.
- [x] J’ai appris à utiliser les projets github.
- [x] J’ai appris à utiliser les branches et les pull request et les issues 
- [x] J’ai créé un repo github avec un projet contenant un tableau kaban et un tableau de gestion de bug 
- [x] J’ai pris les consignes et créé le product backlog 
- [x] Créer le release backlog 
- [x] Créer le sprint backlog 
- [x] Je sais manier CLion
- [x] Je sais coder un main.c puis le compiler et l’executer
- [x] Je sais générer un nombre aléatoire différent à chaque exécution du programme
- [x] Je sais sortir le code du main pour le mettre dans une fonction
- [x] Je sais appeler la fonction plusieurs fois pour faire des tests de cas particuliers
- [x] je sais afficher les titre et valeur dans afficheur
- [x] je sais ecrire le tableau dans un fichier
- [x] je sais calculer laddition des secteurs
- [x] je sais convertir des sec en minsec
- [x] je sais rafraichir la console pour afficher en continu
- [x] je sais generer des pit et out aleatoire avec respectivement 10% et 5% de chance
- [x] le code de la version 1 est entièrement commenté
- [x] j’ai validé ma structure de flux de travail
- [x] j'ai édité le readme pour expliquer les démarches que j'ai l'habitude d'entreprendre pour contribuer au projet
- [x] j'ai établi un rapport de reflexion retrospective sur la version 1
- [x] j'ai créé le backlog pour la version 2
- [x] j'ai merge master avec la version 1
- [x] j'ai créé la branche version 2 avec une pull request citant le sprint backlog



# sprint backlog
> fin estimée au 18/07/2019
### fork pour avoir un process afficheur et 20 pour voiture
* rappel fork()
    * afficher 21 ou 22 fois "une chaine"
* afficher un seul nbre generé pour chaque process 
* afficher la ligne entière pour chaque process 
### stocker les infos generée par tout les process dans mem partagée
> tâches à déterminer
### tester la mem partagée et l'ajuster avec des semaphores
> tâches à déterminer
### afficher le tableau avec les 20 temps
> tâches à déterminer


# release backlog
## Version 1:
> Pas de tri, ni de shmem ou sem. On veut juste des temps bien affichés pour une seule voiture.
- [x] générer s1, s2, s3, (s1+s2+s3) pit out
- [x] les convertir au format human readable
- [x] les afficher dans un tableau
- [x] rendre le tableau dynamique pour afficher les resultat dune seule voiture
- [x] stocker les résultats

## Version 2:
> on veut la même chose que la version 1 mais pour 20 voitures
* fork pour avoir un process afficheur et 20 pour voiture
* stocker les infos generée par tout les process dans mem partagée
* tester la mem partagée et l'ajuster avec des semaphores
* afficher le tableau avec les 20 temps 

## Version 3:
> Tri synchrone et classement finaux stocké
* classement selon tour complet, pit, out
* stocker le best time tout le temps
* (Q) éliminer 5 puis 5 puis classer dans l'ordre pour départ finale.
* écrire les résultats (PQF) dans un fichier
> affichage: 
> * voiture|s1|s2|s3|besttime|pit|out 
> * trié constamment pour que les meilleurs temps soit en haut
> * n’affiche plus de temps si il est out ou pit. Remettre la voiture à sa place dès son retour du pit

## Version 4:
* écriture d’un makefile
* écriture doc, rapport
* perfectionner le code en le paramétrant et refactor

# product backlog
## Concrètement, on veut:
* un afficheur qui montre voiture|s1|s2|s3|tot|...
* 20 voitures qui génèrent des temps aléatoires de +/- 40sec/secteur, 2-3 pit, 2-3 crash
* 3 Périodes d’essai (P) dont la dernière (P3) détermine l'ordre de départ des Q
* 3 Qualifications (Q) 
    * où les 5 derniers de Q1 sont OUT et dernier du tableau (16-20)
    * les 5 derniers de Q2 aussi (11-15)
    * et enfin la Q3 sert à déterminer le classement de départ de F
* la course finale (F)

## Fonctionnalités:
* Pour P et Q: 
    * générer s1, s2, s3
    * classement selon tour complet (s1+s2+s3)
    * stocker le best time tout le temps
    * générer un pit (garde temps et classement)
    * générer un out (garde temps et classement)
    * (Q) éliminer 5 puis 5 puis classer dans l'ordre pour départ finale.
    * Stocker classement final du 3 et tour plus rapide
* affichage: 
    * voiture|s1|s2|s3|besttime|pit|out 
    * trié constamment pour que les meilleurs temps soit en haut
    * n’affiche plus de temps si il est out ou pit. Remettre la voiture à sa place dès son retour
    * écrire les résultats (PQF) dans un fichier

## Implémentation obligatoire
* Utiliser la mémoire partagée comme moyen de communication inter-processus
> Soit un père afficheur qui crée des fils qui génèrent les temps, pit et out. Soit un process crée les voitures et l'afficheur.
* Utiliser les sémaphores pour synchroniser l’accès à la mémoire partagée
> le père doit prendre les infos des fils dans la mémoire partagée mais il faut pas qu’il y ait de conflit. 
> //paramétrer le programme pour insérer les options voulue (le nombre de tour car le circuit peut être +/- long)

## Finitions
* un makefile qui compile le code
* une documentation riche
