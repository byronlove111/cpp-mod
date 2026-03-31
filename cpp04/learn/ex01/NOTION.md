# Notion — Fonctions virtuelles

## Pourquoi ?

Sans `virtual`, quand tu appelles une méthode via un **pointeur de classe de base**,
le compilateur utilise le type **statique** (le type du pointeur) — pas l'objet réel.

`virtual` force le programme à regarder le **vrai type** de l'objet à l'exécution.

## Mécanisme : la vtable

Chaque classe avec des méthodes virtuelles possède une **table de pointeurs de fonctions** (vtable).
Chaque objet contient un pointeur caché vers cette table (vptr).

```
objet Circle {
    vptr ──► vtable de Circle {
                 getArea → &Circle::getArea   ← c'est celle-ci qui sera appelée
             }
}
```

## Comparaison directe

```cpp
// SANS virtual
class WrongShape { float getArea() const { return 0.0f; } };
class WrongCircle : public WrongShape { float getArea() const { return 3.14f; } };

WrongShape* s = new WrongCircle();
s->getArea();   // → 0.0f  (type statique = WrongShape)

// AVEC virtual
class Shape { virtual float getArea() const { return 0.0f; } };
class Circle : public Shape { float getArea() const { return 3.14f; } };

Shape* s2 = new Circle(1.0f);
s2->getArea();  // → 3.14f (type dynamique = Circle)  ← POLYMORPHISME
```

## Lien avec cpp04

Dans `cpp04/ex00`, le sujet demande de faire un `WrongAnimal`/`WrongCat` sans virtual :
le `WrongCat` via un pointeur `WrongAnimal*` produit le son du **WrongAnimal**.
C'est exactement ce comportement "wrong" que `virtual` corrige.

## À retenir

- `virtual` active le **dispatch dynamique** (décision à l'exécution)
- Sans `virtual` → **dispatch statique** (décision à la compilation selon le type du pointeur)
- Mettre `virtual` sur la méthode de la base suffit (propagé aux dérivées)
- Mais il faut aussi rendre le **destructeur virtual** (voir ex02)
