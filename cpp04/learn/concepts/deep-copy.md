# Deep Copy (Copie Profonde)

---

## Before You Start

- **Pointeurs** — tu sais qu'un pointeur contient une adresse mémoire, pas une valeur
- **`new` / `delete`** — tu sais allouer et libérer de la mémoire sur le tas
- **Forme Canonique Orthodoxe** — tu sais qu'une classe doit avoir : constructeur par défaut, constructeur de copie, opérateur d'affectation, destructeur
- **Héritage basique** — utile pour le contexte cpp04, pas indispensable pour comprendre la notion

---

## 1. Le Hook

Tu copies un objet. Tu modifies la copie. Et l'original change aussi.

Tu n'as rien partagé. Tu n'as rien passé par référence. Tu as juste fait `Dog b = a;`. Et pourtant, les deux chiens pensent la même chose au même moment — et si tu en détruis un, l'autre plante le programme.

Comment est-ce possible ?

---

## 2. La Douleur — La Vie Sans Ça

```cpp
class Dog {
public:
    Brain* brain_;
    Dog() { brain_ = new Brain(); }
    ~Dog() { delete brain_; }
};

Dog a;
a.brain_->ideas[0] = "chasser les chats";

Dog b = a; // copie... ou pas ?

b.brain_->ideas[0] = "dormir";

std::cout << a.brain_->ideas[0]; // affiche "dormir". Pas "chasser les chats".
```

Tu as modifié `b`. Mais `a` a changé. Ils partagent le même `Brain` en mémoire.

Et quand `b` est détruit en fin de scope :

```
delete b.brain_; // libère le Brain
```

Puis quand `a` est détruit :

```
delete a.brain_; // CRASH — ce pointeur pointe vers de la mémoire déjà libérée
```

Double free. Comportement indéfini. Ton programme explose.

Il faut un moyen de copier un objet qui crée de **nouveaux** sous-objets — pas de partager les anciens.

---

## 3. L'Histoire de l'Invention

Par défaut, quand tu écris `Dog b = a;`, C++ copie chaque attribut de `a` dans `b` — bit par bit, champ par champ. C'est la **copie superficielle** (shallow copy).

Pour un `int` ou un `std::string`, ça marche parfaitement : les valeurs sont copiées indépendamment.

Mais pour un `Brain*` — un **pointeur** — copier bit par bit copie l'adresse, pas ce qu'il y a à cette adresse. Les deux objets pointent maintenant vers **le même Brain**.

Quelqu'un a réalisé : il faut pouvoir redéfinir ce que "copier" veut dire. C++ permet exactement ça via le **constructeur de copie** et **l'opérateur d'affectation** : tu prends le contrôle total de la copie. Tu décides que copier un `Dog`, ça veut dire allouer un nouveau `Brain` et y recopier le contenu de l'ancien.

C'est ça la deep copy : **recréer toute la structure, pas juste les adresses**.

---

## 4. L'Idée Centrale — Une Phrase

La deep copy crée de nouvelles ressources indépendantes pour chaque objet copié, au lieu de partager les mêmes ressources entre l'original et la copie.

---

## 5. Pense-y Comme...

**Un document Word** : copier-coller un fichier Word crée deux fichiers indépendants (deep copy). Créer un raccourci vers ce fichier, c'est une shallow copy — il n'y a qu'un seul vrai fichier, et si tu le supprimes, le raccourci est cassé.
→ Mapping : le fichier = le `Brain`, le raccourci = le pointeur copié.
→ Où ça casse : un raccourci cassé ne plante pas ton OS. Un double `delete` en C++, si.

**Un carnet d'adresses** : tu donnes ton carnet à un ami pour qu'il le "copie". S'il recopie toutes les adresses à la main dans un nouveau carnet → deep copy, deux carnets indépendants. S'il photocopie juste la couverture avec ton nom et garde le même carnet → shallow copy, un seul carnet, deux propriétaires.
→ Où ça casse : en vrai, partager un carnet n'est pas dangereux. En C++, partager un pointeur et `delete` des deux côtés, ça l'est.

**Un moule à gâteau** : deep copy = couler un nouveau moule identique. Shallow copy = prêter le moule. Si quelqu'un casse le moule prêté, tu n'en as plus.
→ Mapping : le moule = la mémoire allouée, `delete` = casser le moule.
→ Où ça casse : un moule cassé te prive de gâteaux. Un pointeur double-freed te donne un crash ou, pire, un comportement indéfini silencieux.

---

## 6. La Cascade d'Exemples

**Exemple 1 — Shallow copy par défaut (le problème)**

```cpp
class Brain {
public:
    std::string ideas[100];
};

class Dog {
public:
    Brain* brain_;
    Dog()  { brain_ = new Brain(); }
    ~Dog() { delete brain_; }
    // pas de constructeur de copie → C++ génère une shallow copy
};

Dog a;
Dog b = a; // b.brain_ == a.brain_ → même adresse !
// destruction de b → delete brain_
// destruction de a → delete brain_ à nouveau → CRASH
```

**Exemple 2 — Deep copy : le constructeur de copie**

```cpp
Dog::Dog(const Dog& other) {
    brain_ = new Brain();           // nouvelle allocation
    *brain_ = *other.brain_;        // copie du contenu, pas de l'adresse
}
```

Maintenant `b.brain_` et `a.brain_` sont à des adresses différentes, avec le même contenu. Modifier l'un ne touche pas l'autre. Détruire l'un ne casse pas l'autre.

