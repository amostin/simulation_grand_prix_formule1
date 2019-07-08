> On va pas encore faire le readme maintenant. Je vais l'utiliser pour expliquer l'organisation basique pour qu'on puisse produire un travail de qualité. Ces informations sont inspirées des [guides github](https://guides.github.com/) et de [l'aide github](https://help.github.com/en).

> :hammer: Moi aussi je connais pas bien donc je m'entraine en suivant cette procédure :slightly_smiling_face:

# Prérequis:

:warning: **On ne commmit rien sur la branche master.** :warning: 

> Les commits doivent tous passer par une pull request et être validé pour une fusion avec la branche master; Même si c'est par soi même. Cela pour garder un historique clair de notre travail.

:point_right: Le minimum de ce que je sais sur l'organisation d'un projet sur github se trouve dans [ce fichier](https://drive.google.com/open?id=1gvOVPevHNjXMufL_EpnSRNU-TSSCz56bsf2Nkz90PwE).

# Etapes de production de contenu:
1. On va voir les tableau dans l'onglet `Projects` pour savoir où on en est et mettre la ou les taches dans la ou les bonnes colonnes. 
> Je pense que les cartes se mettent automatiquement en proposition dans le tableau mais qu'il faut qu'on les mettent nous même dans la colonne à faire ou en progression pour qu'elle navigue automatiquement. En tout cas je viens de tester que si on met une carte dans `validation` elle bouge automatiquement vers `done` quand je merge mais si je crée une pull request, il me propose juste de mettre la carte dans une colonne. 
2. On crée une branche qui sera nommée selon le code que l'on veut produire.
2. On crée/modifie le fichier.
3. On prend soin de titrer chaque commit en quelque mots bien compréhensible avec une description si besoin
4. Si on bloque sur quoi que ce soit, on ouvre une issue en décrivant le nom du problème, le contexte, le résultat attendu et le résultat obtenu. Ne pas hésiter à enrichir ce genre de contenu (commit, issues, pull request) avec des étiquettes, mention, etc.
5. Si le code est fonctionel, on crée une pull request en mentionnant les personnes qui s'intéressent au projet.
6. Si la request est acceptée, on merge la branche sur la master et on delete la branche.
> Il est possible de modifier directement un fichier de la branche master puis créer une branche avec cette modif au moment du commit. Cest facile et ça envoi direct le commit dans les pull request, ce qui envoi une notif et met les tableaux de gestion de projet à jour.
# Gestion du projet
**Voir l'onglet `Projects` pour accéder:**
* Au tableau avancement qui répertorie les `Travaux à faire`, les `Travaux en cours` et `Travaux fini`.
* Au tableau de gestion de bug qui répertorie les `Bugs à trier`, les `Bugs important`, les `Bugs moins important` et les bugs résolus.
> Dans le tableau Kaban automatisé avec review:
> * Les nouvelles issues arrivent dans la colonne `To Do` 
> * Les nouvelles pull request, les rouvertes et les issues rouvertes arrivent dans la colonne `In progress` 
> * Les issues fermée, pull request fusionée ou fusionnée sans validation arrivent dans la colonne `Done`
> * Si qqu demande des changement dans une pull request, la carte va dans review in progress

> Dans le tableau triage de bug:
> * Les issues nouvelles et réouvertes arrivent dans `To Do`
> * Les issues fermée, pull request fusionée ou fusionnée sans validation arrivent dans la colonne `Done`
# En résumé, pour les cartes projects:
* Au moment du commit, il faut sélectionner le tableau dans lequel la carte doit être ajoutée.
* Prendre l'habitude d'aller tout le temps vérifier que les tableaux sont à jour. 
* On commente un max les issues et pull request
