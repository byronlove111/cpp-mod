# ex03 — Copie profonde (deep copy)

Implémenter la Forme Canonique Orthodoxe avec un attribut pointeur pour forcer la deep copy.

## À implémenter

- Classe **`Memory`** : contient un tableau `std::string _data[10]`  
  (simule le `Brain` de cpp04)

- Classe **`Bot`** : contient un `Memory* _memory` (alloué avec `new`)
  - Constructeur par défaut
  - Constructeur de copie (**deep copy** : alloue un nouveau `Memory`, copie le contenu)
  - Opérateur d'assignation (**deep copy**)
  - Destructeur (libère `_memory`)
  - `setIdea(int index, std::string idea)` et `getIdea(int index) const`

## Deliverables

```
Memory.hpp / Memory.cpp
Bot.hpp / Bot.cpp
```

Signatures attendues :
```cpp
class Bot {
    Memory* _memory;
public:
    Bot();
    Bot(const Bot& other);          // deep copy
    Bot& operator=(const Bot& other); // deep copy
    ~Bot();
    void        setIdea(int index, std::string idea);
    std::string getIdea(int index) const;
};
```

## Compiler & tester

```bash
c++ -std=c++98 -Wall -Wextra -Werror Memory.cpp Bot.cpp test.cpp -o test && ./test
```
