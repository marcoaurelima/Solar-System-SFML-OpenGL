CC = g++
CCFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLU -lGLEW -lSOIL
DEPS = Planet.cpp Sun.cpp
all: 
	$(CC) main.cpp $(DEPS) -o main $(CCFLAGS)
	@./main

run:
	./main