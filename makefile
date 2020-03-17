CC=g++
CFLAGS=-std=c++11
SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cpp
	$(CC) -c $< $(CFLAGS)

sfml-app: game.o 
	$(CC) $< -o $@ $(SFMLFLAGS)