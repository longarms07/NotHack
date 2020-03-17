CC=g++
CFLAGS=-std=c++11 -MMD -MP
SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

game.app: game.o
	$(CC) $< -o $@ $(SFMLFLAGS)

run: game.app
	./game.app

clean:
	rm -f sfml-app
	rm -f *.o
	rm -f *.d

-include *.d