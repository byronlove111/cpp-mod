#include <iostream>

#if __has_include("Unsafe.hpp") && __has_include("SafeChild.hpp") && \
    __has_include("Safe.hpp") && __has_include("SafeChild2.hpp")
# include "Unsafe.hpp"
# include "SafeChild.hpp"
# include "Safe.hpp"
# include "SafeChild2.hpp"
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

    std::cout << "=== TEST ex02: Destructeur virtuel ===" << std::endl;
    std::cout << std::endl;

    // Test visuel : observe les messages affichés
    // Tu dois voir QUELS destructeurs sont appelés

    std::cout << "-- Cas UNSAFE (destructeur non-virtual) --" << std::endl;
    std::cout << "   Expected: seulement ~Unsafe() affiché, ~SafeChild() MANQUANT" << std::endl;
    {
        Unsafe* u = new SafeChild();
        delete u;
    }
    std::cout << std::endl;

    std::cout << "-- Cas SAFE (destructeur virtual) --" << std::endl;
    std::cout << "   Expected: ~SafeChild2() PUIS ~Safe() tous les deux affichés" << std::endl;
    {
        Safe* s = new SafeChild2();
        delete s;
    }
    std::cout << std::endl;

    // Test de construction directe (toujours correct)
    {
        std::cout << "-- Destruction directe (toujours correct) --" << std::endl;
        SafeChild sc;
        SafeChild2 sc2;
    }
    std::cout << std::endl;

    printResult("Compilation OK (toutes les classes existent)", true);
    std::cout << std::endl;
    std::cout << "IMPORTANT: Lance avec valgrind pour voir les fuites mémoire :" << std::endl;
    std::cout << "  valgrind --leak-check=full ./test" << std::endl;
    std::cout << "Le cas Unsafe DOIT montrer des fuites, Safe ne doit pas en avoir." << std::endl;

    return 0;
#endif
}
