CC=g++
CFLAGS=-std=c++11
SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

%.d: %.cpp

%.o: game.cpp %.d
	$(CC) -c $(CFLAGS) $<

sfml-app: game.o
	$(CC) $< -o $@ $(SFMLFLAGS)

run: sfml-app
	./sfml-app

clean:
	rm -f sfml-app
	rm -f *.o
