# Le problème du dispatch statique (et pourquoi `virtual` existe)

## Before You Start

Pour comprendre ceci, tu dois être à l'aise avec :

- **Héritage en C++** — tu sais qu'une classe fille peut surcharger une méthode de la classe mère
- **Pointeurs** — tu sais ce qu'est un `Shape*` et que tu peux y stocker l'adresse d'un `Circle`
- **Compilation vs exécution** — tu as une intuition que certaines choses sont décidées à la compilation, d'autres au moment où le programme tourne

Si l'un de ces points est flou, clarifie-le d'abord — cette explication s'appuie directement dessus.

---

## The Hook

Tu crées un `Circle`, tu le stockes dans un `Shape*`, tu appelles `getArea()` — et tu obtiens `0`. Pas l'aire du cercle. Zéro.

Le cercle est là. La méthode `getArea()` existe dans `Circle`. Pourtant, ce n'est pas elle qui s'exécute.

Comment c'est possible ?

---

## Life Without It — The Pain

Imagine que tu gères un tableau de formes : des cercles, des rectangles, des triangles. Tu veux calculer l'aire de chacun.

Naturellement, tu crées un tableau de `Shape*` et tu boucles dessus :

```cpp
Shape* formes[3];
formes[0] = new Circle(5.0f);
formes[1] = new Rectangle(4.0f, 3.0f);
formes[2] = new Circle(2.0f);

for (int i = 0; i < 3; i++) {
    std::cout << formes[i]->getArea() << std::endl;
}
```

Tu t'attends à voir `78.5`, `12`, `12.56`.

Tu vois `0`, `0`, `0`.

Le programme est parfaitement compilé, aucune erreur. Mais les résultats sont tous faux. Tu passes des heures à déboguer. *Il doit y avoir une meilleure façon.*

---

## The Invention Story

Au début du C++, les compilateurs étaient simples. Quand tu écrivais `pointeur->methode()`, le compilateur regardait le **type déclaré** du pointeur — pas l'objet réellement stocké dedans.

Si le pointeur est de type `Shape*`, le compilateur se dit : *"OK, c'est un Shape, j'appelle `Shape::getArea()`."* Il ne vérifie pas si l'objet est en réalité un `Circle`. Il a décidé au moment de la compilation, une fois pour toutes.

C'est ce qu'on appelle le **dispatch statique** — "statique" parce que la décision est figée à la compilation.

Quelqu'un a alors réalisé qu'on avait besoin d'un mécanisme pour dire au compilateur : *"Pour cette méthode, attends l'exécution pour décider. Regarde ce qu'il y a vraiment dans le pointeur."*

Le mot clé `virtual` est né de cette idée.

---

## The Core Idea — One Sentence

Sans `virtual`, C++ choisit quelle méthode appeler en regardant le **type du pointeur** ; avec `virtual`, il attend l'exécution pour regarder le **type réel de l'objet**.

---

## Think of It Like...

**Le courrier postal** : Tu envoies une lettre à "M. Dupont, 12 rue de la Paix". Sans `virtual`, c'est comme si le facteur lisait uniquement le nom de la rue et déposait toutes les lettres au numéro 12, peu importe le destinataire. Avec `virtual`, il lit le vrai nom sur la boîte aux lettres avant de déposer.
→ Correspond à : le type du pointeur = la rue, le vrai objet = le vrai destinataire.
→ Limite : dans la vraie vie, le facteur lit toujours le nom — l'analogie montre juste que sans `virtual`, C++ fait quelque chose d'apparemment illogique.

**Un costume de théâtre** : Imagine un acteur habillé en roi. Sans `virtual`, quand quelqu'un lui pose une question, il répond comme si c'était le costume lui-même qui parlait — toujours "roi", peu importe que l'acteur soit un mendiant ou un général dessous. Avec `virtual`, c'est l'acteur réel qui choisit comment répondre.
→ Correspond à : le costume = le type du pointeur (`Shape*`), l'acteur = l'objet réel (`Circle`).
→ Limite : un acteur a toujours une conscience propre ; un objet sans `virtual` n'en a pas.

**Un GPS avec carte périmée** : Le GPS a décidé de ton itinéraire avant que tu partes. Même si la route est fermée, il ne s'adapte pas — il a décidé une fois pour toutes. `virtual`, c'est le GPS qui recalcule en temps réel selon ce qu'il voit réellement.
→ Correspond à : la décision figée à la compilation = carte périmée, le dispatch dynamique = recalcul en temps réel.
→ Limite : un GPS recalcule toujours aujourd'hui ; `virtual` est un choix explicite que le développeur doit faire.

---

## Example Cascade

### Exemple 1 — Le plus simple possible

```cpp
Shape s;
s.getArea(); // Appelle Shape::getArea() → 0.0
```
Le type du pointeur (ou variable) est `Shape`. La décision est immédiate : `Shape::getArea()`. Aucune ambiguïté.

---

### Exemple 2 — L'objet est un Circle, mais vu comme un Shape

```cpp
Circle c(5.0f);
Shape* p = &c;     // p est de type Shape*, mais pointe sur un Circle

p->getArea();      // SANS virtual → appelle Shape::getArea() → 0.0
                   // AVEC virtual → appelle Circle::getArea() → 78.5
```
C'est le coeur du problème. L'objet réel est un `Circle`. Mais le compilateur, sans `virtual`, regarde seulement le type du pointeur : `Shape*`.

