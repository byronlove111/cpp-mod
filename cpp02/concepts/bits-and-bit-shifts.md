# Bits & Décalages Binaires — La Langue Secrète du Processeur

---

## Before You Start

*Aucun prérequis — c'est un concept fondamental. Si tu sais compter, tu peux comprendre ça.*

---

## 1. Le Hook

Ton processeur ne sait pas ce qu'est le chiffre `42`. Il ne connaît que deux états : **courant** ou **pas courant**. Allumé ou éteint. `1` ou `0`.  
Pourtant, tu fais des calculs avec des millions, des décimales, des textes.  
Comment est-ce qu'une machine qui ne comprend que oui/non peut faire tout ça ?

---

## 2. La Douleur — Avant de Comprendre les Bits

Imagine que tu essaies de transmettre un nombre à quelqu'un dans une pièce sombre, en utilisant seulement une lampe de poche. Allumée ou éteinte. C'est tout ce que tu peux faire.

Comment tu enverrais le nombre `13` ?  
Si tu allumes 13 fois ? Lent, ambigu, ça marche pas pour `0`.  
Si tu envoies "treize" en morse ? Tu as besoin d'un alphabet entier.

Tu bloques. Il doit y avoir un système où juste allumé/éteint suffit à tout encoder.

---

## 3. L'Invention — Le Système Binaire

Quelqu'un a eu l'idée suivante : et si chaque lampe représentait une **valeur double de la précédente** ?

Lampe 1 vaut `1`.  
Lampe 2 vaut `2`.  
Lampe 3 vaut `4`.  
Lampe 4 vaut `8`.  
Lampe 5 vaut `16`.

Pour envoyer `13` : tu allumes les lampes qui valent 8, 4 et 1. `8 + 4 + 1 = 13`. ✓

C'est exactement ça le **binaire**. Chaque position est une puissance de 2. Un bit = une lampe. Allumé = `1`, éteint = `0`.

---

## 4. L'Idée Centrale — Une Phrase

> Un nombre en binaire, c'est une suite de 0 et de 1 où chaque position représente une puissance de 2 — exactement comme le système décimal représente des puissances de 10.

---

## 5. Penses-y Comme...

**Le système décimal que tu connais déjà** : Dans `347`, le `3` vaut `300` (3×10²), le `4` vaut `40` (4×10¹), le `7` vaut `7` (7×10⁰). Chaque position est une puissance de 10.  
→ Ça mappe : en binaire c'est pareil mais avec des puissances de 2, et les seuls chiffres possibles sont 0 et 1.  
→ Où ça casse : en décimal on a 10 symboles (0-9), en binaire seulement 2 (0 et 1) — donc les nombres prennent plus de place à écrire.

**Les interrupteurs dans une maison** : Imagine 8 interrupteurs sur un mur. Chacun contrôle une ampoule d'une valeur : 128, 64, 32, 16, 8, 4, 2, 1. La somme des ampoules allumées = ton nombre.  
→ Ça mappe : les interrupteurs = les bits, allumé/éteint = 1/0, la valeur de l'ampoule = la puissance de 2.  
→ Où ça casse : les ampoules ont des valeurs fixes, mais un interrupteur physique n'a pas vraiment de "valeur" — c'est juste une métaphore.

**Un coffre-fort à combinaison** : 8 cadrans qui peuvent être en position haute (1) ou basse (0). Chaque cadran a un poids différent. La "valeur" du coffre = la somme des poids des cadrans en position haute.  
→ Ça mappe : la combinaison du coffre = l'écriture binaire d'un nombre.  
→ Où ça casse : un vrai coffre ne fait pas de maths avec sa combinaison.

---

## 6. La Cascade d'Exemples

### Exemple 1 — Lire du binaire (trivial)

Le nombre binaire `00000101` — lis de droite à gauche, chaque position vaut :

```
Position :  7    6    5    4    3    2    1    0
Valeur    : 128  64   32   16   8    4    2    1
Bit       :  0    0    0    0    0    1    0    1
```

Bits allumés : position 2 (vaut 4) et position 0 (vaut 1).  
Total : `4 + 1 = 5`. Donc `00000101` = `5` en décimal.

### Exemple 2 — Lire `42` en binaire

`42 = 32 + 8 + 2` = `00101010`.

```
Position :  7    6    5    4    3    2    1    0
Valeur    : 128  64   32   16   8    4    2    1
Bit       :  0    0    1    0    1    0    1    0
```

### Exemple 3 — Un `int` c'est 32 bits

En C++, un `int` c'est 32 interrupteurs. Il peut représenter des valeurs de `-2 147 483 648` à `2 147 483 647`.  
Le premier bit (le plus à gauche) est le bit de signe : `0` = positif, `1` = négatif.

```cpp
int x = 5; // en mémoire : 00000000 00000000 00000000 00000101
```

### Exemple 4 — Le décalage à gauche `<<` (la vraie magie)

`n << 1` décale tous les bits d'une position vers la gauche. Le bit de droite devient `0`.

```
Avant  (5) : 00000101
Après  (10): 00001010   ← tout a glissé d'un cran à gauche
```

