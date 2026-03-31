#include <iostream>

// ---- Inclusion conditionnelle : si les fichiers n'existent pas, le test fail proprement ----
#if __has_include("Shape.hpp") && __has_include("Circle.hpp") && __has_include("Rectangle.hpp")
# include "Shape.hpp"
# include "Circle.hpp"
# include "Rectangle.hpp"
# define FILES_FOUND 1
#else
# define FILES_FOUND 0
#endif

static void printResult(const char* testName, bool passed)
{
    std::cout << (passed ? "[PASS] " : "[FAIL] ") << testName << std::endl;
}

int main()
{
#if FILES_FOUND == 0
    std::cout << "[ERROR] Fichiers manquants : Shape.hpp, Circle.hpp ou Rectangle.hpp" << std::endl;
    std::cout << "        Implémente les classes d'abord." << std::endl;
    return 1;
#else

    std::cout << "=== TEST ex00: Héritage simple ===" << std::endl;

    // 1. Type correct
    {
        Circle c(3.0f);
        Rectangle r(4.0f, 5.0f);
        printResult("Circle::getType() == 'Circle'", c.getType() == "Circle");
        printResult("Rectangle::getType() == 'Rectangle'", r.getType() == "Rectangle");
    }

    // 2. getArea() via objet direct (dispatch statique)
    {
        Circle c(1.0f);       // pi * 1^2 ≈ 3.14
        Rectangle r(3.0f, 4.0f); // 12.0
        float ca = c.getArea();
        float ra = r.getArea();
        printResult("Circle::getArea() > 3.0f", ca > 3.0f && ca < 3.2f);
        printResult("Rectangle::getArea() == 12.0f", ra > 11.9f && ra < 12.1f);
    }

    // 3. Via pointeur de base SANS virtual → appelle Shape::getArea() (retourne 0.0)
    //    C'est le comportement ATTENDU pour cet exercice (avant virtual)
    {
        Shape* s = new Circle(5.0f);
        float area = s->getArea();
        printResult("Shape* → getArea() retourne 0 (pas de virtual)", area == 0.0f);
        delete s;
    }

    // 4. Shape de base : getArea retourne 0
    {
        Shape base;
        printResult("Shape::getArea() == 0.0f", base.getArea() == 0.0f);
    }

    std::cout << std::endl;
    std::cout << "Note: via pointeur Shape*, getArea() retourne 0 car pas de virtual." << std::endl;
    std::cout << "      C'est exactement le problème que resout ex01 (virtual)." << std::endl;
    return 0;
#endif
}