**Exemple 3 — L'opérateur d'affectation (le cas `b = a` après construction)**

```cpp
Dog& Dog::operator=(const Dog& other) {
    if (this == &other)       // garde contre a = a
        return *this;
    delete brain_;            // libère l'ancien Brain de this
    brain_ = new Brain();     // alloue un nouveau
    *brain_ = *other.brain_;  // copie le contenu
    return *this;
}
```

Sans cette vérification `this == &other` : `a = a` libèrerait le `Brain` d'`a` avant de le copier. Tu copierais de la mémoire libérée. Comportement indéfini.

**Exemple 4 — Le tableau d'animaux de l'ex01**

```cpp
Animal* zoo[4];
zoo[0] = new Dog();
zoo[1] = new Dog();

Dog copy = *static_cast<Dog*>(zoo[0]); // constructeur de copie appelé

delete zoo[0]; // libère le Brain de zoo[0]
// copy.brain_ est intact — c'est un Brain différent
```

Sans deep copy : `delete zoo[0]` rendrait `copy.brain_` invalide immédiatement.

**Exemple 5 — La subtilité : `*brain_ = *other.brain_`**

```cpp
*brain_ = *other.brain_;
```

`brain_` est un pointeur. Déréférencer avec `*` accède à l'objet `Brain` lui-même.
`*brain_ = *other.brain_` copie le **contenu** du Brain (les 100 `std::string`) dans le nouveau Brain fraîchement alloué.

Ce n'est pas copier l'adresse. C'est copier ce qui est à l'adresse. La différence est tout.

---

## 7. Teste Ton Intuition

> **Question 1** : Tu as deux objets `Dog a` et `Dog b`. Tu fais `b = a` après que les deux ont été construits. Quelle fonction est appelée — le constructeur de copie ou l'opérateur d'affectation ?

<details>
<summary>Réponse</summary>

L'**opérateur d'affectation** (`operator=`). Le constructeur de copie n'est appelé qu'à la construction : `Dog b = a;` ou `Dog b(a);`. Si `b` existe déjà, c'est toujours `operator=`.

C'est important parce que dans `operator=`, tu dois d'abord `delete` l'ancien `brain_` avant d'en allouer un nouveau — sinon tu perds l'accès à l'ancienne mémoire sans la libérer.

</details>

---

> **Question 2** : Ton `Dog` implémente un constructeur de copie en deep copy. Tu fais :
> ```cpp
> Dog a;
> a.brain_->ideas[0] = "os";
> Dog b = a;
> b.brain_->ideas[0] = "balle";
> ```
> Quelle est la valeur de `a.brain_->ideas[0]` après ?

<details>
<summary>Réponse</summary>

`"os"`. La deep copy a créé un `Brain` indépendant pour `b`. Modifier `b.brain_->ideas[0]` ne touche pas `a.brain_->ideas[0]`. Les deux chiens pensent à des choses différentes — c'est le but.

</details>

---

> **Question 3** : Pourquoi faut-il vérifier `if (this == &other)` dans `operator=` ?

<details>
<summary>Réponse</summary>

Pour gérer le cas `a = a`. Sans cette garde :
1. `delete brain_` libère le `Brain` de `a`
2. `brain_ = new Brain()` alloue un nouveau `Brain` vide
3. `*brain_ = *other.brain_` tente de copier depuis `other.brain_` — mais `other`, c'est `a`, et son `brain_` vient d'être libéré à l'étape 1

Tu lis de la mémoire libérée. Comportement indéfini. La garde coûte une comparaison de pointeurs et évite un bug vicieux.

</details>

---

## 8. Ce que Ce N'est PAS — Les Malentendus

**"Deep copy veut dire copier tous les attributs."**
Faux. Copier tous les attributs, c'est ce que la shallow copy fait déjà. La deep copy, c'est copier les **ressources pointées** — allouer de nouveau et recopier le contenu.

**"Il suffit de définir le constructeur de copie, `operator=` c'est optionnel."**
Faux et dangereux. Si tu oublies `operator=`, C++ génère une shallow copy pour l'affectation même si tu as un constructeur de copie en deep copy. Les deux doivent être cohérents.

**"`*brain_ = *other.brain_` copie le pointeur."**
Faux. `brain_` est le pointeur. `*brain_` est l'objet `Brain` lui-même. Écrire `*brain_ = *other.brain_` copie le contenu du `Brain` (les 100 strings) en appelant l'opérateur d'affectation de `Brain`. L'adresse de `brain_` ne change pas.

**"La deep copy est toujours nécessaire."**
Faux. Si ta classe n'a pas de ressources allouées dynamiquement (pas de pointeurs vers du `new`), la shallow copy par défaut est parfaitement correcte et suffisante.

---

## 9. La Grande Image — Où Ça Vit

**Catégorie** : Gestion des ressources, ownership, cycle de vie des objets.

**Dépend de** : `new`/`delete`, constructeur de copie, `operator=`, pointeurs.

**Ce qui dépend de ça** :
- Toute classe qui possède des ressources allouées dynamiquement
- L'ex01 et l'ex02 du cpp04 (le `Brain`)
- La règle des trois (Rule of Three) : si tu définis un des trois — destructeur, constructeur de copie, `operator=` — tu dois probablement définir les trois

**Quand l'utiliser** : dès qu'un attribut est un pointeur vers de la mémoire allouée avec `new`.

**Quand ne pas l'utiliser** : quand tous tes attributs sont des valeurs (`int`, `std::string`, etc.). La copie par défaut de C++ gère ça parfaitement.
