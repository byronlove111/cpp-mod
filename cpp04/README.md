# C++ - Module 04

**Subtype Polymorphism, Abstract Classes, and Interfaces**

Version: 13.1

---

## Table des matières

- [Introduction](#introduction)
- [Règles générales](#règles-générales)
- [Instructions AI](#instructions-ai)
- [Exercise 00: Polymorphism](#exercise-00-polymorphism)
- [Exercise 01: I don't want to set the world on fire](#exercise-01-i-dont-want-to-set-the-world-on-fire)
- [Exercise 02: Abstract class](#exercise-02-abstract-class)
- [Exercise 03: Interface & recap](#exercise-03-interface--recap)
- [Soumission et évaluation](#soumission-et-évaluation)

---

## Introduction

C++ est un langage de programmation généraliste créé par Bjarne Stroustrup comme une extension du langage C, ou "C with Classes" (source: Wikipedia).

L'objectif de ces modules est de vous introduire à la Programmation Orientée Objet. Ce sera le point de départ de votre parcours C++. Bien que de nombreux langages soient recommandés pour apprendre la POO, nous avons choisi C++ car il est dérivé de votre vieil ami C.

Parce que C++ est un langage complexe, et pour garder les choses simples, votre code devra être conforme au standard **C++98**.

Nous sommes conscients que le C++ moderne diffère considérablement à bien des égards. Par conséquent, si vous souhaitez devenir un développeur C++ compétent, c'est à vous de continuer votre parcours au-delà du Common Core de 42 !

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

## Exercise 00: Polymorphism

**Directory:** `ex00/`  
**Files to Submit:** `Makefile`, `main.cpp`, `*.cpp`, `*.{h, hpp}`  
**Forbidden:** None

Pour chaque exercice, vous devez fournir les tests les plus complets possibles. Les constructeurs et destructeurs de chaque classe doivent afficher des messages spécifiques. N'utilisez pas le même message pour toutes les classes.

Commencez par implémenter une classe de base simple appelée `Animal`. Elle a un attribut protégé :

```cpp
std::string type;
```

Implémentez une classe `Dog` qui hérite de Animal.

Implémentez une classe `Cat` qui hérite de Animal.

Ces deux classes dérivées doivent définir leur champ `type` en fonction de leur nom. Ensuite, le type de Dog sera initialisé à "Dog", et le type de Cat sera initialisé à "Cat". Le type de la classe Animal peut être laissé vide ou défini à la valeur de votre choix.

Chaque animal doit pouvoir utiliser la fonction membre :

```cpp
makeSound()
```

Elle affichera un son approprié (les chats n'aboient pas).

L'exécution de ce code devrait afficher les sons spécifiques des classes Dog et Cat, pas celui de Animal :

```cpp
int main()
{
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    
    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    i->makeSound(); // affichera le son du chat !
    j->makeSound();
    meta->makeSound();
    ...
    return 0;
}
```

Pour vous assurer que vous avez compris comment cela fonctionne, implémentez une classe `WrongCat` qui hérite d'une classe `WrongAnimal`. Si vous remplacez Animal et Cat par les mauvaises versions dans le code ci-dessus, le WrongCat devrait afficher le son de WrongAnimal.

Implémentez et rendez plus de tests que ceux donnés ci-dessus.

---

## Exercise 01: I don't want to set the world on fire

**Directory:** `ex01/`  
**Files to Submit:** Files from previous exercise + `*.cpp`, `*.{h, hpp}`  
**Forbidden:** None

Les constructeurs et destructeurs de chaque classe doivent afficher des messages spécifiques.

Implémentez une classe `Brain`. Elle contient un tableau de 100 `std::string` appelé `ideas`.

De cette façon, Dog et Cat auront un attribut privé `Brain*`.

Lors de la construction, Dog et Cat créeront leur Brain en utilisant `new Brain();`

Lors de la destruction, Dog et Cat supprimeront leur Brain.

Dans votre fonction main, créez et remplissez un tableau d'objets `Animal`. La moitié sera des objets Dog et l'autre moitié sera des objets Cat. À la fin de l'exécution de votre programme, parcourez ce tableau et supprimez chaque Animal. Vous devez supprimer directement les chiens et les chats en tant qu'Animals. Les destructeurs appropriés doivent être appelés dans l'ordre attendu.

N'oubliez pas de vérifier les fuites de mémoire.

Une copie d'un Dog ou d'un Cat ne doit pas être superficielle. Ainsi, vous devez tester que vos copies sont des copies profondes !

```cpp
int main()
{
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    
    delete j; // ne doit pas créer de fuite
    delete i;
    ...
    return 0;
}
```

Implémentez et rendez plus de tests que ceux donnés ci-dessus.

---

## Exercise 02: Abstract class

**Directory:** `ex02/`  
**Files to Submit:** Files from previous exercise + `*.cpp`, `*.{h, hpp}`  
**Forbidden:** None

Créer des objets Animal n'a pas de sens après tout. C'est vrai, ils ne font aucun son !

Pour éviter toute erreur possible, la classe Animal par défaut ne devrait pas être instanciable.

Corrigez la classe Animal pour que personne ne puisse l'instancier. Tout devrait fonctionner comme avant.

Si vous le souhaitez, vous pouvez mettre à jour le nom de la classe en ajoutant un préfixe A à Animal.

---

## Exercise 03: Interface & recap

**Directory:** `ex03/`  
**Files to Submit:** `Makefile`, `main.cpp`, `*.cpp`, `*.{h, hpp}`  
**Forbidden:** None

Les interfaces n'existent pas en C++98 (ni même en C++20). Cependant, les classes abstraites pures sont communément appelées interfaces. Ainsi, dans ce dernier exercice, essayons d'implémenter des interfaces afin de vous assurer que vous comprenez ce module.

Complétez la définition de la classe `AMateria` suivante et implémentez les fonctions membres nécessaires :

```cpp
class AMateria
{
protected:
    [...]

public:
    AMateria(std::string const & type);
    [...]
    
    std::string const & getType() const; // Retourne le type de materia
    
    virtual AMateria* clone() const = 0;
    virtual void use(ICharacter& target);
};
```

Implémentez les classes concrètes pour les Materias : `Ice` et `Cure`. Utilisez leurs noms en minuscules ("ice" pour Ice, "cure" pour Cure) pour définir leurs types. Bien sûr, leur fonction membre `clone()` retournera une nouvelle instance du même type (c'est-à-dire si vous clonez une Materia Ice, vous obtiendrez une nouvelle Materia Ice).

La fonction membre `use(ICharacter&)` affichera :

- **Ice:** "* shoots an ice bolt at \<name\> *"
- **Cure:** "* heals \<name\>'s wounds *"

\<name\> est le nom du Character passé en paramètre. N'imprimez pas les chevrons (< et >).

> Lors de l'affectation d'une Materia à une autre, copier le type n'a pas de sens.

Écrivez la classe concrète `Character` qui implémentera l'interface suivante :

```cpp
class ICharacter
{
public:
    virtual ~ICharacter() {}
    virtual std::string const & getName() const = 0;
    virtual void equip(AMateria* m) = 0;
    virtual void unequip(int idx) = 0;
    virtual void use(int idx, ICharacter& target) = 0;
};
```

Le Character possède un inventaire de 4 emplacements, ce qui signifie au maximum 4 Materias. L'inventaire est vide lors de la construction. Ils équipent les Materias dans le premier emplacement vide qu'ils trouvent, dans l'ordre suivant : de l'emplacement 0 à l'emplacement 3. S'ils essaient d'ajouter une Materia à un inventaire plein, ou d'utiliser/déséquiper une Materia inexistante, rien ne devrait se passer (mais les bugs sont toujours interdits). La fonction membre `unequip()` ne doit PAS supprimer la Materia !

Gérez les Materias que votre personnage laisse par terre comme vous le souhaitez. Sauvegardez les adresses avant d'appeler `unequip()`, ou autre chose, mais n'oubliez pas que vous devez éviter les fuites de mémoire.

> Sauvegardez les adresses avant d'appeler unequip(), ou autre chose, mais n'oubliez pas que vous devez éviter les fuites de mémoire.

La fonction membre `use(int, ICharacter&)` devra utiliser la Materia à l'emplacement[idx], et passer le paramètre target à la fonction `AMateria::use`.

> L'inventaire de votre personnage pourra supporter n'importe quel type d'AMateria.

Votre Character doit avoir un constructeur prenant son nom en paramètre. Toute copie (en utilisant le constructeur de copie ou l'opérateur d'affectation de copie) d'un Character doit être profonde. Lors de la copie, les Materias d'un Character doivent être supprimées avant que les nouvelles ne soient ajoutées à leur inventaire. Bien sûr, les Materias doivent être supprimées lorsqu'un Character est détruit.

Écrivez la classe concrète `MateriaSource` qui implémentera l'interface suivante :

```cpp
class IMateriaSource
{
public:
    virtual ~IMateriaSource() {}
    virtual void learnMateria(AMateria*) = 0;
    virtual AMateria* createMateria(std::string const & type) = 0;
};
```

### `learnMateria(AMateria*)`

Copie la Materia passée en paramètre et la stocke en mémoire afin qu'elle puisse être clonée plus tard. Comme le Character, le MateriaSource peut connaître au maximum 4 Materias. Elles ne sont pas nécessairement uniques.

### `createMateria(std::string const &)`

Retourne une nouvelle Materia. Cette dernière est une copie de la Materia précédemment apprise par le MateriaSource dont le type est égal à celui passé en paramètre. Retourne 0 si le type est inconnu.

En résumé, votre MateriaSource doit pouvoir apprendre des "templates" de Materias pour les créer au besoin. Ensuite, vous pourrez générer une nouvelle Materia en utilisant simplement une string qui identifie son type.

L'exécution de ce code :

```cpp
int main()
{
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    
    ICharacter* me = new Character("me");
    
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    
    ICharacter* bob = new Character("bob");
    
    me->use(0, *bob);
    me->use(1, *bob);
    
    delete bob;
    delete me;
    delete src;
    
    return 0;
}
```

Devrait afficher :

```
$> clang++ -W -Wall -Werror *.cpp
$> ./a.out | cat -e
* shoots an ice bolt at bob *$
* heals bob's wounds *$
```

Comme d'habitude, implémentez et rendez plus de tests que ceux donnés ci-dessus.

> Vous pouvez passer ce module sans faire l'exercice 03.

---

## Soumission et évaluation

Soumettez votre travail dans votre dépôt Git comme d'habitude. Seul le travail à l'intérieur de votre dépôt sera évalué pendant la défense. N'hésitez pas à vérifier les noms de vos dossiers et fichiers pour vous assurer qu'ils sont corrects.

Pendant l'évaluation, une brève modification du projet peut occasionnellement être demandée. Cela pourrait impliquer un changement de comportement mineur, quelques lignes de code à écrire ou réécrire, ou une fonctionnalité facile à ajouter.

Bien que cette étape ne soit pas applicable à tous les projets, vous devez être prêt si elle est mentionnée dans les directives d'évaluation.

Cette étape vise à vérifier votre compréhension réelle d'une partie spécifique du projet. La modification peut être effectuée dans n'importe quel environnement de développement de votre choix (par exemple, votre configuration habituelle), et elle devrait être réalisable en quelques minutes — à moins qu'un délai spécifique ne soit défini dans le cadre de l'évaluation.

Vous pouvez, par exemple, être invité à effectuer une petite mise à jour d'une fonction ou d'un script, modifier un affichage, ou ajuster une structure de données pour stocker de nouvelles informations, etc.

Les détails (portée, cible, etc.) seront spécifiés dans les directives d'évaluation et peuvent varier d'une évaluation à l'autre pour le même projet.
