all:tetrisSimple

tetris: environment_tetris_final.o agent_clever.o learning_curve.o main.o
	gcc environment_tetris_final.o agent_clever.o learning_curve.o main.o -o tetris

tetrisSimple: environment_tetris_simple.o agent_clever.o learning_curve.o main.o
	gcc environment_tetris_simple.o agent_clever.o learning_curve.o main.o -o tetrisSimple

grid2D: environment_grid2D.o agent_clever.o learning_curve.o main.o
	gcc environment_grid2D.o agent_clever.o learning_curve.o main.o -o grid2D

grid2DBlocks: environment_grid2D_with_blocks.o agent_clever.o learning_curve.o main.o
	gcc environment_grid2D_with_blocks.o agent_clever.o learning_curve.o main.o -o grid2DBlocks

grid2DBlocksStoch: environment_grid2D_with_blocks_and_stochastic.o agent_clever.o learning_curve.o main.o
	gcc environment_grid2D_with_blocks_and_stochastic.o agent_clever.o learning_curve.o main.o -o grid2DBlocksStoch

environment_grid2D.o: environments/environment_grid2D.c environment.h environment_print.h 
	gcc -g -Wall environments/environment_grid2D.c -c -o environment_grid2D.o

environment_grid2D_with_blocks.o: environments/environment_grid2D_with_blocks.c environment.h environment_print.h 
	gcc -g -Wall environments/environment_grid2D_with_blocks.c -c -o environment_grid2D_with_blocks.o

environment_grid2D_with_blocks_and_stochastic.o: environments/environment_grid2D_with_blocks_and_stochastic.c environment.h environment_print.h 
	gcc -g -Wall environments/environment_grid2D_with_blocks_and_stochastic.c -c -o environment_grid2D_with_blocks_and_stochastic.o

environment_tetris_final.o: environments/environment_tetris_final.c environment.h environment_print.h 
	gcc -g -Wall environments/environment_tetris_final.c -c -o environment_tetris_final.o

environment_tetris_simple.o: environments/environment_tetris_simple.c environment.h environment_print.h 
	gcc -g -Wall environments/environment_tetris_simple.c -c -o environment_tetris_simple.o

agent_clever.o: agents/agent_clever.c agent.h
	gcc -g -Wall agents/agent_clever.c -c -o agent_clever.o

learning_curve.o: learning_curve.c learning_curve.h
	gcc -g -Wall learning_curve.c -c -o learning_curve.o

main.o: main.c environment.h environment_print.h agent.h learning_curve.h
	gcc -g -Wall main.c -c -o main.o

clean:
	rm -f *.o


# pas la peine de compiler les .h !!!
#il n'y a que la première cible d'appelée !!!
# possible de mettre des fctions orphelines, qui ne s'appellent 
# que si on écrit make fction

