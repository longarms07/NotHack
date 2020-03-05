CC=g++
CFLAGS=-std=c++11

%.o: %.cpp
	$(CC) -c $< $(CFLAGS)

sfml-app: game.o
	$(CC) $< -o $@ $(CFLAGS)