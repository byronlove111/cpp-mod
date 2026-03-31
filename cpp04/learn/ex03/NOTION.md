# Notion — Copie profonde (Deep Copy)

## Pourquoi ?

Quand une classe possède un attribut **pointeur**, la copie par défaut copie
**l'adresse** — pas la valeur pointée. Les deux objets partagent alors la même mémoire :

```
Bot a;     →  a._memory ──► [Memory @ 0x100]
Bot b = a; →  b._memory ──► [Memory @ 0x100]  ← MÊME adresse !

delete a;  →  [Memory @ 0x100] libérée
delete b;  →  DOUBLE FREE → crash
```

## La Forme Canonique Orthodoxe (FCO)

En C++98, chaque classe avec une ressource doit implémenter ces 4 éléments :

```cpp
class Bot {
public:
    Bot();                              // 1. Constructeur par défaut
    Bot(const Bot& other);             // 2. Constructeur de copie
    Bot& operator=(const Bot& other);  // 3. Opérateur d'assignation
    ~Bot();                            // 4. Destructeur
};
```

## Implémentation d'une deep copy

```cpp
// Constructeur de copie : crée une NOUVELLE Memory
Bot::Bot(const Bot& other) {
    _memory = new Memory(*other._memory);  // copie le contenu, pas l'adresse
}

// Opérateur = : libère l'ancienne, crée une nouvelle
Bot& Bot::operator=(const Bot& other) {
    if (this != &other) {          // garde contre l'auto-assignation
        delete _memory;            // libère l'ancienne ressource
        _memory = new Memory(*other._memory);
    }
    return *this;
}
```

## Vérification

```
Bot a;
a.setIdea(0, "dominate the world");

Bot b = a;                         // deep copy
b.setIdea(0, "eat pizza");        // modifie b

a.getIdea(0) == "dominate the world"  ← inchangé !
b.getIdea(0) == "eat pizza"
```

## Pitfalls

- Oublier `if (this != &other)` → `a = a` libère sa propre mémoire avant de copier
- Copier l'adresse au lieu du contenu → les deux objets modifient les mêmes données
- Ne pas copier dans `operator=` → la vieille mémoire fuit
