#pragma once
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else 
	#include <GL/glut.h> 
#endif
#include <math.h>
#include "othello.hpp"


#define PI 3.1415926535
extern GameOthello *othello;

extern int fps;
extern int cursorX;
extern int cursorY;

extern int windowWidth;
extern int windowHeight;


class Scene{
	// enum scene_list{
	// 	select,
	// 	reverse
	// };

	// enum scene_list scState=select;
	long long elapsed_time=0; //ms(ミリ秒)
	// vec2d<int> putted_stone;
	// double dynamic_board[8][8]; //アニメーションする石

	void disp_select(void);
	void disp_reverse(void);


	public:
	enum scene_list{
		select,
		reverse
	};
	enum scene_list scState=select;
	vec2d<int> putted_stone;
	double dynamic_board[8][8]; //アニメーションする石

	void display(void);
	void change_scState(enum scene_list new_state);
};

extern Scene *scene;

void display(void);