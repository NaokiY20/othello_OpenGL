#pragma once
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else 
	#include <GL/glut.h> 
#endif
#include <math.h>
#include "othello.hpp"


#define PI 3.1415926535
extern GameOthello* othello;

extern int fps;
extern int cursorX;
extern int cursorY;

extern int windowWidth;
extern int windowHeight;

enum scene_state{
    select,
    reverse
};

extern enum scene_state scState;
extern long long elapsed_time; //ms(ミリ秒)
extern vec2d<int> putted_stone;
extern double dynamic_board[8][8];

void display(void);
void disp_select(void);
void disp_reverse(void);
void change_scState(enum scene_state new_state);
