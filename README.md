# SpaceInvaders
Projet de Space Invaders

Dans le fichier README.md, je vous propose qu'on note les différentes choses à faire pour le projet, afin qu'on soit pas
trop en retard ^^'. J'ajoute de plus un tutoriel pour se servir de Github sur CLion (ou autre projet JetBrains) afin de
récupérer le projet à jour directement, avant d'y apporter vos modifications.

J'ai fait exprès d'inclure le fichier CMakeLists.txt afin de pouvoir vous le renvoyer si je le modifie. On pourra ainsi
compiler à la volée plusieurs fichiers de code, ce qui organisera considérablement notre travail. Si vous mettez à jour
ce fichier, n'oubliez pas de le recharger en faisant Tools > CMake > Reload CMake Project afin d'y appliquer les
modifications.

Le Groupe 2 est fier de vous compter dans ses rangs, faites-en sorte d'y rester. \#Délégué

## Roadmap

Les différentes étapes à coder prochainement :

- Compilation sous Qt Creator, générer notre .pro, intégrer la lib SFML pour le son, tester la compatibilité sur Linux, ajouter la ligne de Casali pour la compilation sous Mac OS X -- WORK IN PROGRESS
- Bouclier ; -- DONE
- Items en jeu ; -- WORK IN PROGRESS
- Gestionnaire automatique de niveaux ; --DONE
- Ecran de score. -- WORK IN PROGRESS
- ULTRA BOSS !!! -- DONE -- BUG SEGFAULT ??

N'hésitez pas à modifier en rajoutant des choses !

## Tutoriel : comment se servir de Github sous CLion

Nous considérerons ici que la dernière version à récupérer se trouve être celle sur le Github. Si vous avez des
modifications sur le projet à envoyer, faites une sauvegarde de votre code.

### Windows / Linux

Ouvrir les options dans File > Settings (ou File > Preferences selon la version).

### Mac OS X

Ouvrir les options complètes de CLion dans CLion > Preferences.

### Configuration

Sous la partie "Version control", sélectionnez l'onglet Github.

Entrez ici les champs suivants :
- Host : github.com
- Auth type : Password
- Login : <votre nom d'utilisateur Github>
- Password : <votre mot de passe Github>

N'oubliez pas de tester, puis Apply, et enfin OK.

_Éventuellement si ça n'a pas déjà été fait, CLion peut vous demander de configurer le mot de passe d'une base de données
, il s'agit de la fenêtre au cadenas bleu. Il s'agit d'une base de données contenant divers mots de passe liés au VCS,
éventuellement aux sites rattachés, etc. Il est pratique de configurer un mot de passe général afin de ne pas se faire
voler les accès à ses comptes._

Fermez tous les projets courants (File > Close Project).

### Cloner le projet Github

"Cloner un projet" signifie en télécharger la version courante à modifier pour pouvoir y apporter vos modifications afin
de le renvoyer.

Dans la petite fenêtre qui s'ouvre lorsque tous les projets sont fermés, créez un nouveau projet en sélectionnant 
l'option "Check out from version control", puis "Github". Comme vous avez configuré votre compte d'accès et m'avez passé
votre nom d'utilisateur Github, CLion devrait vous proposer de travailler sur vos projets sur une liste. Le projet à
sélectionner est https://github.com/GeeksdelaCave/SpaceInvaders.git. Si vous ne l'avez pas, collez l'URL.

Sélectionnez ensuite le répertoire où le projet sera cloné. Donnez enfin un nom au répertoire du projet en lui-même, par
défaut SpaceInvaders. Enfin, le bouton "Clone" pour valider. Le projet actuel devrait s'ouvrir sous vos yeux.
