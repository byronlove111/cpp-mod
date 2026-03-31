# Float vs Fixed — Comment les Nombres Sont Vraiment Stockés

---

## Before You Start

- **Fixed-point** — tu sais que `vraie valeur = raw / 256`, la virgule est toujours au même endroit
- **Bits et puissances de 2** — tu sais lire un nombre binaire

---

## 1. Le Hook

Tu sais maintenant comment fonctionne le fixed-point : 32 bits, virgule fixe après le bit 8, toujours divisé par 256. Simple.  
Mais un `float` stocke `0.000001` et `999 999 999.0` avec la même précision.  
Comment est-ce possible avec le même nombre de bits ?  
La virgule ne peut pas être au même endroit pour les deux — elle **se déplace**.

---

## 2. La Douleur — Le Problème que le Float Résout

Imaginons que tu fasses de l'astronomie. Tu veux stocker la distance Terre-Soleil : `149 600 000 000` mètres. Et aussi la taille d'un atome d'hydrogène : `0.0000000001` mètre.

Avec le fixed-point à 8 bits fractionnaires, tu as :
- 24 bits pour la partie entière → max `16 777 215`. La distance Terre-Soleil ne rentre pas.
- 8 bits pour la partie fractionnaire → précision de `1/256 ≈ 0.004`. L'atome d'hydrogène est invisible.

Le fixed-point est coincé dans une plage rigide. Il ne peut pas gérer des valeurs très grandes **et** très petites en même temps.

*Il faut un système où la précision s'adapte à l'ordre de grandeur du nombre.*

---

## 3. L'Invention — La Notation Scientifique en Binaire

En maths, quand les nombres deviennent énormes ou minuscules, on utilise la notation scientifique :

```
149 600 000 000  =  1.496 × 10¹¹
0.0000000001     =  1.0   × 10⁻¹⁰
```

L'idée : on sépare le nombre en deux parties :
- **Un chiffre significatif** (la mantisse) : ce qui est "précis", ex `1.496`
- **Un exposant** : l'ordre de grandeur, ex `10¹¹`

Le float fait exactement ça, mais en binaire avec des puissances de 2.  
La virgule n'est pas fixe — elle **flotte** selon l'exposant. D'où le nom : **floating**-point.

---

## 4. L'Idée Centrale — Une Phrase

> Un `float` stocke un nombre sous forme de notation scientifique en base 2 : signe × mantisse × 2^exposant — ce qui lui permet de représenter des nombres minuscules et gigantesques avec la même structure.

---

## 5. Les 32 Bits d'un Float — Découpés en 3 Zones

Un `float` 32 bits (norme IEEE 754) est découpé comme ça :

```
[S] [EEEEEEEE] [MMMMMMMMMMMMMMMMMMMMMMM]
  1 bit signe   8 bits exposant   23 bits mantisse
```

**Bit S — le signe** : `0` = positif, `1` = négatif. Identique au fixed-point.

**8 bits E — l'exposant** : représente la puissance de 2. Mais il est **décalé de 127** (appelé "biais") — donc la valeur réelle de l'exposant = `E - 127`. Ça permet de stocker des exposants négatifs (pour les petits nombres) sans bit de signe supplémentaire.

**23 bits M — la mantisse** : la partie précise du nombre. En binaire, un nombre normalisé commence toujours par `1.quelque chose` — ce `1` initial est **implicite**, non stocké. Donc les 23 bits stockent seulement ce qui vient après la virgule.

La formule complète :

```
valeur = (-1)^S × 1.M × 2^(E-127)
```

---

## 6. Exemple Concret — Comment `5.75` Est Stocké en Float

### Étape 1 : Convertir 5.75 en binaire

Partie entière : `5 = 101` en binaire.  
Partie fractionnaire : `0.75 = 0.11` en binaire (0.5 + 0.25).  
Donc `5.75 = 101.11` en binaire.

### Étape 2 : Normaliser (mettre sous forme `1.xxx × 2^n`)

`101.11` → on décale la virgule de 2 positions à gauche → `1.0111 × 2²`  
L'exposant est `2`.

### Étape 3 : Encoder les 3 champs

- **Signe** : `0` (positif)
- **Exposant** : `2 + 127 = 129` → en binaire : `10000001`
- **Mantisse** : `0111` + des zéros pour remplir 23 bits → `01110000000000000000000`

### Résultat final en mémoire :
```
0  10000001  01110000000000000000000
S     E                M
```

---

## 7. Fixed vs Float — La Comparaison Directe

Stockons `10.5` dans les deux systèmes.

