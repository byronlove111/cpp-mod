# Destructeur virtuel

---

## Before You Start

To understand this, you need to be comfortable with:

- **Héritage** — tu sais qu'une classe fille hérite d'une classe mère
- **Pointeurs** — tu sais qu'un `Dog*` peut être stocké derrière un `Animal*`
- **`new` / `delete`** — tu sais qu'allouer avec `new` nécessite de libérer avec `delete`
- **Fonctions virtuelles** — tu sais qu'elles permettent d'appeler la version de la classe fille via un pointeur de base

Si une de ces notions est floue, commence par là.

---

## 1. Le Hook

Tu crées un `Dog`. Tu lui alloues un `Brain`. Tu le supprimes. Et pourtant, Valgrind te crie dessus pour une fuite mémoire.

Tu as écrit `delete`. Tu as tout fait correctement. Alors pourquoi le `Brain` n'est jamais libéré ?

---

## 2. La Douleur — La Vie Sans Ça

Imagine ce code :

```cpp
Animal* a = new Dog();
delete a;
```

Tu t'y attends : `delete a` détruit le `Dog`, appelle son destructeur `~Dog()`, lequel appelle `delete brain_` → tout est propre.

Mais ce n'est pas ce qui se passe.

Le compilateur regarde `a`. Son type statique (celui écrit dans le code) est `Animal*`. Donc il appelle `~Animal()`. Pas `~Dog()`.

Le `Brain` alloué dans `Dog` n'est **jamais supprimé**. Il est perdu dans la mémoire pour toujours.

Tu as fait tout bien. Et tu as quand même une fuite. Il doit y avoir un moyen de dire au compilateur : "hé, pour la destruction, regarde le vrai type, pas le type du pointeur."

---

## 3. L'Histoire de l'Invention

Les fonctions virtuelles existent pour résoudre exactement ça : au lieu d'écouter le type statique du pointeur, le programme regarde le **vrai type de l'objet** à l'exécution.

Tu le savais déjà pour `makeSound()` : appeler `a->makeSound()` sur un `Dog` appelle bien `Dog::makeSound()`, même si `a` est un `Animal*`. C'est le dispatch dynamique.

Quelqu'un a réalisé que le destructeur, c'est juste une fonction comme les autres. Rien de magique. Si on le rend `virtual`, le même mécanisme s'applique : au moment du `delete`, le programme regarde le vrai type de l'objet, trouve `~Dog()`, et l'appelle.

La règle d'or : **le destructeur est une fonction membre. Rends-le `virtual`, et il se comporte comme toutes tes autres fonctions virtuelles.**

---

## 4. L'Idée Centrale — Une Phrase

Un destructeur virtuel garantit que quand tu `delete` un objet via un pointeur de base, c'est le destructeur de la vraie classe qui est appelé, pas celui du pointeur.

---

## 5. Pense-y Comme...

**Un hôtel** : Tu réserves une chambre sous le nom "Personne" (type de base). À ton départ (destruction), si la réception utilise ton vrai nom pour récupérer tes effets personnels, tu repars avec tout. Si elle utilise uniquement "Personne", tes affaires restent dans la chambre pour toujours (fuite).
→ `virtual` = "utiliser le vrai nom au départ".
→ Où ça casse : dans un hôtel, la réception sait toujours qui tu es. En C++, sans `virtual`, le compilateur ne cherche pas — il fait aveuglément confiance au type du pointeur.

**Un contrat de sous-traitance** : Tu signes un contrat avec "Entrepreneur Général". À la fin du projet, c'est l'entrepreneur général qui nettoie. Mais si le vrai travail a été sous-traité à une équipe de plombiers qui ont posé des tuyaux dans les murs — et que le nettoyage contractuel ne prévoit pas de les retirer — les tuyaux restent.
→ `virtual ~` = le contrat précise explicitement "nettoyage complet selon le sous-traitant réel".
→ Où ça casse : ici la métaphore parle de gens qui savent ce qu'ils font. Le compilateur, lui, est strictement littéral : sans `virtual`, il ne cherche jamais.

**Une étiquette "Fruit" sur un panier de pommes** : Quelqu'un jette le contenu du panier parce que "Fruit périmé". Mais les pommes avaient un noyau au centre. Le noyau (le `Brain`) n'est pas jeté, il est juste oublié sur la table.
→ `virtual ~` = "détruire le vrai contenu du panier, pas juste ce que dit l'étiquette".
→ Où ça casse : en vrai, un noyau ne cause pas de bug. En C++, un `Brain` oublié c'est de la mémoire perdue.

---

## 6. La Cascade d'Exemples

**Exemple 1 — Le plus simple possible**

```cpp
class Animal {
public:
    ~Animal() { std::cout << "~Animal\n"; } // PAS virtual
};

class Dog : public Animal {
public:
    ~Dog() { std::cout << "~Dog\n"; }
};

Animal* a = new Dog();
delete a; // affiche seulement "~Animal". ~Dog() n'est JAMAIS appelé.
```

**Exemple 2 — Avec `virtual`**

