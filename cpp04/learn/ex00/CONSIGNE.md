# ex00 — Héritage simple

Créer une hiérarchie de classes avec héritage sans `virtual`.

## À implémenter

- Classe `Shape` avec un attribut protégé `std::string _type` et une méthode `getArea()` retournant `0.0`
- Classe `Circle` hérite de `Shape`, prend un `float radius` en constructeur, surcharge `getArea()`
- Classe `Rectangle` hérite de `Shape`, prend `float width, float height`, surcharge `getArea()`
- Chaque constructeur/destructeur affiche un message

## Deliverables

```
Shape.hpp / Shape.cpp
Circle.hpp / Circle.cpp
Rectangle.hpp / Rectangle.cpp
```

Signatures attendues :
```cpp
class Shape {
protected:
    std::string _type;
public:
    Shape();
    ~Shape();
    std::string getType() const;
    float       getArea() const;  // retourne 0.0
};

class Circle : public Shape {
public:
    Circle(float radius);
    ~Circle();
    float getArea() const;
};
```

## Compiler & tester

```bash
c++ -std=c++98 -Wall -Wextra -Werror Shape.cpp Circle.cpp Rectangle.cpp test.cpp -o test && ./test
```
