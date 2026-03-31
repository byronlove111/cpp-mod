# ex02 — Destructeur virtuel

Comprendre pourquoi le destructeur doit être `virtual` dans une hiérarchie polymorphe.

## À implémenter

- Classe **`Unsafe`** : destructeur **non-virtual**, alloue une ressource `int* _data`
- Classe **`SafeChild : Unsafe`** : alloue sa propre ressource `int* _childData`
- Classe **`Safe`** : destructeur **virtual**, même logique
- Classe **`SafeChild2 : Safe`** : alloue `int* _childData`

Dans les constructeurs/destructeurs, affiche un message (ex: `"SafeChild destroyed"`)  
pour pouvoir observer quels destructeurs sont appelés.

## Deliverables

```
Unsafe.hpp / Unsafe.cpp
SafeChild.hpp / SafeChild.cpp
Safe.hpp / Safe.cpp
SafeChild2.hpp / SafeChild2.cpp
```

Signatures clés :
```cpp
class Unsafe {
    int* _data;
public:
    Unsafe();
    ~Unsafe();          // NON-virtual → problème !
};

class Safe {
    int* _data;
public:
    Safe();
    virtual ~Safe();    // virtual → correct
};
```

## Compiler & tester

```bash
c++ -std=c++98 -Wall -Wextra -Werror Unsafe.cpp SafeChild.cpp Safe.cpp SafeChild2.cpp test.cpp -o test && ./test
```
