#include <iostream>

#if __has_include("Shape.hpp") && __has_include("Circle.hpp") && \
    __has_include("WrongShape.hpp") && __has_include("WrongCircle.hpp")
# include "Shape.hpp"
# include "Circle.hpp"
# include "WrongShape.hpp"
# include "WrongCircle.hpp"
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
    std::cout << "[ERROR] Fichiers manquants. Implémente les classes d'abord." << std::endl;
    return 1;
#else

    std::cout << "=== TEST ex01: Virtual vs Non-Virtual ===" << std::endl;

    // --- Comportement WRONG (sans virtual) ---
    std::cout << "\n-- WrongShape (non-virtual) --" << std::endl;
    {
        WrongShape* ws = new WrongCircle(5.0f);
        float area = ws->getArea();
        // Doit retourner 0.0 : la méthode de WrongShape est appelée, pas celle de WrongCircle
        printResult("WrongShape* → getArea() == 0 (dispatch statique)", area == 0.0f);
        delete ws;
    }

    // --- Comportement CORRECT (avec virtual) ---
    std::cout << "\n-- Shape (virtual) --" << std::endl;
    {
        Shape* s = new Circle(1.0f);  // pi * 1^2 ≈ 3.14
        float area = s->getArea();
        // Doit retourner ~3.14 : le vrai objet (Circle) est consulté
        printResult("Shape* → getArea() > 3.0 (dispatch dynamique)", area > 3.0f && area < 3.2f);
        delete s;
    }

    // --- Appel direct (toujours correct même sans virtual) ---
    std::cout << "\n-- Appel direct sur l'objet --" << std::endl;
    {
        WrongCircle wc(1.0f);
        Circle c(1.0f);
        printResult("WrongCircle direct → getArea() > 3.0", wc.getArea() > 3.0f);
        printResult("Circle direct     → getArea() > 3.0", c.getArea() > 3.0f);
    }

    std::cout << std::endl;
    std::cout << "Résumé: virtual = le BON objet est appelé via pointeur de base." << std::endl;
    return 0;
#endif
}
