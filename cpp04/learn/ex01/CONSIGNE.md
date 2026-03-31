# ex01 — Fonctions virtuelles

Reprendre l'exercice précédent et ajouter `virtual` pour activer le dispatch dynamique.

## À implémenter

Crée deux versions de `Shape` dans le même exercice pour comparer :

- **`WrongShape`** : `getArea()` **non-virtual** (copie de ex00)
- **`Shape`** : `getArea()` **virtual** → la bonne version

Dérive de chacune :
- `WrongCircle : WrongShape` — `getArea()` masqué (pas d'override réel)
- `Circle : Shape` — `getArea()` virtual override

## Deliverables

```
WrongShape.hpp / WrongShape.cpp
WrongCircle.hpp / WrongCircle.cpp
Shape.hpp / Shape.cpp
Circle.hpp / Circle.cpp
```

Signatures clés :
```cpp
class Shape {
public:
    virtual float getArea() const;   // virtual !
    virtual ~Shape();                // destructeur aussi !
};

class Circle : public Shape {
public:
    float getArea() const;           // override implicite
};
```

## Compiler & tester

```bash
c++ -std=c++98 -Wall -Wextra -Werror WrongShape.cpp WrongCircle.cpp Shape.cpp Circle.cpp test.cpp -o test && ./test
```
