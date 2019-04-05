# Labirinto-KMP-Backtracking
Algoritmo que encontrar uma forma de sair do labirinto. Consegue sair ao achar um padrão por onde passa usando o KMP, se for um caminho sem saída efetua o Backtracking.
O algoritmo lê o seguinte arquivo (retire tudo que está nos parenteses) por exemplo:

8                   (dimensão do mapa)
1 3                 (a posição x e y inicial do personagem)
7 5                 (a posição x e y da saída)
0 v 0 a 0 v 0 0     (um mapa aleatorio de sua preferencia, 0 são buracos onde o personagem não passa)
a r 0 r l r a 0
r 0 a v a l 0 v
0 v 0 r l 0 r r
a l l 0 r a l 0
0 0 v a a 0 v a
v r 0 r 0 r l 0
l 0 l v v a r v
lral                (a sequência necessária para achar a saída)