### En Fixed-Point (ton code)
```
vraie valeur = raw / 256
raw = 10.5 × 256 = 2688

En binaire : 00000000 00000000 00001010 10000000
                                 ^^^^^ ^^^^^^^^^
                              partie   partie
                              entière  frac.
                               (10)   (0.5)
```
La virgule est **toujours** entre le bit 7 et le bit 8. Fixe. Immuable.

### En Float
```
10.5 = 1010.1 en binaire
     = 1.0101 × 2³

Signe    : 0
Exposant : 3 + 127 = 130 = 10000010
Mantisse : 0101000000000000000000

En mémoire : 0  10000010  01010000000000000000000
```
La virgule est **implicitement** après le premier `1`, mais l'exposant dit "décale de 3 positions". Elle a **flotté**.

---

## 8. Ce Que Ça Change Concrètement

| | Fixed-Point (ton code) | Float |
|---|---|---|
| Virgule | Toujours au même endroit | Se déplace selon l'exposant |
| Plage | Limitée (~-128 à +127) | Énorme (~10⁻³⁸ à 10³⁸) |
| Précision | Uniforme (1/256 partout) | Varie selon la taille du nombre |
| Vitesse | Rapide (entier + décalage) | Plus lent (circuit dédié FPU) |
| Résultat exact | Déterministe | Peut varier entre processeurs |

**La précision variable du float** : `1.0000001` et `1.0000002` sont distinguables. Mais `10000000.1` et `10000000.2` peuvent être **identiques** pour le float — il n'a plus assez de mantisse pour voir la différence à cette échelle. C'est pourquoi `0.1 + 0.2 != 0.3` en float.

---

## 9. Test Ton Intuition

> **Question 1** : Pourquoi `Fixed(42.42f)` ne stocke pas exactement `42.42` ?

<details>
<summary>Réponse</summary>

Deux sources d'imprécision :

1. Le `float` `42.42f` lui-même n'est pas exactement `42.42` — c'est déjà une approximation en base 2.
2. Le fixed-point a une précision de `1/256 ≈ 0.004`. Donc `42.42` arrondi à la valeur représentable la plus proche.

`roundf(42.42 × 256) = roundf(10859.52) = 10860` → `10860 / 256 = 42.421875`. C'est la meilleure approximation possible avec 8 bits fractionnaires.

</details>

---

> **Question 2** : Pourquoi le résultat d'un calcul fixed-point est **déterministe** alors qu'un float peut donner des résultats différents sur deux machines ?

<details>
<summary>Réponse</summary>

Le fixed-point n'est que des opérations sur des entiers (`+`, `>>`, `<<`). Les entiers sont identiques sur tous les processeurs qui respectent le standard.

Le float utilise l'IEEE 754, mais les processeurs ont des registres internes plus précis (80 bits sur x86), des optimisations qui réordonnent les opérations, etc. Le même calcul peut donner `0.30000000000000004` sur une machine et `0.3` sur une autre.

C'est pourquoi les jeux réseau utilisent le fixed-point : si deux machines calculent une position de personnage, elles doivent obtenir **exactement** le même bit.

</details>

---

## 10. Ce que C'est PAS

**"Le float est plus précis que le fixed-point."**  
→ Ça dépend. Pour les grands nombres, le float est moins précis que le fixed-point car la mantisse ne suffit plus. Pour les petits nombres, il est plus précis. La précision du float est **relative** (proportionnelle à la valeur), celle du fixed-point est **absolue** (toujours 1/256).

**"Le float et le fixed-point stockent les bits de la même façon."**  
→ FAUX. Fixed : les bits représentent directement un entier qu'on divise par 256. Float : les bits sont répartis en signe/exposant/mantisse avec une formule complexe.

**"On peut convertir un float en fixed-point sans perte."**  
→ FAUX. Le float peut stocker des valeurs hors plage du fixed-point (trop grand, trop petit). Et même dans la plage, arrondir à `1/256` près perd de l'information.

---

## 11. La Vue d'Ensemble

```
Fixed-Point :
  [signe + entier (24 bits)] [fraction (8 bits)]
  ← virgule toujours ici, divisé par 256, toujours

Float (IEEE 754) :
  [S 1bit] [Exposant 8bits] [Mantisse 23bits]
  ← virgule flottante selon exposant
  ← formule : (-1)^S × 1.M × 2^(E-127)
```

**Dans ton constructeur `Fixed(const float n)`** :
```cpp
fixed_point_value = roundf(n * (1 << fractional_value));
```
Tu prends un float (qui est déjà une approximation en base 2), tu le multiplies par 256, tu arrondis, et tu le colles dans un entier. Tu **abandonne** la représentation flottante pour la représentation fixed. C'est une conversion avec perte — normale et intentionnelle.