`5 << 1 = 10`. C'est une **multiplication par 2**.  
`5 << 2 = 20`. Multiplication par 4.  
`5 << 8 = 1280`. Multiplication par 256.

Pourquoi ? Parce qu'avancer d'une position = multiplier par la base (comme ajouter un zéro en décimal : `5` → `50` → `500`).

### Exemple 5 — Le décalage à droite `>>` (la division)

`n >> 1` décale tous les bits vers la droite. Le bit de droite tombe.

```
Avant  (10): 00001010
Après   (5): 00000101   ← tout a glissé d'un cran à droite
```

`10 >> 1 = 5`. Division par 2, **troncature** (pas d'arrondi).  
`7 >> 1 = 3`. (`7/2 = 3.5`, tronqué → `3`).  
`2560 >> 8 = 10`. Division par 256.

### Exemple 6 — Pourquoi c'est plus rapide que `* 256` ou `/ 256`

`n * 256` → le processeur doit faire une vraie multiplication (plusieurs cycles d'horloge).  
`n << 8` → c'est **une seule instruction** : décale les bits. Un cycle. Instantané.

Le compilateur le fait souvent tout seul, mais dans le fixed-point c'est toi qui l'écris explicitement.

---

## 7. Teste Ton Intuition

> **Question 1** : Que vaut `1 << 8` ?

<details>
<summary>Réponse</summary>

`1` en binaire c'est `00000001`. Décaler de 8 vers la gauche : `100000000` en binaire = **256** en décimal.  
C'est pourquoi `(1 << fractional_value)` avec `fractional_value = 8` donne `256` — le dénominateur de ton fixed-point.

</details>

---

> **Question 2** : Tu as `fixed_point_value = 2560`. Tu fais `2560 >> 8`. Quel est le résultat et que représente-t-il dans le contexte du Fixed-Point ?

<details>
<summary>Réponse</summary>

`2560 >> 8 = 2560 / 256 = 10`.  
Dans Fixed, c'est ce que fait `toInt()` : extraire la partie entière du nombre. `Fixed(10)` a un raw de `2560`, et `toInt()` retourne bien `10`.

</details>

---

> **Question 3** : Pourquoi `7 >> 1` vaut `3` et pas `3.5` ?

<details>
<summary>Réponse</summary>

Le décalage à droite tronque — le bit qui "tombe" de l'autre côté est perdu.  
`7` en binaire : `0111`. Décalé d'un cran : `011` = `3`. Le `1` de droite disparaît.  
C'est une division entière, pas une division flottante. Le résultat est toujours un entier.

</details>

---

## 8. Ce que C'est PAS — Les Pièges

**"`5 << 2` c'est `5 × 2`."**  
→ FAUX. `<< 2` décale de **2 positions**, donc multiplie par **2² = 4**. `5 << 2 = 20`.  
Le nombre après `<<` c'est l'exposant, pas le multiplicateur.

**"Le décalage à droite c'est comme la division flottante."**  
→ FAUX. `7 >> 1 = 3`, pas `3.5`. Les bits perdus disparaissent. C'est une division entière qui tronque vers zéro.

**"On peut décaler autant qu'on veut."**  
→ FAUX (comportement indéfini). Pour un `int` de 32 bits, décaler de 32 ou plus est **undefined behavior** en C++. Et décaler un bit signé à gauche jusqu'à toucher le bit de signe est aussi UB.

**"Binaire et hexadécimal c'est pareil."**  
→ Pas tout à fait. L'hexa (base 16) est juste une façon compacte d'écrire du binaire — 1 chiffre hexa = 4 bits. `0xFF = 11111111 = 255`. C'est utile pour lire des patterns de bits, pas un système différent.

**"Le processeur 'comprend' les nombres comme nous."**  
→ FAUX. Il ne connaît que des tensions électriques, regroupées en bits. Le "nombre" est une interprétation qu'on lui impose avec le type (`int`, `float`, etc.).

---

## 9. La Vue d'Ensemble

```
Binaire : représentation de tout avec 0 et 1
    ↓
Chaque bit = puissance de 2
    ↓
Décalage gauche << = × 2^n  (rapide, une instruction)
Décalage droit  >> = ÷ 2^n  (rapide, tronque)
    ↓
Application directe dans Fixed-Point :
  - Encoder :  n << 8   (× 256)
  - Décoder :  raw >> 8 (÷ 256, partie entière)
```

**Ce dont les bits dépendent** : rien, c'est vraiment la base de tout en informatique.

**Ce qui dépend des bits** : les entiers, les flottants, les adresses mémoire, les couleurs RGB, les permissions de fichiers, les masques réseau, les fixed-points... tout.

**Quand utiliser `<<` et `>>`** : multiplication/division par une puissance de 2 quand la performance compte, ou quand tu manipules des bits directement (flags, masques, encodage).

**Quand ne pas les utiliser** : pour de la lisibilité — si tu veux juste multiplier par 4 dans du code normal, `x * 4` est plus clair. Réserve `<<` aux contextes où le sens "bit shift" est explicite.
