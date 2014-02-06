iterative_deepening
===================

iterative deepening

the script builds a graph and searches the fastest way from Start to Ziel.
Zx = a Node
Kx = a neighbour/child from the Node. The other parameter is the way from Node to this child

Start Z1
Ziel Z6
Z1: Gelsenkirchen
K1: Z2, 20
K2: Z3, 15
Z2: Oberhausen
K1: Z1, 20
K2: Z4, 10
Z3: Essen
K1: Z1, 15
K2: Z5, 12
K3: Z6, 35
Z4: Duisburg
K1: Z2, 10
K2: Z5, 13
K3: Z6, 14
Z5: Muehlheim
K1: Z3, 15
K2: Z4, 13
Z6: Duesseldorf
K1: Z3, 35
K2: Z4, 14
