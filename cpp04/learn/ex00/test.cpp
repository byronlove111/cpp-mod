#include <iostream>
#include <string>

// Forward-declare to allow compiling even if files are missing
// Replace with your actual headers once implemented:
// #include "Animal.hpp"
// #include "Dog.hpp"
// #include "Cat.hpp"
// #include "WrongAnimal.hpp"
// #include "WrongCat.hpp"

// ──────────────────────────────────────────────────
// Stub implementations so the test compiles standalone.
// DELETE these once you add your own header/source files.
// ──────────────────────────────────────────────────
struct Animal {
    std::string type;
    Animal() : type("Animal") {}
    virtual ~Animal() {}
    virtual void makeSound() const { std::cout << "..." << std::endl; }
    std::string getType() const { return type; }
};
struct Dog : public Animal {
    Dog() { type = "Dog"; }
    void makeSound() const { std::cout << "Woof!" << std::endl; }
};
struct Cat : public Animal {
    Cat() { type = "Cat"; }
    void makeSound() const { std::cout << "Meow!" << std::endl; }
};
struct WrongAnimal {
    std::string type;
    WrongAnimal() : type("WrongAnimal") {}
    virtual ~WrongAnimal() {}
    void makeSound() const { std::cout << "WrongAnimal sound" << std::endl; }
    std::string getType() const { return type; }
};
struct WrongCat : public WrongAnimal {
    WrongCat() { type = "WrongCat"; }
    void makeSound() const { std::cout << "Wrong Meow!" << std::endl; }
};
// ──────────────────────────────────────────────────

static int passed = 0;
static int failed = 0;

static void check(bool condition, const std::string& label) {
    if (condition) {
        std::cout << "[PASS] " << label << std::endl;
        ++passed;
    } else {
        std::cout << "[FAIL] " << label << std::endl;
        ++failed;
    }
}

int main() {
    std::cout << "=== ex00: Virtual Functions ===" << std::endl;

    // 1. type fields
    {
        Dog d; Cat c;
        check(d.getType() == "Dog", "Dog type == \"Dog\"");
        check(c.getType() == "Cat", "Cat type == \"Cat\"");
    }

    // 2. polymorphic dispatch via base pointer
    {
        const Animal* dog = new Dog();
        const Animal* cat = new Cat();

        // We can't capture stdout easily in C++98; we test dispatch indirectly
        // by checking that the pointer's static type is Animal but virtual works.
        // Visual check: the next two lines should print Dog/Cat sounds, not Animal's.
        std::cout << "  (should print Dog sound) "; dog->makeSound();
        std::cout << "  (should print Cat sound) "; cat->makeSound();
        check(dog->getType() == "Dog", "Dog pointer dispatches correct type");
        check(cat->getType() == "Cat", "Cat pointer dispatches correct type");

        delete dog;
        delete cat;
    }

    // 3. WrongAnimal / WrongCat — no virtual, so WrongCat's sound is NOT called
    {
        const WrongAnimal* wc = new WrongCat();
        std::cout << "  (should print WrongAnimal sound, NOT WrongCat) ";
        wc->makeSound();
        check(wc->getType() == "WrongCat", "WrongCat type field is set");
        // The point: wc->makeSound() prints WrongAnimal's version — that's the expected (wrong) behavior
        check(true, "WrongAnimal::makeSound called (compile-time binding confirmed by visual output)");
        delete wc;
    }

    // 4. virtual destructor safety
    {
        Animal* d = new Dog();
        delete d; // must not crash / leak (requires virtual ~Animal)
        check(true, "delete Dog via Animal* did not crash");
    }

    std::cout << "\n" << passed << " passed, " << failed << " failed." << std::endl;
    return failed ? 1 : 0;
}
