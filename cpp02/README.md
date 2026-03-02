# C++ - Module 02

**Ad-hoc polymorphism, operator overloading and the Orthodox Canonical class form**

Version: 9.1

---

## Table des matières

- [Introduction](#introduction)
- [Règles générales](#règles-générales)
- [Nouvelles règles](#nouvelles-règles)
- [Instructions AI](#instructions-ai)
- [Exercise 00: My First Class in Orthodox Canonical Form](#exercise-00-my-first-class-in-orthodox-canonical-form)
- [Exercise 01: Towards a more useful fixed-point number class](#exercise-01-towards-a-more-useful-fixed-point-number-class)
- [Exercise 02: Now we're talking](#exercise-02-now-were-talking)
- [Exercise 03: BSP](#exercise-03-bsp)
- [Soumission et évaluation](#soumission-et-évaluation)

---

## Introduction

C++ est un langage de programmation généraliste créé par Bjarne Stroustrup comme une extension du langage C, ou "C with Classes" (source: Wikipedia).

L'objectif de ces modules est de vous introduire à la Programmation Orientée Objet. Ce sera le point de départ de votre parcours C++. Bien que de nombreux langages soient recommandés pour apprendre la POO, nous avons décidé de choisir C++ car il est dérivé de votre vieil ami C.

Parce que c'est un langage complexe, et afin de garder les choses simples, votre code devra être conforme au standard **C++98**.

Nous sommes conscients que le C++ moderne est assez différent à bien des égards. Donc, si vous souhaitez devenir un développeur C++ compétent, c'est à vous d'aller plus loin après le Common Core de 42 !

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

## Nouvelles règles

À partir de maintenant, toutes vos classes doivent être conçues selon la **Forme Canonique Orthodoxe**, sauf indication contraire explicite. Elles devront alors implémenter les quatre fonctions membres requises ci-dessous :

- **Constructeur par défaut**
- **Constructeur de copie**
- **Opérateur d'affectation de copie**
- **Destructeur**

Divisez le code de votre classe en deux fichiers. Le fichier d'en-tête (`.hpp`/`.h`) contient la définition de la classe, tandis que le fichier source (`.cpp`) contient l'implémentation.

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

## Exercise 00: My First Class in Orthodox Canonical Form

**Directory:** `ex00/`  
**Files to Submit:** `Makefile`, `main.cpp`, `Fixed.{h, hpp}`, `Fixed.cpp`  
**Forbidden:** None

Vous pensez connaître les entiers et les nombres à virgule flottante. Comme c'est mignon.

Veuillez lire cet article de 3 pages (1, 2, 3) pour découvrir que vous ne les connaissez pas. Allez-y, lisez-le.

Jusqu'à aujourd'hui, chaque nombre que vous avez utilisé dans votre code était essentiellement soit un entier, soit un nombre à virgule flottante, ou l'une de leurs variantes (short, char, long, double, etc.). Après avoir lu l'article ci-dessus, il est prudent de supposer que les entiers et les nombres à virgule flottante ont des caractéristiques opposées.

Mais aujourd'hui, les choses vont changer. Vous allez découvrir un nouveau et génial type de nombre : les **nombres à virgule fixe** ! Toujours absents des types scalaires de la plupart des langages, les nombres à virgule fixe offrent un équilibre précieux entre performance, précision, plage et exactitude. C'est pourquoi les nombres à virgule fixe sont particulièrement applicables aux graphiques informatiques, au traitement du son ou à la programmation scientifique, pour n'en nommer que quelques-uns.

Comme C++ manque de nombres à virgule fixe, vous allez les ajouter. Cet article de Berkeley est un bon début. Si vous n'avez aucune idée de ce qu'est l'Université de Berkeley, lisez cette section de sa page Wikipedia.

Créez une classe en Forme Canonique Orthodoxe qui représente un nombre à virgule fixe :

### Membres privés

- Un entier pour stocker la valeur du nombre à virgule fixe
- Un entier constant statique pour stocker le nombre de bits fractionnaires. Sa valeur sera toujours le littéral entier **8**

### Membres publics

- Un constructeur par défaut qui initialise la valeur du nombre à virgule fixe à 0
- Un constructeur de copie
- Une surcharge d'opérateur d'affectation de copie
- Un destructeur
- Une fonction membre `int getRawBits( void ) const;` qui retourne la valeur brute du nombre à virgule fixe
- Une fonction membre `void setRawBits( int const raw );` qui définit la valeur brute du nombre à virgule fixe

L'exécution de ce code :

```cpp
#include <iostream>

int main( void ) {
    Fixed a;
    Fixed b( a );
    Fixed c;
    c = b;
    
    std::cout << a.getRawBits() << std::endl;
    std::cout << b.getRawBits() << std::endl;
    std::cout << c.getRawBits() << std::endl;
    
    return 0;
}
```

Devrait afficher quelque chose de similaire à :

```
$> ./a.out
Default constructor called
Copy constructor called
Copy assignment operator called // <-- Cette ligne peut manquer selon votre implémentation
getRawBits member function called
Default constructor called
Copy assignment operator called
getRawBits member function called
getRawBits member function called
0
getRawBits member function called
0
getRawBits member function called
0
Destructor called
Destructor called
Destructor called
$>
```

---

## Exercise 01: Towards a more useful fixed-point number class

**Directory:** `ex01/`  
**Files to Submit:** `Makefile`, `main.cpp`, `Fixed.{h, hpp}`, `Fixed.cpp`  
**Authorized:** `roundf` (from `<cmath>`)

L'exercice précédent était un bon début, mais notre classe est assez inutile. Elle ne peut représenter que la valeur 0.0.

Ajoutez les constructeurs publics et fonctions membres publiques suivants à votre classe :

- Un constructeur qui prend un entier constant en paramètre. Il le convertit en la valeur à virgule fixe correspondante. La valeur des bits fractionnaires doit être initialisée à 8, comme dans l'exercice 00
- Un constructeur qui prend un nombre à virgule flottante constant en paramètre. Il le convertit en la valeur à virgule fixe correspondante. La valeur des bits fractionnaires doit être initialisée à 8, comme dans l'exercice 00
- Une fonction membre `float toFloat( void ) const;` qui convertit la valeur à virgule fixe en valeur à virgule flottante
- Une fonction membre `int toInt( void ) const;` qui convertit la valeur à virgule fixe en valeur entière

Et ajoutez la fonction suivante aux fichiers de la classe Fixed :

- Une surcharge de l'opérateur d'insertion (`<<`) qui insère une représentation à virgule flottante du nombre à virgule fixe dans l'objet de flux de sortie passé en paramètre

L'exécution de ce code :

```cpp
#include <iostream>

int main( void ) {
    Fixed a;
    Fixed const b( 10 );
    Fixed const c( 42.42f );
    Fixed const d( b );
    
    a = Fixed( 1234.4321f );
    
    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;
    
    std::cout << "a is " << a.toInt() << " as integer" << std::endl;
    std::cout << "b is " << b.toInt() << " as integer" << std::endl;
    std::cout << "c is " << c.toInt() << " as integer" << std::endl;
    std::cout << "d is " << d.toInt() << " as integer" << std::endl;
    
    return 0;
}
```

Devrait afficher quelque chose de similaire à :

```
$> ./a.out
Default constructor called
Int constructor called
Float constructor called
Copy constructor called
Copy assignment operator called
Float constructor called
Copy assignment operator called
Destructor called
a is 1234.43
b is 10
c is 42.4219
d is 10
a is 1234 as integer
b is 10 as integer
c is 42 as integer
d is 10 as integer
Destructor called
Destructor called
Destructor called
Destructor called
$>
```

---

## Exercise 02: Now we're talking

**Directory:** `ex02/`  
**Files to Submit:** `Makefile`, `main.cpp`, `Fixed.{h, hpp}`, `Fixed.cpp`  
**Authorized:** `roundf` (from `<cmath>`)

Ajoutez des fonctions membres publiques à votre classe pour surcharger les opérateurs suivants :

- Les 6 opérateurs de comparaison : `>`, `<`, `>=`, `<=`, `==`, et `!=`
- Les 4 opérateurs arithmétiques : `+`, `-`, `*`, et `/`
- Les 4 opérateurs d'incrémentation/décrémentation (pré-incrémentation et post-incrémentation, pré-décrémentation et post-décrémentation), qui augmenteront ou diminueront la valeur à virgule fixe du plus petit ϵ représentable, tel que `1 + ϵ > 1`

Ajoutez ces quatre fonctions membres publiques surchargées à votre classe :

- Une fonction membre statique `min` qui prend deux références à des nombres à virgule fixe en paramètres, et retourne une référence au plus petit
- Une fonction membre statique `min` qui prend deux références à des nombres à virgule fixe constants en paramètres, et retourne une référence au plus petit
- Une fonction membre statique `max` qui prend deux références à des nombres à virgule fixe en paramètres, et retourne une référence au plus grand
- Une fonction membre statique `max` qui prend deux références à des nombres à virgule fixe constants en paramètres, et retourne une référence au plus grand

C'est à vous de tester chaque fonctionnalité de votre classe. Cependant, l'exécution du code ci-dessous :

```cpp
#include <iostream>

int main( void ) {
    Fixed a;
    Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
    
    std::cout << a << std::endl;
    std::cout << ++a << std::endl;
    std::cout << a << std::endl;
    std::cout << a++ << std::endl;
    std::cout << a << std::endl;
    
    std::cout << b << std::endl;
    
    std::cout << Fixed::max( a, b ) << std::endl;
    
    return 0;
}
```

Devrait afficher quelque chose comme (pour une meilleure lisibilité, les messages de constructeur/destructeur sont supprimés dans l'exemple ci-dessous) :

```
$> ./a.out
0
0.00390625
0.00390625
0.00390625
0.0078125
10.1016
10.1016
$>
```

> Si vous faites une division par 0, il est acceptable que le programme plante.

---

## Exercise 03: BSP

**Directory:** `ex03/`  
**Files to Submit:** `Makefile`, `main.cpp`, `Fixed.{h, hpp}`, `Fixed.cpp`, `Point.{h, hpp}`, `Point.cpp`, `bsp.cpp`  
**Authorized:** `roundf` (from `<cmath>`)

Maintenant que vous avez une classe Fixed fonctionnelle, ce serait bien de l'utiliser.

Implémentez une fonction qui indique si un point est à l'intérieur d'un triangle ou non. Très utile, n'est-ce pas ?

BSP signifie Binary Space Partitioning. Vous êtes les bienvenus. :)

> Vous pouvez passer ce module sans compléter l'exercice 03.

Commençons par créer la classe `Point` en Forme Canonique Orthodoxe qui représente un point 2D :

### Membres privés

- Un attribut `Fixed const` x
- Un attribut `Fixed const` y
- Tout ce qui est utile

### Membres publics

- Un constructeur par défaut qui initialise x et y à 0
- Un constructeur qui prend deux nombres à virgule flottante constants en paramètres. Il initialise x et y avec ces paramètres
- Un constructeur de copie
- Une surcharge d'opérateur d'affectation de copie
- Un destructeur
- Tout ce qui est utile

Pour conclure, implémentez la fonction suivante dans le fichier approprié :

```cpp
bool bsp( Point const a, Point const b, Point const c, Point const point);
```

- `a`, `b`, `c` : Les sommets de notre triangle bien-aimé
- `point` : Le point à vérifier
- **Returns:** True si le point est à l'intérieur du triangle. False sinon

Ainsi, si le point est un sommet ou sur une arête, il retournera False.

Implémentez et rendez vos propres tests pour vous assurer que votre classe se comporte comme prévu.

---

## Soumission et évaluation

Rendez votre travail dans votre dépôt Git comme d'habitude. Seul le travail à l'intérieur de votre dépôt sera évalué pendant la défense. N'hésitez pas à vérifier les noms de vos dossiers et fichiers pour vous assurer qu'ils sont corrects.

Pendant l'évaluation, une brève modification du projet peut occasionnellement être demandée. Cela pourrait impliquer un changement de comportement mineur, quelques lignes de code à écrire ou réécrire, ou une fonctionnalité facile à ajouter.

Bien que cette étape ne soit pas applicable à tous les projets, vous devez être prêt si elle est mentionnée dans les directives d'évaluation.

Cette étape vise à vérifier votre compréhension réelle d'une partie spécifique du projet. La modification peut être effectuée dans n'importe quel environnement de développement de votre choix (par exemple, votre configuration habituelle), et elle devrait être réalisable en quelques minutes — à moins qu'un délai spécifique ne soit défini dans le cadre de l'évaluation.

Vous pouvez, par exemple, être invité à effectuer une petite mise à jour d'une fonction ou d'un script, modifier un affichage, ou ajuster une structure de données pour stocker de nouvelles informations, etc.

Les détails (portée, cible, etc.) seront spécifiés dans les directives d'évaluation et peuvent varier d'une évaluation à l'autre pour le même projet.
