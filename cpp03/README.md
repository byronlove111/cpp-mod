# C++ - Module 03

**Inheritance**

Version: 8.1

---

## Table des matières

- [Introduction](#introduction)
- [Règles générales](#règles-générales)
- [Instructions AI](#instructions-ai)
- [Exercise 00: Aaaaand... OPEN!](#exercise-00-aaaaand-open)
- [Exercise 01: Serena, my love!](#exercise-01-serena-my-love)
- [Exercise 02: Repetitive work](#exercise-02-repetitive-work)
- [Exercise 03: Now it's weird!](#exercise-03-now-its-weird)
- [Soumission et évaluation](#soumission-et-évaluation)

---

## Introduction

C++ est un langage de programmation généraliste créé par Bjarne Stroustrup comme une extension du langage C, ou "C with Classes" (source: Wikipedia).

L'objectif de ces modules est de vous introduire à la Programmation Orientée Objet. Ce sera le point de départ de votre parcours C++. Bien que de nombreux langages soient recommandés pour apprendre la POO, nous avons décidé de choisir C++ car il est dérivé de votre vieil ami C.

Parce que c'est un langage complexe, et afin de garder les choses simples, votre code devra être conforme au standard **C++98**.

Nous sommes conscients que le C++ moderne est très différent à bien des égards. Donc, si vous souhaitez devenir un développeur C++ compétent, c'est à vous d'aller plus loin après le Common Core de 42 !

---

## Règles générales

### Compilation

- Compilez votre code avec `c++` et les flags `-Wall -Wextra -Werror`
- Votre code doit toujours compiler avec le flag `-std=c++98`

### Formatage et conventions de nommage

- Les répertoires d'exercices seront nommés ainsi : `ex00`, `ex01`, ... , `exn`
- Nommez vos fichiers, classes, fonctions, fonctions membres et attributs comme requis dans les consignes
- Écrivez les noms de classes en format **UpperCamelCase**. Les fichiers contenant du code de classe seront toujours nommés selon le nom de la classe. Par exemple :
  - `ClassName.hpp`/`ClassName.h`, `ClassName.cpp`, ou `ClassName.tpp`
  - Si vous avez un fichier d'en-tête contenant la définition d'une classe "BrickWall" représentant un mur de briques, son nom sera `BrickWall.hpp`
- Sauf indication contraire, chaque message de sortie doit se terminer par un caractère de nouvelle ligne et être affiché sur la sortie standard
- **Adieu Norminette !** Aucun style de codage n'est imposé dans les modules C++. Vous pouvez suivre votre préféré. Mais gardez à l'esprit que du code que vos évaluateurs ne peuvent pas comprendre est du code qu'ils ne peuvent pas noter. Faites de votre mieux pour écrire du code propre et lisible.

### Autorisé/Interdit

Vous ne codez plus en C. Il est temps de passer au C++ ! Par conséquent :

- Vous êtes autorisé à utiliser presque tout de la bibliothèque standard. Ainsi, au lieu de vous en tenir à ce que vous connaissez déjà, il serait intelligent d'utiliser autant que possible les versions C++ des fonctions C auxquelles vous êtes habitué
- Cependant, vous ne pouvez pas utiliser d'autre bibliothèque externe. Cela signifie que C++11 (et les formes dérivées) et les bibliothèques Boost sont interdites. Les fonctions suivantes sont également interdites : `*printf()`, `*alloc()` et `free()`. Si vous les utilisez, votre note sera 0 et c'est tout
- Notez que sauf indication contraire explicite, les mots-clés `using namespace <ns_name>` et `friend` sont interdits. Sinon, votre note sera -42
- Vous êtes autorisé à utiliser la STL **uniquement dans les Modules 08 et 09**. Cela signifie : pas de Conteneurs (vector/list/map, etc.) et pas d'Algorithmes (tout ce qui nécessite d'inclure l'en-tête `<algorithm>`) jusqu'à ce moment. Sinon, votre note sera -42

### Quelques exigences de conception

- Les fuites de mémoire se produisent aussi en C++ ! Lorsque vous allouez de la mémoire (en utilisant le mot-clé `new`), vous devez éviter les fuites de mémoire
- Du Module 02 au Module 09, vos classes doivent être conçues selon la **Forme Canonique Orthodoxe**, sauf indication contraire explicite
- Toute implémentation de fonction placée dans un fichier d'en-tête (sauf pour les templates de fonction) signifie 0 à l'exercice
- Vous devriez pouvoir utiliser chacun de vos en-têtes indépendamment des autres. Ainsi, ils doivent inclure toutes les dépendances dont ils ont besoin. Cependant, vous devez éviter le problème de double inclusion en ajoutant des gardes d'inclusion. Sinon, votre note sera 0

### À lire

- Vous pouvez ajouter des fichiers supplémentaires si nécessaire (c'est-à-dire pour diviser votre code). Comme ces devoirs ne sont pas vérifiés par un programme, n'hésitez pas à le faire tant que vous rendez les fichiers obligatoires
- Parfois, les consignes d'un exercice semblent courtes mais les exemples peuvent montrer des exigences qui ne sont pas explicitement écrites dans les instructions
- **Lisez chaque module complètement avant de commencer !** Vraiment, faites-le
- **Par Odin, par Thor ! Utilisez votre cerveau !!!**

> En ce qui concerne le Makefile pour les projets C++, les mêmes règles qu'en C s'appliquent (voir le chapitre Norm sur le Makefile).

> Vous devrez implémenter beaucoup de classes. Cela peut sembler fastidieux, à moins que vous ne puissiez scripter votre éditeur de texte préféré.

> Vous disposez d'une certaine liberté pour compléter les exercices. Cependant, suivez les règles obligatoires et ne soyez pas paresseux. Vous manqueriez beaucoup d'informations utiles ! N'hésitez pas à lire sur les concepts théoriques.

---

## Instructions AI

### Contexte

Ce projet est conçu pour vous aider à découvrir les éléments fondamentaux de votre formation 42.

Pour ancrer correctement les connaissances et compétences clés, il est essentiel d'adopter une approche réfléchie de l'utilisation des outils d'IA et du soutien.

Un véritable apprentissage fondamental nécessite un effort intellectuel authentique — à travers le défi, la répétition et les échanges d'apprentissage par les pairs.

Pour un aperçu plus complet de notre position sur l'IA — en tant qu'outil d'apprentissage, dans le cadre de la formation 42, et en tant qu'attente sur le marché du travail — veuillez consulter la FAQ dédiée sur l'intranet.

### Message principal

☛ Construisez des fondations solides sans raccourcis.  
☛ Développez réellement vos compétences techniques et personnelles.  
☛ Vivez un véritable apprentissage par les pairs, commencez à apprendre comment apprendre et résoudre de nouveaux problèmes.  
☛ Le parcours d'apprentissage est plus important que le résultat.  
☛ Apprenez les risques associés à l'IA, et développez des pratiques de contrôle efficaces et des contre-mesures pour éviter les pièges courants.

### Règles pour l'apprenant

- Vous devez appliquer un raisonnement à vos tâches assignées, surtout avant de vous tourner vers l'IA
- Vous ne devez pas demander de réponses directes à l'IA
- Vous devez vous renseigner sur l'approche globale de 42 concernant l'IA

### Résultats de phase

Dans cette phase fondamentale, vous obtiendrez les résultats suivants :

- Obtenir des fondations techniques et de codage appropriées
- Savoir pourquoi et comment l'IA peut être dangereuse pendant cette phase

### Commentaires et exemple

- Oui, nous savons que l'IA existe — et oui, elle peut résoudre vos projets. Mais vous êtes ici pour apprendre, pas pour prouver que l'IA a appris. Ne perdez pas votre temps (ni le nôtre) juste pour démontrer que l'IA peut résoudre le problème donné
- Apprendre à 42 ne consiste pas à connaître la réponse — il s'agit de développer la capacité d'en trouver une. L'IA vous donne la réponse directement, mais cela vous empêche de construire votre propre raisonnement. Et le raisonnement prend du temps, des efforts et implique l'échec. Le chemin vers le succès n'est pas censé être facile
- Gardez à l'esprit que pendant les examens, l'IA n'est pas disponible — pas d'internet, pas de smartphones, etc. Vous réaliserez rapidement si vous avez trop compté sur l'IA dans votre processus d'apprentissage
- L'apprentissage par les pairs vous expose à différentes idées et approches, améliorant vos compétences interpersonnelles et votre capacité à penser de manière divergente. C'est bien plus précieux que de simplement discuter avec un bot. Alors n'ayez pas peur — parlez, posez des questions et apprenez ensemble !
- Oui, l'IA fera partie du programme — à la fois comme outil d'apprentissage et comme sujet en soi. Vous aurez même la chance de construire votre propre logiciel d'IA. Pour en savoir plus sur l'approche crescendo que vous suivrez, consultez la documentation disponible sur l'intranet

#### ✓ Bonne pratique

Je suis bloqué sur un nouveau concept. Je demande à quelqu'un à proximité comment il l'a abordé. Nous parlons pendant 10 minutes — et soudain ça fait tilt. Je comprends.

#### ✗ Mauvaise pratique

J'utilise secrètement l'IA, je copie du code qui semble correct. Pendant l'évaluation par les pairs, je ne peux rien expliquer. J'échoue. Pendant l'examen — pas d'IA — je suis à nouveau bloqué. J'échoue.

---

## Exercise 00: Aaaaand... OPEN!

**Directory:** `ex00/`  
**Files to Submit:** `Makefile`, `main.cpp`, `ClapTrap.{h, hpp}`, `ClapTrap.cpp`  
**Forbidden:** None

Tout d'abord, vous devez implémenter une classe ! Comme c'est original !

Elle s'appellera `ClapTrap` et aura les attributs privés suivants initialisés aux valeurs spécifiées entre parenthèses :

- **Name**, qui est passé en paramètre au constructeur
- **Hit points (10)**, représentant la santé du ClapTrap
- **Energy points (10)**
- **Attack damage (0)**

Ajoutez les fonctions membres publiques suivantes pour que le ClapTrap se comporte de manière plus réaliste :

```cpp
void attack(const std::string& target);
void takeDamage(unsigned int amount);
void beRepaired(unsigned int amount);
```

Lorsque ClapTrap attaque, il fait perdre `<attack damage>` points de vie à sa cible. Lorsque ClapTrap se répare, il récupère `<amount>` points de vie. Attaquer et se réparer coûtent chacun 1 point d'énergie. Bien sûr, ClapTrap ne peut rien faire s'il n'a plus de points de vie ou de points d'énergie. Cependant, comme ces exercices servent d'introduction, les instances de ClapTrap ne doivent pas interagir directement les unes avec les autres, et les paramètres ne feront pas référence à une autre instance de ClapTrap.

Dans toutes ces fonctions membres, vous devez afficher un message pour décrire ce qui se passe. Par exemple, la fonction `attack()` peut afficher quelque chose comme (bien sûr, sans les chevrons) :

```
ClapTrap <name> attacks <target>, causing <damage> points of damage!
```

Les constructeurs et le destructeur doivent également afficher un message, afin que vos évaluateurs puissent facilement voir qu'ils ont été appelés.

Implémentez et rendez vos propres tests pour vous assurer que votre code fonctionne comme prévu.

---

## Exercise 01: Serena, my love!

**Directory:** `ex01/`  
**Files to Submit:** Files from the previous exercise + `ScavTrap.{h, hpp}`, `ScavTrap.cpp`  
**Forbidden:** None

Parce qu'on n'a jamais assez de ClapTraps, vous allez maintenant créer un robot dérivé.

Il s'appellera `ScavTrap` et héritera des constructeurs et du destructeur de ClapTrap. Cependant, ses constructeurs, destructeur et `attack()` afficheront des messages différents. Après tout, les ClapTraps sont conscients de leur individualité.

Notez qu'un **chaînage de construction/destruction approprié** doit être montré dans vos tests. Lorsqu'un ScavTrap est créé, le programme commence par construire un ClapTrap. La destruction se produit dans l'ordre inverse. Pourquoi ?

ScavTrap utilisera les attributs de ClapTrap (mettez à jour ClapTrap en conséquence) et doit les initialiser à :

- **Name**, qui est passé en paramètre au constructeur
- **Hit points (100)**, représentant la santé du ClapTrap
- **Energy points (50)**
- **Attack damage (20)**

ScavTrap aura également sa propre capacité spéciale :

```cpp
void guardGate();
```

Cette fonction membre affichera un message indiquant que ScavTrap est maintenant en mode Gate keeper.

N'oubliez pas d'ajouter plus de tests à votre programme.

---

## Exercise 02: Repetitive work

**Directory:** `ex02/`  
**Files to Submit:** Files from previous exercises + `FragTrap.{h, hpp}`, `FragTrap.cpp`  
**Forbidden:** None

Créer des ClapTraps commence probablement à vous énerver.

Maintenant, implémentez une classe `FragTrap` qui hérite de ClapTrap. Elle est très similaire à ScavTrap. Cependant, ses messages de construction et de destruction doivent être différents. Un chaînage de construction/destruction approprié doit être montré dans vos tests. Lorsqu'un FragTrap est créé, le programme commence par construire un ClapTrap. La destruction se produit dans l'ordre inverse.

Il en va de même pour les attributs, mais avec des valeurs différentes cette fois :

- **Name**, qui est passé en paramètre au constructeur
- **Hit points (100)**, représentant la santé du ClapTrap
- **Energy points (100)**
- **Attack damage (30)**

FragTrap a aussi une capacité spéciale :

```cpp
void highFivesGuys(void);
```

Cette fonction membre affiche une demande positive de high-five sur la sortie standard.

Encore une fois, ajoutez plus de tests à votre programme.

---

## Exercise 03: Now it's weird!

**Directory:** `ex03/`  
**Files to Submit:** Files from previous exercises + `DiamondTrap.{h, hpp}`, `DiamondTrap.cpp`  
**Forbidden:** None

Dans cet exercice, vous allez créer un monstre : un ClapTrap qui est moitié FragTrap, moitié ScavTrap. Il s'appellera `DiamondTrap`, et il héritera à la fois de FragTrap ET de ScavTrap. C'est tellement risqué !

La classe DiamondTrap aura un attribut privé nommé `name`. Cet attribut doit avoir exactement le même nom de variable que dans la classe de base ClapTrap (sans faire référence au nom du robot).

Pour être plus clair, voici deux exemples :

- Si la variable de ClapTrap est `name`, donnez à la variable de DiamondTrap le nom `name`
- Si la variable de ClapTrap est `_name`, donnez à la variable de DiamondTrap le nom `_name`

Ses attributs et fonctions membres seront hérités de ses classes parentes :

- **Name**, qui est passé en paramètre à un constructeur
- **ClapTrap::name** (paramètre du constructeur + suffixe "_clap_name")
- **Hit points (FragTrap)**
- **Energy points (ScavTrap)**
- **Attack damage (FragTrap)**
- **attack() (ScavTrap)**

En plus des fonctions spéciales des deux classes parentes, DiamondTrap aura sa propre capacité spéciale :

```cpp
void whoAmI();
```

Cette fonction membre affichera à la fois son nom et son nom ClapTrap.

Bien sûr, l'instance ClapTrap de DiamondTrap sera créée une fois, et une seule fois. Oui, il y a une astuce.

Encore une fois, ajoutez plus de tests à votre programme.

> Connaissez-vous les flags de compilation `-Wshadow` et `-Wno-shadow` ?

> Vous pouvez passer ce module sans compléter l'exercice 03.

---

## Soumission et évaluation

Soumettez votre travail dans votre dépôt Git comme d'habitude. Seul le travail à l'intérieur de votre dépôt sera évalué pendant la défense. N'hésitez pas à vérifier les noms de vos dossiers et fichiers pour vous assurer qu'ils sont corrects.

Pendant l'évaluation, une brève modification du projet peut occasionnellement être demandée. Cela pourrait impliquer un changement de comportement mineur, quelques lignes de code à écrire ou réécrire, ou une fonctionnalité facile à ajouter.

Bien que cette étape ne soit pas applicable à tous les projets, vous devez être prêt si elle est mentionnée dans les directives d'évaluation.

Cette étape vise à vérifier votre compréhension réelle d'une partie spécifique du projet. La modification peut être effectuée dans n'importe quel environnement de développement de votre choix (par exemple, votre configuration habituelle), et elle devrait être réalisable en quelques minutes — à moins qu'un délai spécifique ne soit défini dans le cadre de l'évaluation.

Vous pouvez, par exemple, être invité à effectuer une petite mise à jour d'une fonction ou d'un script, modifier un affichage, ou ajuster une structure de données pour stocker de nouvelles informations, etc.

Les détails (portée, cible, etc.) seront spécifiés dans les directives d'évaluation et peuvent varier d'une évaluation à l'autre pour le même projet.
