# Fixed-Point Numbers — Ce que tu dois savoir pour l'éval

---

## Before You Start

Pour comprendre ce qui suit, tu dois être à l'aise avec :

- **Les bits et la représentation binaire** — un entier `int` c'est 32 bits, et on peut les décaler avec `<<` et `>>`
- **Les opérateurs de décalage bit à bit** — `n << 8` multiplie par 256, `n >> 8` divise par 256
- **Les classes C++ de base** — constructeurs, destructeur, `this`, membres privés/publics
- **La Form Canonique Orthodoxe (OCF)** — les 4 fonctions spéciales que toute classe "sérieuse" doit avoir

Si un de ces points flanche, revois-le d'abord — tout le module repose dessus.

---

## 1. Le Hook

Ton ordinateur sait très bien manipuler des entiers : `1`, `42`, `1000`. Pas de problème.  
Mais `3.14` ? `0.001` ? Il commence à galérer — les flottants sont lents, imprécis, et se comportent bizarrement.  
Et si tu pouvais avoir la rapidité des entiers **et** la précision des décimales, en même temps ?

---

## 2. La Douleur — La Vie Sans Fixed-Point

Imagine un développeur qui programme un jeu vidéo en 1990. Les processeurs sont lents, pas de FPU (unité pour les flottants).  
Il veut que son personnage se déplace de `0.5` pixel par frame.

Il essaie avec des `float` : le jeu rame. La puce doit faire des calculs compliqués à chaque frame.  
Il essaie avec des `int` : le personnage ne bouge que par pixel entier — mouvement saccadé, jeu injouable.

Il est coincé. Soit précis et lent, soit rapide et moche.  
*Il doit y avoir un meilleur moyen.*

---

## 3. L'Invention — L'Astuce du Dénominateur Fixe

Quelqu'un a réalisé une chose brillante : **les entiers peuvent représenter des fractions si on convient d'un dénominateur fixe.**

C'est exactement ce qu'on fait avec les centimes. `100` centimes = `1` euro.  
L'entier `150` représente `1.50€`. On sait juste que le dénominateur est toujours 100.

Le fixed-point fait pareil, mais avec des **puissances de 2** comme dénominateur — parce que les décalages binaires remplacent les multiplications/divisions, et c'est ultra-rapide.

Dans cpp02, tu as choisi le dénominateur **2⁸ = 256**.  
L'entier `256` dans ton `fixed_point_value` représente `1.0`.  
L'entier `128` représente `0.5`.  
L'entier `384` représente `1.5`.

Les 8 bits les plus bas = la partie fractionnaire. Les bits au-dessus = la partie entière.

---

## 4. L'Idée Centrale — Une Phrase

> Un nombre fixed-point, c'est un entier ordinaire qu'on décide de toujours diviser par un même dénominateur fixe (ici 256), ce qui lui donne l'apparence d'un nombre décimal.

---

## 5. Penses-y Comme...

**Les centimes (monnaie)** : Tu stockes `1050` et tu sais que ça veut dire `10.50€`. Tu ne stockes jamais le point décimal — tu sais juste qu'il est toujours 2 chiffres avant la fin.  
→ Ça mappe : `fixed_point_value = 1050`, `fractional_value = 2 (puissance de 10)`.  
→ Où ça casse : en monnaie le dénominateur est une puissance de 10 (100), en fixed-point c'est une puissance de 2 (256) — pour profiter des décalages binaires.

**La règle graduée** : Une règle millimétrique mesure en entiers de millimètres. `1732mm` = `1.732m`. Le "point décimal" est encodé dans le choix de l'unité.  
→ Ça mappe : l'unité (mm) = la fraction minimale représentable, le mètre = l'unité "réelle".  
→ Où ça casse : une règle peut avoir n'importe quelle précision, fixed-point est limité par le nombre de bits fractionnaires.

**Les degrés vs tours complets** : Un angle de `90°` c'est `0.25 tour`. Si tu stockes toujours en `1/360ème`, ton entier `90` encode `0.25`. Même idée : une unité implicite qui donne du sens aux entiers.  
→ Ça mappe : le `1/256` joue le rôle du `1/360`.  
→ Où ça casse : les degrés ne sont pas une puissance de 2, donc pas de truc binaire.

