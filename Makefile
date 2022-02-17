LIBS = -lfreeglut -lopengl32
CC = g++

all: othello
othello: othello.cpp
	$(CC) othello.cpp -o run.exe $(LIBS)
