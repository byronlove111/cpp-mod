# Notion — Destructeur virtuel

## Le problème

Quand tu supprimes un objet via un **pointeur de classe de base** :

```cpp
Unsafe* u = new SafeChild();
delete u;  // ← Seul ~Unsafe() est appelé !
           //   ~SafeChild() n'est JAMAIS appelé
           //   → fuite mémoire de _childData
```

Le compilateur voit un `Unsafe*`, donc il appelle `Unsafe::~Unsafe()`.  
Il ne sait pas que l'objet est en réalité un `SafeChild`.

## La solution : `virtual ~Base()`

```cpp
class Safe {
public:
    virtual ~Safe() { delete _data; }  // virtual !
};

class SafeChild2 : public Safe {
public:
    ~SafeChild2() { delete _childData; }  // automatiquement virtual
};

Safe* s = new SafeChild2();
delete s;
// Appelle d'abord ~SafeChild2(), PUIS ~Safe()
// Les deux ressources sont libérées correctement
```

## Ordre de destruction

La destruction est toujours dans l'ordre **inverse de la construction** :

1. `SafeChild2::~SafeChild2()`
2. `Safe::~Safe()`

## Règle d'or

> **Toute classe destinée à être héritée DOIT avoir un destructeur virtual.**

En particulier :

- Si ta classe a des méthodes `virtual` → mets `virtual ~MaClasse()`
- Si tu fais `delete ptr_base` → le destructeur de base DOIT être virtual

## Lien avec cpp04

Dans `cpp04/ex01`, tu fais :

```cpp
const Animal* j = new Dog();
delete j;  // Dog::~Dog() doit être appelé pour delete le Brain*
```

Sans `virtual ~Animal()`, le `Brain` de Dog ne serait jamais détruit → **memory leak**.