---

## 6. La Cascade d'Exemples — Du Plus Simple au Plus Subtil

### Exemple 1 — Stocker `1.0`
Tu veux représenter `1.0` en fixed-point avec 8 bits fractionnaires.  
`1.0 × 256 = 256` → tu stockes `256` dans `fixed_point_value`.  
Pour récupérer : `256 / 256 = 1.0`. Simple.

### Exemple 2 — Stocker `0.5`
`0.5 × 256 = 128` → tu stockes `128`.  
Pour récupérer : `128 / 256 = 0.5`. 

### Exemple 3 — Constructeur int (ton code ex01)
```cpp
Fixed::Fixed(const int n) {
    fixed_point_value = n << fractional_value; // n << 8 = n × 256
}
```
`Fixed(10)` → `fixed_point_value = 10 × 256 = 2560`.  
C'est logique : `2560 / 256 = 10.0`. Le nombre est bien encodé.

### Exemple 4 — Constructeur float (ton code ex01)
```cpp
Fixed::Fixed(const float n) {
    fixed_point_value = roundf(n * (1 << fractional_value)); // roundf(n × 256)
}
```
`Fixed(42.42f)` → `roundf(42.42 × 256) = roundf(10859.52) = 10860`.  
Pour vérifier : `10860 / 256 = 42.421875`. Légère imprécision — c'est **normal**, c'est la limite de précision avec 8 bits fractionnaires.

### Exemple 5 — La Multiplication (le cas piégeux)
Tu veux faire `Fixed(2.0) * Fixed(3.0)`.  
Leurs `raw` sont : `512` et `768`.  
Si tu fais naïvement `512 * 768 = 393216`... mais `393216 / 256 = 1536 = 6 × 256`. Euh, ça donnerait `6.0`, c'est correct mathématiquement, mais regarde ce qui se passe en vrai :

`512 × 768 = 393216` → `393216 / 256 = 1536` ✓

Mais pourquoi est-ce que tu ne peux pas juste faire `raw_a * raw_b` directement ?  
Parce que `raw_a = a × 256` et `raw_b = b × 256`, donc `raw_a × raw_b = a × b × 256²`.  
Tu as **256 de trop** — il faut redécaler de 8 bits :

```cpp
result.fixed_point_value = ((long)fixed_point_value * other.fixed_point_value) >> fractional_value;
```

Le `long` évite l'overflow : `256 × 256 = 65536`, et si a et b sont grands, ça déborde un `int`.

### Exemple 6 — La Division (le cas inverse)
`raw_a / raw_b` = `(a × 256) / (b × 256)` = `a / b`. On a **perdu** le facteur 256 !  
Il faut décaler **avant** de diviser :

```cpp
result.fixed_point_value = ((long)fixed_point_value << fractional_value) / other.fixed_point_value;
```

`(raw_a × 256) / raw_b` = `(a × 256²) / (b × 256)` = `(a/b) × 256`. C'est exactement ce qu'on veut.

---

## 7. Teste Ton Intuition

> **Question 1** : `Fixed(3)` a un `fixed_point_value` de combien ? Et que vaut `toFloat()` ?

<details>
<summary>Réponse</summary>

`3 << 8 = 3 × 256 = 768`.  
`toFloat()` retourne `768 / 256.0f = 3.0f`. Cohérent.

</details>

---

> **Question 2** : `++a` sur un Fixed incrémente de combien en valeur réelle ?

<details>
<summary>Réponse</summary>

`++fixed_point_value` ajoute `1` au raw. Sachant que `1 raw = 1/256 en réel`, l'incrément réel est `1/256 ≈ 0.00390625`.  
C'est le plus petit pas représentable — l'epsilon du fixed-point à 8 bits.

</details>

---

> **Question 3** : Pourquoi `toInt()` utilise `>> 8` et pas `/ 256` ?

<details>
<summary>Réponse</summary>