---

### Exemple 3 — Le tableau de formes (le vrai use case)

```cpp
Shape* formes[2];
formes[0] = new Circle(3.0f);
formes[1] = new Rectangle(4.0f, 5.0f);

// SANS virtual :
formes[0]->getArea(); // → 0.0  (faux)
formes[1]->getArea(); // → 0.0  (faux)

// AVEC virtual :
formes[0]->getArea(); // → 28.27  (correct)
formes[1]->getArea(); // → 20.0   (correct)
```
C'est exactement ce que tu voulais faire. Sans `virtual`, tout le polymorphisme s'effondre.

---

### Exemple 4 — La surcharge directe fonctionne toujours

```cpp
Circle c(3.0f);
c.getArea(); // Appelle TOUJOURS Circle::getArea(), virtual ou pas
```
Quand tu appelles directement sur l'objet (pas via un pointeur de classe mère), il n'y a pas d'ambiguïté — C++ sait exactement quel type c'est. Le problème n'existe que via un pointeur ou une référence de classe parente.

---

### Exemple 5 — Le comportement de ex00 était voulu

```cpp
// Test 3 de ex00 :
Shape* s = new Circle(5.0f);
float area = s->getArea();
// → 0.0 attendu et obtenu — c'est CORRECT pour cet exo
```
L'exo 00 testait que tu comprends ce comportement. Obtenir `0.0` via un `Shape*` sans `virtual` n'est pas un bug — c'est le comportement garanti du dispatch statique. Ex01 introduira `virtual` pour le corriger.

---

## Test Your Intuition

> **Question 1** : Tu as ce code. Qu'est-ce qui s'affiche ?
> ```cpp
> Shape* p = new Rectangle(3.0f, 4.0f);
> std::cout << p->getArea(); // sans virtual
> ```

<details>
<summary>Réponse</summary>

`0.0` — parce que sans `virtual`, C++ regarde le type du pointeur (`Shape*`) et appelle `Shape::getArea()` qui retourne `0.0`. Peu importe que l'objet soit réellement un `Rectangle`.

</details>

---

> **Question 2** : Dans quel cas est-ce que le dispatch statique et le dispatch dynamique donnent le même résultat ?

<details>
<summary>Réponse</summary>

Quand le type du pointeur correspond exactement au type réel de l'objet. Par exemple : `Circle* p = new Circle(5.0f); p->getArea();` — ici, qu'il y ait `virtual` ou non, C++ appelle `Circle::getArea()`. L'ambiguïté n'existe que quand on passe par un pointeur de classe parente.

</details>

---

> **Question 3** : Tu veux stocker 10 formes différentes dans un tableau et calculer leur aire correctement. Que te manque-t-il sans `virtual` ?

<details>
<summary>Réponse</summary>

Sans `virtual`, ton tableau de `Shape*` appellera toujours `Shape::getArea()` → `0.0` pour chaque forme. Il te manque le dispatch dynamique : déclarer `getArea()` avec `virtual` dans `Shape` pour que C++ regarde le type réel de chaque objet à l'exécution.

</details>

---

## What It's NOT — Misconceptions

**"La méthode de Circle n'est pas appelée parce qu'elle n'est pas trouvée."**
Faux. Le compilateur connaît parfaitement `Circle::getArea()`. Il choisit délibérément de ne pas l'appeler parce que le pointeur est de type `Shape*`. C'est une décision de design, pas une erreur de recherche.

**"La surcharge suffit à avoir du polymorphisme."**
Faux. Surcharger (redéfinir une méthode dans une classe fille) est nécessaire, mais pas suffisant. Sans `virtual`, la surcharge n'est active que quand tu appelles directement sur l'objet. Via un pointeur de classe mère, c'est toujours la version de la mère qui s'exécute.

**"`Shape* p = new Circle()` change le type de p."**
Faux. `p` reste de type `Shape*` — pour toujours. Le type du pointeur est fixé à sa déclaration. Ce qui change, c'est l'objet pointé. Sans `virtual`, C++ regarde le type du pointeur, pas de l'objet.

**"Ce problème n'arrive qu'avec les pointeurs."**
Partiellement faux. Ça arrive aussi avec les références (`Shape& ref = circle`). Par contre, ça n'arrive pas avec les variables directes (`Circle c; c.getArea()` appelle toujours `Circle::getArea()`).

---

## The Big Picture — Where Does This Live?

Ce problème appartient à la catégorie du **polymorphisme** — la capacité à traiter des objets de types différents de façon uniforme.

- **Dépend de** : l'héritage (sans héritage, pas de ce problème), les pointeurs et références
- **`virtual` dépend de lui** : tu ne peux pas comprendre `virtual`, les classes abstraites, ou les interfaces C++ sans avoir ressenti ce problème
- **Mène à** : les destructeurs virtuels (ex02), les classes purement abstraites avec `= 0` (ex03/ex04)

**Quand utiliser le dispatch dynamique (`virtual`)** : dès que tu veux stocker des objets de types différents via un pointeur de classe mère et appeler leurs méthodes spécifiques.

**Quand ne pas l'utiliser** : quand tu n'as pas besoin de polymorphisme — `virtual` a un petit coût en performance (table de fonctions virtuelles). Sur des classes simples sans héritage, c'est inutile.
