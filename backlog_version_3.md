# sprint backlog
## sprint 2
> fin estimée au 2/8/2019
* implementer les semaphores
* afficher 20 voitures sur plusieurs tour
* afficher le tableau en le mettant à jour toute les x secondes pendant 1h30

num|s1|s2|s3|tour  |bestour|pit|out|numTour|Tot
---|--|--|--|------|-------|---|---|-------|---
1  |35|41|37|1min53|1min53 |0  |0  |1      |1min53
2  |38|40|38|1min56|1min56 |0  |0  |1      |1min56
3  |38|40|37|1min55|1min55 |0  |0  |1      |1min55
4  |38|35|41|1min54|1min54 |0  |0  |1      |1min54
5  |40|35|39|1min54|1min54 |0  |0  |1      |1min54
... JUSQUA 20


## sprint 1
> fin esperée le 18/07/2019 mais estimée au 01/08/2019
> ***FINI LE 26/7/2019***
* stocker les infos generée par tout les process dans mem partagée
* tester la mem partagée et l'ajuster avec des semaphores
* afficher le tableau avec les 20 temps 


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
- [x] fork pour avoir un process afficheur et 20 pour voiture

## Version 3:
### Sprint 1
> on veut pas spécialement de refresh avec les 15 tour pour chaque voiture mais au moins davoir les voiture classée pour un tour
- [x] stocker les infos generée par tout les process dans mem partagée
- [x] tester la mem partagée
- [x] afficher le tableau avec les 20 temps 

## Sprint 2
> on veut afficher le tableau que arrive dèjà à avoir avec la shm mais en plus, pouvoir écrire et lire en même temps pour au final afficher un tableau qui se rafraichis pour 1h30 de course

* implementer les semaphores
* afficher 20 voitures sur plusieurs tour
* afficher le tableau en le mettant à jour toute les x secondes pendant 1h30

## Version 4:
> Tri synchrone et classement finaux stocké
* classement selon tour complet, pit, out
* stocker le best time tout le temps
* (Q) éliminer 5 puis 5 puis classer dans l'ordre pour départ finale.
* écrire les résultats (PQF) dans un fichier
> affichage: 
> * voiture|s1|s2|s3|besttime|pit|out 
> * trié constamment pour que les meilleurs temps soit en haut
> * n’affiche plus de temps si il est out ou pit. Remettre la voiture à sa place dès son retour du pit

## Version 5:
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
:octocat:
