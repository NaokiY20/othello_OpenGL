LIBS = -lfreeglut -lopengl32
CC = g++

all: othello
othello: main.cpp othello.cpp
	$(CC) main.cpp othello.cpp -o run.exe $(LIBS)
debug: debug.cpp othello.cpp
	$(CC) debug.cpp othello.cpp -o debug