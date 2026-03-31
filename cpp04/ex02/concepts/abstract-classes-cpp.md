# Classes abstraites et interfaces en C++

## Before You Start

To understand this, you need to be comfortable with:

- **Héritage** — tu sais qu'une classe peut hériter d'une autre et récupérer ses méthodes
- **Fonctions virtuelles** — tu sais que `virtual` permet au bon destructeur/méthode d'être appelé via un pointeur de base
- **Pointeurs** — tu manipules des `Animal*` qui pointent vers des `Dog` ou `Cat`

If any of these feel shaky, understand them first — this explanation builds directly on them.

---

## The Hook

Tu as une classe `Animal`. Tu peux faire `new Animal()`. Mais c'est quoi un "Animal" tout seul, sans être un chien ou un chat ? Ça n'existe pas dans la vraie vie. Alors pourquoi le compilateur te laisse faire ça sans broncher ? Et si tu pouvais lui dire : *"cette classe n'est qu'un contrat, personne n'a le droit de l'instancier directement"* ?

---

## Life Without It — The Pain

Lucas bosse sur un jeu vidéo. Il a une classe `Shape` avec une méthode `draw()`. Il a `Circle`, `Square`, `Triangle` qui héritent de `Shape`.

Le problème : n'importe qui dans l'équipe peut faire `new Shape()` et appeler `draw()`. Mais `Shape` tout seul n'a pas de sens — qu'est-ce que ça dessine ? Un truc vide ? Une erreur silencieuse ?

Lucas se retrouve avec des bugs bizarres parce qu'un collègue a oublié de choisir la bonne sous-classe et a instancié `Shape` directement. Le compilateur n'a rien dit. Aucune erreur. Juste un comportement inattendu au runtime.

*Il doit exister un moyen de dire au compilateur : "Shape ne peut pas exister seul, point."*

---

## The Invention Story

Les concepteurs de C++ se sont posé la question : comment forcer les développeurs à n'utiliser une classe que comme un modèle, jamais comme un objet réel ?

L'insight clé : *une classe qui a une méthode sans implémentation ne peut pas être instanciée* — parce que si tu crées un objet et que tu appelles la méthode, il n'y a rien à exécuter.

Ils ont inventé la syntaxe `= 0` pour marquer une méthode comme **"non implémentée ici, quelqu'un d'autre doit le faire"**. On appelle ça une **fonction virtuelle pure**.

Dès qu'une classe en a une, elle devient **abstraite** : le compilateur bloque toute tentative d'instanciation directe.

---

## The Core Idea — One Sentence

Une classe abstraite est une classe incomplète volontairement — elle définit un contrat que ses sous-classes sont **obligées** de remplir.

---

## Think of It Like... (3 Analogies)

**Architecture** : un plan d'architecte définit qu'un bâtiment "doit avoir des fenêtres", mais le plan lui-même n'est pas un bâtiment — tu ne peux pas habiter dedans.  
→ Ici : la classe abstraite = le plan, les sous-classes = les bâtiments construits.  
→ Où ça casse : un plan peut rester incomplet indéfiniment, une classe abstraite doit quand même compiler.

**Contrat légal** : un contrat de travail dit "l'employé devra effectuer des livraisons". Il ne dit pas comment. Chaque employé (livreur, coursier, chauffeur) implémente ça à sa façon.  
→ Ici : le contrat = la classe abstraite, les employés = les sous-classes, "effectuer des livraisons" = la méthode pure virtual.  
→ Où ça casse : un contrat peut ne jamais être signé, une sous-classe doit forcément implémenter toutes les méthodes pures sinon elle est abstraite aussi.

**Recette de cuisine** : une recette dit "ajouter une viande". Elle ne précise pas laquelle. Chaque cuisinier choisit bœuf, poulet ou tofu — mais tous respectent l'étape "ajouter une viande".  
→ Ici : la recette = la classe abstraite, chaque version du plat = une sous-classe concrète.  
→ Où ça casse : une recette peut être délicieuse à lire, une classe abstraite ne "fait" rien toute seule.

---

## Example Cascade

**Exemple 1 — Le plus simple possible**

```cpp
class Shape {
public:
    virtual void draw() const = 0; // pure virtual
};

// Shape s; // ERREUR de compilation — Shape est abstraite
```

Le compilateur refuse. C'est tout ce qu'on veut.

---

**Exemple 2 — Une sous-classe qui implémente le contrat**

```cpp
class Circle : public Shape {
public:
    void draw() const {
        std::cout << "Dessin d'un cercle" << std::endl;
    }
};

Circle c; // OK — Circle a implémenté draw()
```

`Circle` est concrète parce qu'elle remplit le contrat.

---

**Exemple 3 — Utilisation via pointeur de base (le vrai use case)**

```cpp
Shape* shapes[3];
shapes[0] = new Circle();
shapes[1] = new Square();
shapes[2] = new Triangle();

for (int i = 0; i < 3; i++)
    shapes[i]->draw(); // appelle la bonne méthode grâce au virtual
```

