# Notion — Héritage simple

## Pourquoi ?

L'héritage permet de réutiliser du code et d'exprimer une relation "est-un" :  
`Circle` **est un** `Shape`. Il hérite de ses attributs et méthodes.

## Mécanisme

```cpp
class Shape {
protected:           // accessible dans les classes dérivées (pas à l'extérieur)
    std::string _type;
public:
    float getArea() const { return 0.0f; }
};

class Circle : public Shape {   // Circle hérite de Shape
    float _radius;
public:
    Circle(float r) : _radius(r) {
        _type = "Circle";       // accès à l'attribut protégé
    }
    float getArea() const {     // MASQUE (shadowing) la méthode parente
        return 3.14159f * _radius * _radius;
    }
};
```

## Appel du constructeur parent

Le constructeur de la classe de base est **toujours appelé en premier** :

```cpp
Circle::Circle(float r) : Shape(), _radius(r) { ... }
//                         ^^^^^^^ explicite (ou automatique si défaut)
```

## Piège : sans `virtual`, le dispatch est statique

```cpp
Shape* s = new Circle(5.0f);
s->getArea();   // appelle Shape::getArea() → retourne 0.0 !
                // le compilateur décide à la COMPILATION selon le type du pointeur
```

C'est exactement ce que `WrongAnimal`/`WrongCat` illustre dans cpp04.  
→ C'est pour ça que `virtual` existe (voir ex01).

## À retenir

- `protected` : visible dans la classe et ses dérivées, invisible à l'extérieur
- La surcharge sans `virtual` ne fait que **masquer** la méthode parente
- Via un pointeur de base non-virtual, c'est toujours la méthode de **base** qui est appelée
