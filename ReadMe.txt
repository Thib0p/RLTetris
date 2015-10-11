Sommaire :
I   - Introduction
II  - Instructions
III - Conclusion
IV  - Idées d'amelioration et avis sur le projet

I - Introduction :

	L'objectif de ce projet est de réaliser un apprentissage par renforcement. Le pretexte est la résolution d'une grille de Tetris. L'agent ainsi generé est capable de travailler avec n'importe queltype d'environnement. Nous avons essayé de maximiser la modularité de notre code.
	
II - Instructions

	Une fois dans le repertoire src : 
make permet de créer l'agent agent_clever qui est un agent intelligent qui se déplace dans une grille 2D avec des blocks. Pour créer des agents évoluant dans d'autres environnement, il suffit de changer le nom de l'environnement dans le fichier makefile.


Il est possible de jouer avec beaucoup de paramètres dans les programmes.
Les modifications s'effectuent toujours au début des fichiers grâce aux "#define".

	a) Environnements : 

Pour changer la taille de la grille, taper simplement :
	./agent_clever nombre_de_lignes nombre_de_colonnes
ex :
	./agent_clever 5 4
permet de créer une grille avec 5 lignes et 4 colonnes.
Les valeurs par défaut sont définies dans des "#define" au début des fichiers.

Description des environnements :
		i)environment_grid1D.c
La grille 1D tout simplement
		ii)environment_grid2D.c
Même chose que la grille 1 dimension mais en 2 dimensions
		iii)environment_grid2D_with_blocks.c
Des blocs sont créés dans la grille. Il sont codés en dur. Pour les modifier, se reporter à la doc.
		iv)environment_grid2D_with_blocks_and_stochastic.c
Basé sur environment_grid2D_with_blocks, on rajoute du stochiastique en faisant en sorte que l'agent puisse bumper sur un bloc "sans faire expres".
		v)environment_tetris_simple.c
L'environnement de tetris simplifié : l'agent ne pose qu'un seul bloc à la fois (1x1)
		vi)environment_tetris_final.c :
L'environnement de tetris au complet avec les blocs du vrai tetris qui peuvent tourner etc. Pour faire fonctionner Tetris, il a fallu trouver une nouvelle façon de coder les états de la grille car si l'on a une grille 8 lignes par 4 colonnes soit 32 cases pouvant être occupées ou innocupées. Donc 2^32 états possibles. Il faut en plus de ça prendre en compte la pièce(6 possibilités) et sa rotation (4 possibilités) pour chaque état de la grille soit en réalité 3*2^37 possibilités ou 3*2^34 octets ( 51Go de mémoire à allouer..) D'où l'idée de ne coder comme état que la frontière de la grille, c'est à dire la position des cases remplies qui sont sur le dessus, avec la pièce et sa rotation. Pour une grille 8 lignes 4 colonnes on a donc 6*4*9^4 possibilités soit ~20 Ko de mémoire allouée.

Cette difference de performance est d'autant plus significative qu'ensuite il va falloir associer à chaque couple état-action un reward ( double (8octets)..)

	b) Agent : 
on peut décider du moment où l'on débute les actions déterminées, ainsi que la vitesse de diminution du epsilon. Epsilon étant le paramètre qui définit à quel point les actions sont déterministes ( epsilon = 1 => hasard total, epsilon = 0 => tout est determiné par les values)

	c) Main : 
PlOT à 1 permet d'afficher les learning curves, le mettre à 0 sinon.
PRECISION_PLOT est le nombre de rewards utilisés pour un point de la learning curve
NOMBRE_EP_FINAUX défini le nombre d'épisode que l'on affiche après la boucle principale

L'entier P permet de printer l'affichage graphique si P = 1.


III - Conclusion

	Nous nous sommes vraiment investis dans ce projet et aurions aimé pouvoir vous envoyer les résultats de nos tests mais nous esperons pouvoir vous les présenter la semaine prochaine lors de la soutenance du projet !

IV- Idées d'amélioration et avis sur le projet

	Ce fut un projet très intéressant de notre point de vue, Il pose des bases solides dans cette branche de l'apprentissage artificielle. 
	C'est un peu dommage que l'interface graphique n'ait pas fonctionnée. Il pourrait être interessant de travailler sur un autre environnement que le tetris pour vraiment voir les applications.
