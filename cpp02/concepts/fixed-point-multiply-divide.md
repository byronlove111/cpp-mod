# Multiplication & Division en Fixed-Point — Pourquoi C'est Spécial

---

## Before You Start

- **Fixed-point** — tu sais que la vraie valeur = `raw / 256`, et que `raw = vraie_valeur × 256`
- **Décalages binaires** — `>> 8` divise par 256, `<< 8` multiplie par 256

---

## 1. Le Hook

L'addition et la soustraction en fixed-point marchent exactement comme avec des entiers normaux. Aucune surprise.  
Mais dès que tu multiplies ou divises deux fixed-points entre eux, quelque chose cloche.  
Le résultat est systématiquement **faux par un facteur de 256**.  
Pourquoi ? Et comment le corriger ?

---

## 2. La Douleur — Ce Qui Se Passe Si Tu Fais Rien

Tu veux calculer `2.0 × 3.0` en fixed-point.

Leurs raw :
- `Fixed(2.0)` → `raw = 2 × 256 = 512`
- `Fixed(3.0)` → `raw = 3 × 256 = 768`

Tu te dis : "je multiplie juste les raw" → `512 × 768 = 393 216`.

Tu vérifies le résultat : `393 216 / 256 = 1536`.

Mais `2.0 × 3.0` devrait valoir `6.0`, pas `1536`. Tu es **256 fois trop grand**.

Quelque chose s'est cassé quelque part — mais où ?

---

## 3. L'Invention — Trouver Le Bug en Raisonnant

Appelons `a` et `b` les vraies valeurs (`2.0` et `3.0`).  
Leurs raw sont `a × 256` et `b × 256`.

Quand tu multiplies les deux raw :

```
raw_a × raw_b
= (a × 256) × (b × 256)
= a × b × 256 × 256
= a × b × 256²
```

