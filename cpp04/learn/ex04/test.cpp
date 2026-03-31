#include <iostream>
#include <string>

#if __has_include("AShape.hpp") && __has_include("ACircle.hpp") && __has_include("ASquare.hpp")
# include "AShape.hpp"
# include "ACircle.hpp"
# include "ASquare.hpp"
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
    std::cout << "[ERROR] Fichiers manquants : AShape.hpp, ACircle.hpp ou ASquare.hpp" << std::endl;
    return 1;
#else

    std::cout << "=== TEST ex04: Classe abstraite ===" << std::endl;

    // Note : tenter de compiler "AShape s;" doit échouer à la compilation
    // Décommente la ligne suivante pour vérifier :
    // AShape s;  // DOIT provoquer une erreur de compilation

    // 1. Instanciation des classes concrètes uniquement
    {
        ACircle c(1.0f);
        ASquare s(4.0f);
        printResult("ACircle instanciable", true);
        printResult("ASquare instanciable", true);
    }

    // 2. Polymorphisme via pointeur abstrait
    {
        AShape* shapes[3];
        shapes[0] = new ACircle(1.0f);     // area ≈ 3.14
        shapes[1] = new ASquare(4.0f);     // area = 16.0
        shapes[2] = new ACircle(2.0f);     // area ≈ 12.56

        printResult("AShape* → ACircle::getArea() > 3.0",
                    shapes[0]->getArea() > 3.0f && shapes[0]->getArea() < 3.2f);
        printResult("AShape* → ASquare::getArea() == 16.0",
                    shapes[1]->getArea() > 15.9f && shapes[1]->getArea() < 16.1f);
        printResult("AShape* → getType() == 'Circle'",
                    shapes[0]->getType() == "Circle");
        printResult("AShape* → getType() == 'Square'",
                    shapes[1]->getType() == "Square");

        for (int i = 0; i < 3; i++)
            delete shapes[i];   // ~ACircle() / ~ASquare() doivent être appelés
    }

    // 3. Dispatch dynamique dans un tableau
    {
        AShape* arr[4];
        arr[0] = new ACircle(1.0f);
        arr[1] = new ASquare(2.0f);
        arr[2] = new ACircle(3.0f);
        arr[3] = new ASquare(1.0f);

        float totalArea = 0.0f;
        for (int i = 0; i < 4; i++)
            totalArea += arr[i]->getArea();

        printResult("Tableau AShape*: totalArea > 0", totalArea > 0.0f);

        for (int i = 0; i < 4; i++)
            delete arr[i];
    }

    std::cout << std::endl;
    std::cout << "Pour vérifier qu'AShape n'est pas instanciable, décommente" << std::endl;
    std::cout << "la ligne 'AShape s;' dans test.cpp : doit refuser de compiler." << std::endl;
    return 0;
#endif
}