```cpp
class Animal {
public:
    virtual ~Animal() { std::cout << "~Animal\n"; } // virtual
};

class Dog : public Animal {
public:
    ~Dog() { std::cout << "~Dog\n"; }
};

Animal* a = new Dog();
delete a;
// affiche : "~Dog" puis "~Animal". Les deux. Dans l'ordre attendu.
```

`virtual` sur le destructeur de la base suffit. Les destructeurs des classes filles sont automatiquement virtuels par héritage.

**Exemple 3 — Le cas du Brain (exactement ton ex01)**

```cpp
class Dog : public Animal {
private:
    Brain* brain_;
public:
    Dog() { brain_ = new Brain(); }
    ~Dog() { delete brain_; } // ce destructeur doit être appelé !
};

Animal* a = new Dog();
delete a; // sans virtual ~Animal() → Brain jamais supprimé → LEAK
```

**Exemple 4 — Le tableau d'animaux**

```cpp
Animal* zoo[4];
zoo[0] = new Dog();
zoo[1] = new Cat();
zoo[2] = new Dog();
zoo[3] = new Cat();

for (int i = 0; i < 4; i++)
    delete zoo[i]; // sans virtual ~Animal(), aucun Brain n'est libéré
```

**Exemple 5 — La subtilité : supprimer directement par le vrai type**

```cpp
Dog* d = new Dog();
delete d; // ça marche MÊME sans virtual ~Animal()
```

Pourquoi ? Parce que le type statique de `d` est déjà `Dog*`. Le compilateur appelle directement `~Dog()`. Pas de dispatch nécessaire.

Le `virtual` ne sert que quand **le type du pointeur diffère du type réel** — c'est-à-dire uniquement quand tu manipules par un pointeur de classe mère.

---

## 7. Teste Ton Intuition

> **Question 1** : Tu as `Animal* a = new Dog()`. Le destructeur de `Animal` est `virtual`. Que se passe-t-il quand tu fais `delete a` ?

<details>
<summary>Réponse</summary>

Le runtime regarde le vrai type de l'objet pointé : c'est un `Dog`. Il appelle `~Dog()`, puis automatiquement `~Animal()` (la chaîne de destructeurs remonte toujours jusqu'à la base). Le `Brain` est supprimé. Zéro fuite.

</details>

---

> **Question 2** : Tu as `Dog* d = new Dog()`. Le destructeur de `Animal` n'est **pas** `virtual`. Y a-t-il une fuite ?

<details>
<summary>Réponse</summary>

Non. Le type statique de `d` est `Dog*`. Le compilateur appelle directement `~Dog()` sans avoir besoin de dispatch virtuel. `virtual` n'est utile que quand le type du pointeur ne correspond pas au type réel.

</details>

---

> **Question 3** : Pourquoi est-ce que `virtual ~Animal()` suffit ? Pourquoi n'a-t-on pas besoin d'écrire `virtual ~Dog()` aussi ?

<details>
<summary>Réponse</summary>

En C++, quand une fonction est déclarée `virtual` dans une classe mère, **toutes ses redéfinitions dans les classes filles sont automatiquement `virtual`**, même sans le mot-clé. Donc `~Dog()` est implicitement `virtual` dès que `~Animal()` l'est. Une seule déclaration au sommet de la hiérarchie suffit.

</details>

---

## 8. Ce que Ce N'est PAS — Les Malentendus

**"Le destructeur virtuel, c'est pour que le destructeur soit appelé."**
Faux. Le destructeur est *toujours* appelé — c'est juste que sans `virtual`, c'est le mauvais qui est appelé (celui du pointeur, pas celui de l'objet réel).

**"Il faut mettre `virtual` sur tous les destructeurs."**
Faux. Seulement sur les classes conçues pour être héritées et manipulées via pointeur de base. Sur une classe finale ou une classe non-polymorphe, `virtual` ajoute une vtable inutile et alourdit l'objet.

**"Si j'écris `virtual ~Dog()`, c'est suffisant."**
Faux. Il faut le `virtual` sur la **base** (`Animal`). Si `~Animal()` n'est pas `virtual`, même si `~Dog()` l'est, `delete` sur un `Animal*` appellera quand même `~Animal()` directement.

**"Le destructeur virtuel change l'ordre de destruction."**
Faux. L'ordre est toujours : classe fille en premier, puis classe mère en remontant. Le `virtual` ne change pas l'ordre — il garantit juste que le bon destructeur de départ est appelé.

---

## 9. La Grande Image — Où Ça Vit

**Catégorie** : Gestion du cycle de vie des objets en POO.

**Dépend de** : fonctions virtuelles (vtable), héritage, `new`/`delete`.

**Ce qui dépend de ça** :
- Toute classe pensée comme classe de base (ex00 → ex02 du cpp04)
- Toute hiérarchie polymorphe où tu manipules des objets via des pointeurs de base
- Valgrind et l'absence de fuites mémoire dans tes projets 42

**Quand l'utiliser** : dès qu'une classe a au moins une fonction `virtual`, mets son destructeur `virtual`. C'est une règle quasi-systématique.

**Quand ne pas l'utiliser** : classes utilitaires sans héritage, classes `final`, structs simples. Inutile d'ajouter le coût d'une vtable si personne n'hérite.
