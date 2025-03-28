# Rapport 

Groupe : L2G12

Alan Sottile, Calvin Graf, Lucas Hussain

# Introduction

Dans le cadre de ce laboratoire, nous avons dû travailler en groupe de 3 afin de créer
un programme permettant de retourner toutes les solutions possibles d'un jeu
de puzzle de 9 pièces avec 4 rotations possibles pour chaque pièce.

Nous avons à notre disposition une classe contenant les différentes pièces du jeu.

Le programme devra retourner une chaine de caractère sous la forme : 

"N° de la pièce(1 à 9)" + "rotation(a à d)".


# Nombre de permutations

Pour calculer le nombre de permutations possible, nous avons d'abord
calculés le nombre de permutations possible pour 2 pièces et
pour 3 pièces afin de trouver une formule.

Pour 1 pièce, nous avons trouvé qu'il y a 4 permutations possibles, pour 2 pièces, il y en a 32
et pour 3 pièces 384.

Nous avons donc trouvé la formule suivante : **n! * 4 <sup> n**

En utilisant cette formule, nous avons trouvé qu'il y avait **95'126'814'720** possibilités pour 9 pièces.

Avec cette formule on peut calculer le nombre de possibilités pour d'autres puzzles facilement et nous pouvons constater que cette formule exponentielle monte très rapidement.

Pour un puzzle de 4 pièces, (2x2) : 4! * 4^4 = 6’144 possibilités
Pour un puzzle de 16 pièces, (4x4) : 16! * 4^16 = 89’862’698’310’039’502’848’000 possibilités
Pour un puzzle de 25 pièces, (5x5) : 25! * 4^25 ≈ 1.75 * 10^40 possibilités

# Comparaison avec notre algorithme

Comme il était demandé, notre algorithme ne va pas au bout de chaque possibilité, lorsque deux pièces sont incompatibles, il passe à la pièce suivante jusqu'à la dernière et revient en arrière si aucune des 9 pièces n'est compatible pour cette possibilité.

Cela nous permet d'économiser énormément de temps pour la recherche de nos solutions. Nous pouvons constater que notre algorithme est environ 25 millions de fois plus rapide que si nous devions essayer toutes les possibilités une à une jusqu'au bout puisque nous avons seulement 3677 appels récursifs. Si nous devions toutes les essayer, cela prendrait beaucoup trop de temps pour trouver toutes les solutions possibles.

En opérant de cette manière, nous pouvons trouver qu'il y a 8 solutions au puzzle. Attention tout de même, car il faut prendre en compte que sur ces 8 solutions, en réalité il n'y en a que 2 solutions et celles-ci sont tournées dans 4 sens différents, ce qui nous donne notre chiffre de 8 solutions.

Nous avons décidé de rester sur un algorithme plutôt simple. Il est bien sûr possible de l'optimiser encore. Par exemple, nous avons ajouté que la pièce qui contient l'arrosoir inversé ne peut pas être au milieu et qu'il est donc inutile de la tester. Grâce à ça nous économisons environ 100 appels récursifs. Nous ne voulions cependant pas trop complexifier notre code pour quelques appels récursifs.

# Conclusion

Le texte commercial de Djeco "des millions de possibilités et une seule solution" est érroné étant donné qu'il existe plus de 95 milliards
de possibilités et que nous avons trouvé 8 solutions différentes possibles.
