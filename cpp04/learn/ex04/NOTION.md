# Notion — Classe abstraite et pure virtual

## Pourquoi ?

Certaines classes sont trop générales pour avoir une implémentation concrète.
`AAnimal` ne fait pas de son — seuls `Dog` et `Cat` en font.

Plutôt que de laisser `AAnimal` instanciable avec un `makeSound()` vide ou inutile,
on la rend **abstraite** : elle définit une interface sans l'implémenter.

## Syntaxe : `= 0`

```cpp
class AShape {
public:
    virtual float getArea() const = 0;  // "= 0" → pure virtual
    virtual ~AShape() {}
};
```

`= 0` signifie : "cette méthode DOIT être implémentée par les classes dérivées".

## Classe abstraite vs classe concrète

```cpp
AShape s;         // ERREUR de compilation : cannot instantiate abstract class
ACircle c(5.0f); // OK : ACircle implémente toutes les pure virtuals

AShape* s = new ACircle(5.0f);  // OK : pointeur vers abstraite, objet concret
s->getArea();    // → appelle ACircle::getArea() via vtable
```

## Classe concrète : implémenter TOUTES les méthodes virtuelles pures

```cpp
class ACircle : public AShape {
    float _radius;
public:
    ACircle(float r) : _radius(r) { _type = "Circle"; }
    float       getArea() const { return 3.14159f * _radius * _radius; }
    std::string getType() const { return _type; }
};
```

Si `ACircle` oublie d'implémenter `getArea()` → `ACircle` devient aussi abstraite.

## Lien avec cpp04

Dans `cpp04/ex02`, `Animal` devient `AAnimal` :
```cpp
class AAnimal {
public:
    virtual void makeSound() const = 0;  // oblige Dog et Cat à l'implémenter
    virtual ~AAnimal();
};

// AAnimal a;  → ERREUR : tu ne peux plus créer un Animal sans cerveau/son
```

C'est un **contrat** : toute classe qui hérite de `AAnimal` **doit** définir `makeSound()`.

## Résumé

| Caractéristique        | Classe normale | Classe abstraite |
|------------------------|----------------|------------------|
| Peut être instanciée   | Oui            | Non              |
| A des pure virtuals    | Non            | Oui (`= 0`)      |
| Peut avoir des méthodes concrètes | Oui | Oui         |
| Peut être un type de pointeur | Oui  | Oui              |