Tu manipules tout via `Shape*` sans savoir le type réel — et ça fonctionne parfaitement. C'est le polymorphisme.

---

**Exemple 4 — Sous-classe qui oublie d'implémenter**

```cpp
class WeirdShape : public Shape {
    // oubli de draw()
};

WeirdShape w; // ERREUR — WeirdShape est abstraite aussi !
```

Si une sous-classe n'implémente pas toutes les méthodes pures, elle devient abstraite à son tour. Le compilateur te force à compléter le contrat.

---

**Exemple 5 — Classe abstraite partielle (ton cas dans ex02)**

```cpp
class AAnimal {
protected:
    std::string type;
public:
    AAnimal(std::string t) : type(t) {}
    std::string getType() const { return type; } // implémentée
    virtual void makeSound() const = 0;          // pure virtual
    virtual ~AAnimal() {}
};
```

`AAnimal` a du comportement concret (`getType`) ET une méthode pure virtual. Elle n'est pas une interface pure — c'est une classe abstraite partielle. C'est le pattern le plus courant en C++.

---

**Exemple 6 — L'interface pure (100% virtuel)**

```cpp
class IAnimal {
public:
    virtual void makeSound() const = 0;
    virtual std::string getType() const = 0;
    virtual ~IAnimal() {}
};
```

Aucun attribut, aucune implémentation. C'est l'équivalent exact d'une interface Java ou d'un trait Rust. En C++ on préfixe souvent avec `I` par convention.

---

## Test Your Intuition

> **Question** : Tu as une classe `Vehicle` avec `virtual void move() const = 0`. Tu crées `class Boat : public Vehicle` mais tu oublies d'implémenter `move()`. Que se passe-t-il si tu fais `Boat b;` ?

<details>
<summary>Réponse</summary>

Erreur de compilation. `Boat` n'implémente pas `move()`, donc elle hérite de la méthode pure virtual de `Vehicle` et devient abstraite à son tour. Tu ne peux pas l'instancier.

</details>

---

> **Question** : Tu fais `Vehicle* v = new Boat();`. Est-ce que ça compile si `Boat` implémente correctement `move()` ?

<details>
<summary>Réponse</summary>

Oui. `Vehicle` est abstraite donc tu ne peux pas faire `new Vehicle()`, mais tu peux avoir un **pointeur** vers `Vehicle` qui pointe vers une sous-classe concrète. C'est exactement le but — manipuler des `Vehicle*` sans connaître le type réel.

</details>

---

> **Question** : Quelle est la différence entre `virtual void makeSound() const {}` et `virtual void makeSound() const = 0` ?

<details>
<summary>Réponse</summary>

La première a une implémentation vide — la classe reste instanciable, et si tu ne l'override pas dans la sous-classe, ça appelle la version vide sans erreur.

La deuxième n'a aucune implémentation — la classe devient abstraite, et la sous-classe est **obligée** d'implémenter la méthode sinon elle ne compile pas.

</details>

---

## What It's NOT — Misconceptions

**"Une classe abstraite ne peut avoir aucun code."**  
Faux. Elle peut avoir des attributs, des constructeurs, des méthodes implémentées. La seule contrainte : au moins une méthode pure virtual. Ton `AAnimal` a un `type`, un `getType()`, un constructeur — et elle est quand même abstraite.

**"On ne peut pas avoir de pointeur vers une classe abstraite."**  
Faux. On ne peut pas instancier une classe abstraite, mais `AAnimal*` est parfaitement valide et c'est exactement ce qu'on utilise pour faire du polymorphisme. `AAnimal* a = new Dog();` fonctionne.

**"= 0 signifie que la méthode retourne 0."**  
Non. `= 0` n'a rien à voir avec la valeur de retour. C'est une syntaxe C++ spéciale qui dit "cette méthode n'a pas d'implémentation ici". Ça ne s'applique qu'aux fonctions virtuelles.

**"Les interfaces n'existent pas en C++."**  
Elles n'ont pas de mot-clé dédié, mais on les simule avec des classes abstraites où **toutes** les méthodes sont pure virtual. C'est fonctionnellement identique à une interface Java.

---

## The Big Picture — Where Does This Live?

Les classes abstraites appartiennent au monde du **polymorphisme** — le fait de manipuler des objets de types différents via une interface commune.

Elles dépendent de :
- **Héritage** — sans héritage, pas de sous-classes pour remplir le contrat
- **Fonctions virtuelles** — sans `virtual`, le polymorphisme ne fonctionne pas

Elles sont utilisées par :
- **Tout pattern de conception** qui repose sur une abstraction (Strategy, Factory, Observer...)
- **Les APIs** qui veulent exposer une interface sans exposer leur implémentation

Quand l'utiliser : dès que tu as un concept qui ne devrait jamais exister seul (Animal, Shape, Vehicle) mais qui définit un comportement commun à plusieurs types.

Quand ne pas l'utiliser : si toutes tes classes sont concrètes et que tu n'as pas besoin de polymorphisme — c'est inutilement complexe.
