# ex04 — Classe abstraite (pure virtual)

Créer une classe abstraite qui ne peut pas être instanciée directement.

## À implémenter

- Classe **`AShape`** (abstraite) :
  - `virtual float getArea() const = 0;` ← pure virtual
  - `virtual std::string getType() const = 0;` ← pure virtual
  - `virtual ~AShape();` ← destructeur virtual
  - Attribut protégé `std::string _type`

- Classe **`ACircle : public AShape`** (concrète) :
  - Implémente `getArea()` et `getType()`
  - Constructeur avec `float radius`

- Classe **`ASquare : public AShape`** (concrète) :
  - Implémente `getArea()` et `getType()`
  - Constructeur avec `float side`

**Ne pas** implémenter `getArea()` dans `AShape` (c'est une pure virtual).

## Deliverables

```
AShape.hpp / AShape.cpp
ACircle.hpp / ACircle.cpp
ASquare.hpp / ASquare.cpp
```

Signature clé :
```cpp
class AShape {
public:
    virtual float       getArea() const = 0;   // pure virtual
    virtual std::string getType() const = 0;   // pure virtual
    virtual ~AShape();
};
```

## Compiler & tester

```bash
c++ -std=c++98 -Wall -Wextra -Werror AShape.cpp ACircle.cpp ASquare.cpp test.cpp -o test && ./test
```
