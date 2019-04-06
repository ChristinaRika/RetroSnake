RetroSnake: RetroSnake.o Operate.o
	gcc -o RetroSnake RetroSnake.o Operate.o

RetroSnake.o: RetroSnake.c Operate.h
	gcc -c RetroSnake.c

Operate.o: Operate.c Operate.h
	gcc -c Operate.c