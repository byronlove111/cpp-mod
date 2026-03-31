# Être un bon programmeur

*15 décembre 2025*

---

À première vue, ce blog pourrait ressembler à un énième article sur la façon dont l'IA pourrait, ou non, sonner le glas du génie logiciel et de la programmation.

Mais ce n'est que la surface. La vraie question que nous allons aborder est : qu'est-ce qui fait un bon programmeur, indépendamment de l'IA ou non ? Je vais soutenir que les principes fondamentaux pour être un bon programmeur à l'ère de l'IA sont très similaires à ce qu'ils étaient avant l'IA.

Ce qui est différent aujourd'hui, c'est la vitesse du changement. Elle est extrêmement rapide, et par conséquent, l'écart entre les bons et les mauvais programmeurs se creuse encore davantage. Les bons programmeurs seront bien plus productifs qu'avant, tandis que les mauvais stagneront.

Je ne pense pas que le niveau actuel de l'IA entraînera un changement fondamental où nous irions tous en vacances à la plage pendant que des IA surpuissantes écrivent du code et dirigent nos entreprises à notre place. Je pense plutôt que ce progrès va engendrer une accélération massive de la programmation elle-même et des capacités potentielles des programmeurs.

---

## La programmation, c'est construire des théories

Commençons par cette citation :

> *…le but premier et fondamental de la programmation n'est pas de produire des programmes, mais de permettre aux programmeurs de construire des théories sur la manière dont les problèmes en question sont résolus par l'exécution du programme.*

Si vous ne retenez qu'une seule chose de ce blog, que ce soit celle-là.

Malheureusement, quand on apprend la programmation comme un savoir-faire et comme un outil, on saute immédiatement l'étape de la construction de théorie. On vous donne un exercice : "construire une application de prise de notes avec React et MongoDB", ou quelque chose de plus théorique comme "comment améliorer la complexité temporelle O(n) dans le pire cas ici ?"

Ces exercices ne sont pas mauvais en soi. Les deux sont des choses importantes à savoir et à comprendre. Le problème, c'est que la construction de théories est rarement exercée dans l'enseignement formel. Et malheureusement, elle est rarement exercée au travail non plus.

Pourtant, les meilleures entreprises vous demandent de le faire en permanence, surtout dans les rôles les plus seniors. Votre travail consiste à comprendre le monde de l'utilisateur : ses besoins, ses désirs et ses problèmes. Et surtout, à déterminer s'il y a une valeur commerciale à résoudre ces problèmes. Ce n'est qu'une fois que vous avez une théorie et un argumentaire solide que vous passez à l'implémentation technique.

Puis vous découvrez que votre théorie était en partie fausse, et vous itérez le logiciel en fonction de vos croyances mises à jour. Dans certains cas, il faut d'abord construire pour avoir une théorie. Peu importe comment vous formez votre théorie.

Pour lever toute ambiguïté : l'implémentation technique a toujours beaucoup d'importance. On ne peut pas juste l'écarter d'un revers de main. L'essentiel à retenir, c'est que la construction de théorie précède l'implémentation technique. Une implémentation technique sans théorie ne vaut rien. Mais de même, une théorie avec une mauvaise implémentation technique ne vous mènera pas bien loin. Elle pourrait même vous envoyer dans la mauvaise direction, vous faisant croire que vous avez (in)firmé votre théorie, alors qu'en réalité vous avez simplement construit quelque chose qui ne l'a jamais correctement exprimée.

---

## L'IA est une couche de plus (certes puissante)

Au début, les gens écrivaient des programmes sur des cartes perforées, puis en code machine et en assembleur. À partir des années 50, des langages de haut niveau comme Fortran, COBOL, puis C ont émergé. Dans les années 90, des langages encore plus haut niveau comme Java et Python sont apparus. Aujourd'hui, un développeur web écrit rarement du JavaScript pur, mais plutôt du TypeScript dans un framework, qui est ensuite compilé en JS pur.

Pour le meilleur ou pour le pire, nous nous sommes abstraits très loin des cartes perforées et de l'assembleur.

Le programmeur moderne n'a (généralement) pas besoin de penser aux allocations mémoire en JavaScript. Tout est abstrait par le runtime et le moteur que vous utilisez. Des fuites mémoire occasionnelles peuvent survenir, donc il est bon de comprendre le concept et comment les déboguer. Mais pour la majeure partie de la journée, vous pouvez l'ignorer. Et c'est une bonne chose : cela nous permet de nous concentrer sur la livraison de logiciels plus rapidement aux utilisateurs sans se soucier des détails de bas niveau.

L'aspect crucial, c'est la confiance. Si V8 avait des corruptions mémoire une fois par heure, il ne fonctionnerait pas comme un bloc de construction fiable dans notre tour d'abstractions. L'IA est un autre bloc de construction dans cette tour. Juste une couche de plus. Maintenant, on n'a même plus besoin d'écrire le code React soi-même : on peut instruire l'IA, vérifier le résultat, et éventuellement le corriger légèrement.

Malheureusement, l'IA n'est pas encore aussi fiable que le moteur V8. Dans certains cas, on se retrouve simplement renvoyé en bas de la pile et on perd du temps à corriger ce que l'IA a écrit. Mais ce n'est pas un problème inhérent à l'IA. Il existe encore des cas où les compilateurs C ne produisent pas de code assez performant, et les programmeurs descendent analyser la sortie assembleur ou ont recours à des intrinsèques.

Ce problème existe à chaque niveau de la tour d'abstractions.

---

## Ne vous préoccupez pas de la tour

Le point de ces exemples est le suivant : si vous étiez un programmeur doué pour construire des théories dès le départ, vous réaliserez que peu importe dans quelle partie de la tour d'abstractions vous travaillez.

À chaque couche, vous devez toujours décider, juger et appliquer votre sens du discernement à ce qui doit être construit. Et surtout, vous devez être capable de réviser et de changer d'opinion. Le jugement survit à l'abstraction.

Ce que l'IA change réellement :

- **Vitesse d'itération** : vous pouvez vérifier et tester des théories beaucoup plus rapidement.
- **Outillage** : apprendre de nouveaux outils et langages de programmation devient significativement plus facile.

---

## Construire des théories

Ce serait un blog creux que de rager indéfiniment sur l'importance de construire des théories sans donner au moins quelques pistes concrètes pour le faire réellement.

Inutile de le préciser : je ne suis pas un expert dans ce domaine. Je suis juste un programmeur avec une opinion, ce qui est, je suppose, la première étape dans la construction de théories. Pour beaucoup de choses, vous avez probablement une meilleure intuition que vous ne le pensez. Nous avons tous utilisé des logiciels pénibles à utiliser, et des logiciels invisibles qui fonctionnent simplement.

La prochaine fois que quelque chose vous bloque, ou ne vous bloque pas, demandez-vous pourquoi. Puis creusez davantage.

Au-delà de ça, des livres comme *The Mom Test* sont assez bons. Ils vous aident à apprendre à poser de meilleures questions et à découvrir ce que les gens veulent vraiment, par opposition à ce qu'ils disent vouloir.

---

*Continuez à construire !*
