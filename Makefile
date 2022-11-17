ifeq ($(OS),Windows_NT)
	LIBS = -lfreeglut -lopengl32
else
	LIBS = -framework GLUT -framework OpenGL
endif
CC = g++
# INCLUDE = -I /opt/homebrew/include

all: othello debug test bmp
othello: main.cpp othello.cpp display.cpp
	$(CC) main.cpp othello.cpp display.cpp -o run $(LIBS)
debug: debug.cpp othello.cpp
	$(CC) debug.cpp othello.cpp -o debug
test: animation_test.cpp
	$(CC) animation_test.cpp -o animation_test $(LIBS)
bmp: bmp_test.cpp
ifeq ($(OS),Windows_NT)
	$(CC) bmp_test.cpp -o bmp_test $(LIBS)
else
	# $(CC) bmp_test.cpp -o bmp_test $(LIBS) $(INCLUDE)
	$(CC) bmp_test.cpp -o bmp_test $(LIBS)
endif