Les deux donnent le même résultat numérique, mais `>> 8` est **une instruction processeur**, sans division.  
C'est plus rapide. C'est exactement pourquoi on utilise des puissances de 2 pour le dénominateur — les décalages sont gratuits.

</details>

---

## 8. Ce que C'est PAS — Les Pièges à l'Éval

**"fixed_point_value c'est directement la valeur du nombre."**  
→ FAUX. `Fixed(1)` a un `fixed_point_value` de `256`, pas de `1`. La valeur réelle c'est `raw / 256`.

**"On peut multiplier les raw directement comme des entiers normaux."**  
→ FAUX. `raw_a × raw_b` contient `256²` de trop. Il faut redécaler : `(raw_a × raw_b) >> 8`.

**"Le float et le fixed-point ont la même précision."**  
→ FAUX. Un `float` a ~7 chiffres décimaux significatifs et une plage énorme. Ton fixed-point 8.24 a une précision fixe de `1/256` et une plage de -128 à +127.999...

**"L'opérateur `++` ajoute 1 à la valeur réelle."**  
→ FAUX. Il ajoute `1/256 ≈ 0.004` à la valeur réelle. Il ajoute `1` au raw.

**"La Form Canonique n'est qu'une formalité."**  
→ FAUX à l'éval. L'évaluateur va vérifier que tu as bien les 4 fonctions (défaut, copie, assignation, destructeur) et que la copie ne fait pas de shallow copy bugué.

---

## 9. La Vue d'Ensemble — Où Tu Te Situes

```
Problème : représenter des décimales sans float
     ↓
Solution : entier + dénominateur fixe implicite (2^8 = 256)
     ↓
Implémentation : class Fixed avec fixed_point_value et fractional_value = 8
```

**Ce dont Fixed dépend** : représentation binaire des entiers, décalages bit à bit, OCF C++.

**Ce qui dépend de Fixed** : tous les calculs du module (géométrie, physique de jeu, audio DSP...).

**Quand l'utiliser** : performances critiques, pas de FPU disponible, précision déterministe requise (ex: réseaux de jeu où deux machines doivent avoir le même résultat exact).

**Quand ne PAS l'utiliser** : quand tu as besoin d'une très grande plage de valeurs (fixed-point déborde vite) ou d'une précision scientifique (utilise `double`).

---

## Résumé de tes 3 exercices

### ex00 — La Fondation (OCF)
Tu as implémenté la **Form Canonique Orthodoxe** pure :
- Constructeur par défaut (met `fixed_point_value` à 0)
- Constructeur par copie (copie le raw)
- Opérateur d'assignation (copie le raw, vérifie `this != &other`)
- Destructeur
- `getRawBits()` / `setRawBits()`

Le but : te forcer à maîtriser les 4 fonctions fondamentales d'une classe C++. Aucune conversion encore, juste la structure.

### ex01 — Donner du Sens aux Nombres
Tu as ajouté la **conversion** dans les deux sens :
- `Fixed(int n)` → `n << 8` (multiplie par 256, encode)
- `Fixed(float n)` → `roundf(n * 256)` (convertit et arrondit)
- `toFloat()` → `raw / 256.0f` (décode en float)
- `toInt()` → `raw >> 8` (décode en entier, tronque)
- `operator<<` pour afficher directement avec `cout`

C'est ici que le fixed-point devient utilisable : tu peux mettre des vraies valeurs dedans.

### ex02 — Une Vraie Classe Numérique
Tu as ajouté **tous les opérateurs** pour que `Fixed` se comporte comme un vrai type numérique :
- **Comparaison** : `<`, `>`, `<=`, `>=`, `==`, `!=` → comparent directement les raw (logique : même dénominateur)
- **Arithmétique** : `+`, `-` → addition/soustraction directe des raw ✓
- **Arithmétique** : `*` → `(raw_a × raw_b) >> 8` — décalage pour corriger le dénominateur en double
- **Arithmétique** : `/` → `(raw_a << 8) / raw_b` — décalage avant division pour conserver la précision
- **Incrément/Décrément** : `++a` (pre), `a++` (post) — le post retourne une copie avant modification
- **min/max statiques** : deux versions chacun (const et non-const)
