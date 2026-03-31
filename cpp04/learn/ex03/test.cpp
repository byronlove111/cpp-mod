#include <iostream>
#include <string>

#if __has_include("Bot.hpp") && __has_include("Memory.hpp")
# include "Memory.hpp"
# include "Bot.hpp"
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
    std::cout << "[ERROR] Fichiers manquants : Memory.hpp ou Bot.hpp" << std::endl;
    return 1;
#else

    std::cout << "=== TEST ex03: Deep Copy ===" << std::endl;

    // 1. Constructeur de copie : les deux objets sont indépendants
    {
        Bot a;
        a.setIdea(0, "dominate the world");

        Bot b(a);                        // copy constructor
        b.setIdea(0, "eat pizza");      // modifie b uniquement

        printResult("Copy ctor: modifier b ne change pas a",
                    a.getIdea(0) == "dominate the world");
        printResult("Copy ctor: b a bien sa propre valeur",
                    b.getIdea(0) == "eat pizza");
    }

    // 2. Opérateur d'assignation : idem
    {
        Bot a;
        a.setIdea(1, "plan A");

        Bot b;
        b = a;                           // operator=
        b.setIdea(1, "plan B");

        printResult("Operator=: modifier b ne change pas a",
                    a.getIdea(1) == "plan A");
        printResult("Operator=: b a bien sa propre valeur",
                    b.getIdea(1) == "plan B");
    }

    // 3. Auto-assignation ne plante pas
    {
        Bot a;
        a.setIdea(2, "survive");
        a = a;
        printResult("Auto-assignation (a = a) ne crash pas",
                    a.getIdea(2) == "survive");
    }

    // 4. Chaîne de copies
    {
        Bot a;
        a.setIdea(3, "original");
        Bot b(a);
        Bot c(b);
        c.setIdea(3, "modified");
        printResult("Chaîne de copies: a inchangé après modif de c",
                    a.getIdea(3) == "original");
    }

    std::cout << std::endl;
    std::cout << "Lance avec valgrind pour vérifier les fuites mémoire." << std::endl;
    return 0;
#endif
}
