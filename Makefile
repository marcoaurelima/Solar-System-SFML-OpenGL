CC = g++
CCFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLU -lGLEW -lSOIL -lglut
DEPS = Planet.cpp Sun.cpp Orbits.cpp SpaceShip.cpp Object.cpp
all: 
	$(CC) main.cpp $(DEPS) -o main $(CCFLAGS)
	@./main

run:
	./main