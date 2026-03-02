# C++ - Module 01

**Memory allocation, pointers to members, references and switch statements**

Version: 11.1

---

## Table des matières

- [Introduction](#introduction)
- [Règles générales](#règles-générales)
- [Instructions AI](#instructions-ai)
- [Exercise 00: BraiiiiiiinnnzzzZ](#exercise-00-braiiiiiiinnnzzzz)
- [Exercise 01: Moar brainz!](#exercise-01-moar-brainz)
- [Exercise 02: HI THIS IS BRAIN](#exercise-02-hi-this-is-brain)
- [Exercise 03: Unnecessary violence](#exercise-03-unnecessary-violence)
- [Exercise 04: Sed is for losers](#exercise-04-sed-is-for-losers)
- [Exercise 05: Harl 2.0](#exercise-05-harl-20)
- [Exercise 06: Harl filter](#exercise-06-harl-filter)
- [Soumission et évaluation](#soumission-et-évaluation)

---

## Introduction

C++ est un langage de programmation généraliste créé par Bjarne Stroustrup comme une extension du langage C, ou "C with Classes" (source: Wikipedia).

L'objectif de ces modules est de vous introduire à la Programmation Orientée Objet. Ce sera le point de départ de votre parcours C++. Bien que de nombreux langages soient recommandés pour apprendre la POO, nous avons choisi C++ car il est dérivé de votre vieil ami, le C.

Parce que c'est un langage complexe, et afin de garder les choses simples, votre code devra être conforme au standard **C++98**.

Nous sommes conscients que le C++ moderne est très différent à bien des égards. Si vous souhaitez devenir un développeur C++ compétent, c'est à vous d'aller plus loin après le Common Core de 42 !

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

## Exercise 00: BraiiiiiiinnnzzzZ

**Directory:** `ex00/`  
**Files to Submit:** `Makefile`, `main.cpp`, `Zombie.{h, hpp}`, `Zombie.cpp`, `newZombie.cpp`, `randomChump.cpp`  
**Forbidden:** None

Tout d'abord, implémentez une classe `Zombie`. Elle a un attribut privé `string name`.

Ajoutez une fonction membre `void announce( void );` à la classe Zombie. Les zombies s'annoncent comme suit :

```
<name>: BraiiiiiiinnnzzzZ...
```

N'imprimez pas les chevrons (< et >). Pour un zombie nommé Foo, le message serait :

```
Foo: BraiiiiiiinnnzzzZ...
```

Ensuite, implémentez les deux fonctions suivantes :

### `Zombie* newZombie( std::string name );`

Cette fonction crée un zombie, le nomme et le retourne afin que vous puissiez l'utiliser en dehors de la portée de la fonction.

### `void randomChump( std::string name );`

Cette fonction crée un zombie, le nomme et le fait s'annoncer.

Maintenant, quel est le véritable objectif de l'exercice ? Vous devez déterminer dans quel cas il est préférable d'allouer des zombies sur la pile ou sur le tas.

Les zombies doivent être détruits lorsque vous n'en avez plus besoin. Le destructeur doit afficher un message avec le nom du zombie à des fins de débogage.

---

## Exercise 01: Moar brainz!

**Directory:** `ex01/`  
**Files to Submit:** `Makefile`, `main.cpp`, `Zombie.{h, hpp}`, `Zombie.cpp`, `zombieHorde.cpp`  
**Forbidden:** None

Il est temps de créer une horde de Zombies !

Implémentez la fonction suivante dans le fichier approprié :

```cpp
Zombie* zombieHorde( int N, std::string name );
```

Elle doit allouer N objets Zombie en une seule allocation. Ensuite, elle doit initialiser les zombies, en donnant à chacun d'eux le nom passé en paramètre. La fonction retourne un pointeur vers le premier zombie.

Implémentez vos propres tests pour vous assurer que votre fonction `zombieHorde()` fonctionne comme prévu. Essayez d'appeler `announce()` pour chacun des zombies.

N'oubliez pas d'utiliser `delete` pour désallouer tous les zombies et vérifiez les fuites de mémoire.

---

## Exercise 02: HI THIS IS BRAIN

**Directory:** `ex02/`  
**Files to Submit:** `Makefile`, `main.cpp`  
**Forbidden:** None

Écrivez un programme qui contient :

- Une variable string initialisée à "HI THIS IS BRAIN"
- `stringPTR` : un pointeur vers la string
- `stringREF` : une référence vers la string

Votre programme doit afficher :

- L'adresse mémoire de la variable string
- L'adresse mémoire contenue par `stringPTR`
- L'adresse mémoire contenue par `stringREF`

Et ensuite :

- La valeur de la variable string
- La valeur pointée par `stringPTR`
- La valeur pointée par `stringREF`

C'est tout — pas de pièges. L'objectif de cet exercice est de démystifier les références, qui peuvent sembler complètement nouvelles. Bien qu'il y ait quelques petites différences, c'est simplement une autre syntaxe pour quelque chose que vous faites déjà : la manipulation d'adresses.

---

## Exercise 03: Unnecessary violence

**Directory:** `ex03/`  
**Files to Submit:** `Makefile`, `main.cpp`, `Weapon.{h, hpp}`, `Weapon.cpp`, `HumanA.{h, hpp}`, `HumanA.cpp`, `HumanB.{h, hpp}`, `HumanB.cpp`  
**Forbidden:** None

Implémentez une classe `Weapon` qui a :

- Un attribut privé `type`, qui est une string
- Une fonction membre `getType()` qui retourne une référence constante vers `type`
- Une fonction membre `setType()` qui définit `type` en utilisant la nouvelle valeur passée en paramètre

Maintenant, créez deux classes : `HumanA` et `HumanB`. Elles ont toutes deux une `Weapon` et un `name`. Elles ont aussi une fonction membre `attack()` qui affiche (sans les chevrons) :

```
<name> attacks with their <weapon type>
```

`HumanA` et `HumanB` sont presque identiques sauf pour ces deux petits détails :

- Alors que `HumanA` prend la `Weapon` dans son constructeur, `HumanB` ne le fait pas
- `HumanB` peut ne pas toujours avoir une arme, alors que `HumanA` sera toujours armé

Si votre implémentation est correcte, l'exécution du code suivant affichera une attaque avec "crude spiked club" suivie d'une seconde attaque avec "some other type of club" pour les deux cas de test :

```cpp
int main()
{
    {
        Weapon club = Weapon("crude spiked club");
        HumanA bob("Bob", club);
        bob.attack();
        club.setType("some other type of club");
        bob.attack();
    }
    {
        Weapon club = Weapon("crude spiked club");
        HumanB jim("Jim");
        jim.setWeapon(club);
        jim.attack();
        club.setType("some other type of club");
        jim.attack();
    }
    return 0;
}
```

N'oubliez pas de vérifier les fuites de mémoire.

> Dans quel cas pensez-vous qu'il serait préférable d'utiliser un pointeur vers Weapon ? Et une référence vers Weapon ? Pourquoi ? Réfléchissez-y avant de commencer cet exercice.

---

## Exercise 04: Sed is for losers

**Directory:** `ex04/`  
**Files to Submit:** `Makefile`, `main.cpp`, `*.cpp`, `*.{h, hpp}`  
**Forbidden:** `std::string::replace`

Créez un programme qui prend trois paramètres dans l'ordre suivant : un nom de fichier et deux strings, `s1` et `s2`.

Il doit ouvrir le fichier `<filename>` et copier son contenu dans un nouveau fichier `<filename>.replace`, en remplaçant chaque occurrence de `s1` par `s2`.

L'utilisation de fonctions de manipulation de fichiers C est interdite et sera considérée comme de la triche. Toutes les fonctions membres de la classe `std::string` sont autorisées, sauf `replace`. Utilisez-les judicieusement !

Bien sûr, gérez les entrées inattendues et les erreurs. Vous devez créer et rendre vos propres tests pour vous assurer que votre programme fonctionne comme prévu.

---

## Exercise 05: Harl 2.0

**Directory:** `ex05/`  
**Files to Submit:** `Makefile`, `main.cpp`, `Harl.{h, hpp}`, `Harl.cpp`  
**Forbidden:** None

Connaissez-vous Harl ? Nous le connaissons tous, n'est-ce pas ? Au cas où vous ne le connaîtriez pas, voici le genre de commentaires que Harl fait. Ils sont classés par niveaux :

- **"DEBUG"** : Les messages de débogage contiennent des informations contextuelles. Ils sont principalement utilisés pour le diagnostic de problèmes.
  - Exemple : "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!"

- **"INFO"** : Ces messages contiennent des informations étendues. Ils sont utiles pour tracer l'exécution du programme dans un environnement de production.
  - Exemple : "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!"

- **"WARNING"** : Les messages d'avertissement indiquent un problème potentiel dans le système. Cependant, il peut être géré ou ignoré.
  - Exemple : "I think I deserve to have some extra bacon for free. I've been coming for years, whereas you started working here just last month."

- **"ERROR"** : Ces messages indiquent qu'une erreur irrécupérable s'est produite. C'est généralement un problème critique qui nécessite une intervention manuelle.
  - Exemple : "This is unacceptable! I want to speak to the manager now."

Vous allez automatiser Harl. Ce ne sera pas difficile puisqu'il dit toujours les mêmes choses. Vous devez créer une classe `Harl` avec les fonctions membres privées suivantes :

- `void debug( void );`
- `void info( void );`
- `void warning( void );`
- `void error( void );`

Harl a aussi une fonction membre publique qui appelle les quatre fonctions membres ci-dessus en fonction du niveau passé en paramètre :

```cpp
void complain( std::string level );
```

L'objectif de cet exercice est d'utiliser des **pointeurs vers des fonctions membres**. Ce n'est pas une suggestion. Harl doit se plaindre sans utiliser une forêt de if/else if/else. Il ne réfléchit pas à deux fois !

Créez et rendez des tests pour montrer que Harl se plaint beaucoup. Vous pouvez utiliser les exemples de commentaires listés ci-dessus dans le sujet ou choisir d'utiliser des commentaires de votre choix.

---

## Exercise 06: Harl filter

**Directory:** `ex06/`  
**Files to Submit:** `Makefile`, `main.cpp`, `Harl.{h, hpp}`, `Harl.cpp`  
**Forbidden:** None

Parfois, vous ne voulez pas prêter attention à tout ce que Harl dit. Implémentez un système pour filtrer ce que Harl dit en fonction des niveaux de log que vous voulez écouter.

Créez un programme qui prend en paramètre l'un des quatre niveaux. Il affichera tous les messages de ce niveau et au-dessus. Par exemple :

```bash
$> ./harlFilter "WARNING"
[ WARNING ]
I think I deserve to have some extra bacon for free.
I've been coming for years, whereas you started working here just last month.

[ ERROR ]
This is unacceptable! I want to speak to the manager now.

$> ./harlFilter "I am not sure how tired I am today..."
[ Probably complaining about insignificant problems ]
```

Bien qu'il existe plusieurs façons de gérer Harl, l'une des plus efficaces est de le **SWITCH** (éteindre).

Donnez le nom `harlFilter` à votre exécutable.

Vous devez utiliser, et peut-être découvrir, l'instruction **switch** dans cet exercice.

> Vous pouvez passer ce module sans faire l'exercice 06.

---

## Soumission et évaluation

Rendez votre travail dans votre dépôt Git comme d'habitude. Seul le travail à l'intérieur de votre dépôt sera évalué pendant la défense. N'hésitez pas à vérifier les noms de vos dossiers et fichiers pour vous assurer qu'ils sont corrects.

Pendant l'évaluation, une brève modification du projet peut occasionnellement être demandée. Cela pourrait impliquer un changement de comportement mineur, quelques lignes de code à écrire ou réécrire, ou une fonctionnalité facile à ajouter.

Bien que cette étape ne soit pas applicable à tous les projets, vous devez être prêt si elle est mentionnée dans les directives d'évaluation.

Cette étape vise à vérifier votre compréhension réelle d'une partie spécifique du projet. La modification peut être effectuée dans n'importe quel environnement de développement de votre choix (par exemple, votre configuration habituelle), et elle devrait être réalisable en quelques minutes — à moins qu'un délai spécifique ne soit défini dans le cadre de l'évaluation.

Vous pouvez, par exemple, être invité à effectuer une petite mise à jour d'une fonction ou d'un script, modifier un affichage, ou ajuster une structure de données pour stocker de nouvelles informations, etc.

Les détails (portée, cible, etc.) seront spécifiés dans les directives d'évaluation et peuvent varier d'une évaluation à l'autre pour le même projet.