Or toi, tu veux stocker `a × b × 256` dans le résultat (c'est la convention fixed-point).  
Tu as `a × b × 256²` — il y a **un facteur 256 de trop**.

Il faut diviser par 256 après la multiplication. Soit : décaler de 8 bits vers la droite.

```
résultat_raw = (raw_a × raw_b) >> 8
             = (a × b × 256²) / 256
             = a × b × 256   ✓
```

**Vérification** : `(512 × 768) >> 8 = 393 216 / 256 = 1536`... toujours 1536 ?

Attends — `1536 / 256 = 6.0`. C'est bon ! Le raw `1536` représente bien `6.0`. On avait juste oublié de diviser le raw par 256 pour lire la vraie valeur. Le calcul est correct.

---

## 4. L'Idée Centrale — Une Phrase

> Multiplier deux raw fixed-point donne un résultat avec 256² comme dénominateur au lieu de 256 — il faut décaler de 8 bits à droite pour revenir à la convention.

---

## 5. Penses-y Comme...

**Les unités en physique** : Si `a = 3 mètres` et `b = 4 mètres`, alors `a × b = 12 mètres²` — pas des mètres.  
Tu as changé d'unité en multipliant. Il faut "convertir" le résultat dans la bonne unité.  
→ Ça mappe : multiplier deux raw donne du "256²", pas du "256". Le `>> 8` convertit dans la bonne unité.  
→ Où ça casse : en physique tu gardes les m², en fixed-point tu veux revenir à une unité simple.

**Les pourcentages** : `50% × 50%` devrait donner `25%`, mais si tu multiplies les nombres bruts `50 × 50 = 2500` — tu dois diviser par 100 pour revenir en pourcentage : `2500 / 100 = 25`. Même logique : multiplier deux "pour cent" donne du "pour dix-mille".  
→ Ça mappe : "pour cent" = dénominateur 100, "fixed-point" = dénominateur 256. Multiplier double le dénominateur, il faut le corriger.  
→ Où ça casse : 100 n'est pas une puissance de 2, donc on utilise `/ 100` au lieu de `>> 8`.

---

## 6. La Cascade d'Exemples — Multiplication

### Exemple 1 — `1.0 × 1.0` (le cas le plus simple)

Raw : `256 × 256 = 65 536`.  
Après correction : `65 536 >> 8 = 256`.  
Vraie valeur : `256 / 256 = 1.0`. ✓

### Exemple 2 — `2.0 × 3.0`

Raw : `512 × 768 = 393 216`.  
Après correction : `393 216 >> 8 = 1536`.  
Vraie valeur : `1536 / 256 = 6.0`. ✓

### Exemple 3 — `0.5 × 0.5`

Raw de `0.5` : `128`.  
`128 × 128 = 16 384`.  
Après correction : `16 384 >> 8 = 64`.  
Vraie valeur : `64 / 256 = 0.25`. ✓ (0.5 × 0.5 = 0.25)

### Exemple 4 — Pourquoi on cast en `long` avant de multiplier

`Fixed(300.0f)` a un raw de `300 × 256 = 76 800`.  
`76 800 × 76 800 = 5 898 240 000`.  
Un `int` 32 bits peut aller jusqu'à `2 147 483 647`. On est au-delà → **overflow**, résultat faux.  
En castant en `long` (64 bits) avant : `(long)76800 × 76800 = 5 898 240 000` → ça tient. Ensuite on `>> 8` et on stocke dans l'`int` du résultat.

---

## 7. Maintenant la Division — La Logique Inverse

Pour `a / b`, regardons ce qui se passe si tu divises les raw directement :

```
raw_a / raw_b
= (a × 256) / (b × 256)
= a / b
```

Tu obtiens `a / b` — un nombre **sans** le facteur 256. C'est 256 fois trop petit.

Il faut **multiplier par 256 avant de diviser** :

```
résultat_raw = (raw_a × 256) / raw_b
             = (raw_a << 8)  / raw_b
             = (a × 256 × 256) / (b × 256)
             = (a / b) × 256   ✓
```

**Pourquoi décaler AVANT et non après ?**  
Si tu fais `raw_a / raw_b` d'abord tu obtiens un entier tronqué, puis tu multiplies par 256 — tu as perdu la précision à jamais.  
Si tu fais `raw_a × 256` d'abord, tu conserves les décimales dans l'entier avant de diviser.

---

## 8. Exemples — Division

### Exemple 1 — `6.0 / 3.0`

Raw de `6.0` : `1536`. Raw de `3.0` : `768`.  
Naïf : `1536 / 768 = 2` → vraie valeur `2 / 256 = 0.0078...`. FAUX.  
Correct : `(1536 << 8) / 768 = 393 216 / 768 = 512` → vraie valeur `512 / 256 = 2.0`. ✓

### Exemple 2 — `1.0 / 4.0`

Raw de `1.0` : `256`. Raw de `4.0` : `1024`.  
Naïf : `256 / 1024 = 0` (division entière tronquée à zéro). Catastrophique.  
Correct : `(256 << 8) / 1024 = 65 536 / 1024 = 64` → vraie valeur `64 / 256 = 0.25`. ✓

---

## 9. Résumé Visuel — La Règle à Retenir

```
ADDITION / SOUSTRACTION :
  raw_résultat = raw_a + raw_b       ← rien à faire, le 256 se simplifie
  (a×256) + (b×256) = (a+b)×256 ✓

MULTIPLICATION :
  raw_résultat = (raw_a × raw_b) >> 8   ← corriger le 256 en trop
  (a×256) × (b×256) = a×b×256² → ÷256 → a×b×256 ✓

DIVISION :
  raw_résultat = (raw_a << 8) / raw_b   ← compenser le 256 manquant
  (a×256×256) / (b×256) = (a/b)×256 ✓
```

Et dans ton code, exactement :

```cpp
// Multiplication — décaler APRÈS
Fixed Fixed::operator*(const Fixed &other) const {
    Fixed result;
    result.fixed_point_value =
        ((long)fixed_point_value * other.fixed_point_value) >> fractional_value;
    return result;
}

// Division — décaler AVANT
Fixed Fixed::operator/(const Fixed &other) const {
    Fixed result;
    result.fixed_point_value =
        ((long)fixed_point_value << fractional_value) / other.fixed_point_value;
    return result;
}
```

---

## 10. Test Final

> **Question** : Pourquoi l'addition n'a pas besoin de correction, mais la multiplication si ?

<details>
<summary>Réponse</summary>

Addition : `(a×256) + (b×256) = (a+b) × 256`. Le facteur 256 reste exactement un. Rien à corriger.

Multiplication : `(a×256) × (b×256) = (a×b) × 256²`. Le facteur 256 apparaît **deux fois** parce que les deux opérandes l'apportaient chacun. Il faut en enlever un.

C'est la même raison pour laquelle `mètre + mètre = mètre` mais `mètre × mètre = mètre²`.

</details>

---

## 11. Ce que C'est PAS

**"Pour la multiplication, il faut décaler avant."**  
→ FAUX. C'est l'inverse de la division. Multiplication → décaler **après**. Division → décaler **avant**.

**"La division sans décalage donne juste un résultat un peu imprécis."**  
→ FAUX. Ça donne souvent `0`. `1.0 / 4.0` sans décalage = `256 / 1024 = 0` (division entière). Totalement faux.

**"Le cast en `long` c'est optionnel."**  
→ FAUX pour les grandes valeurs. Sans le cast, la multiplication de deux `int` peut déborder silencieusement et donner un résultat aléatoire. Le cast protège.
