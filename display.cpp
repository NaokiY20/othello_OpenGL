#include "display.hpp"

int fps=100;
int cursorX=0;
int cursorY=0;
int windowWidth=800;
int windowHeight=800;
enum scene_state state=select;
enum scene_state last_state=select;
long long elapsed_time=0;

GameOthello *othello = new GameOthello();

void drawCircle(double radius,double posx,double posy,double r,double g, double b){
	glColor3d(r,g,b);
	
	int resolution=90; //ポリゴンの頂点数
	glBegin(GL_POLYGON);
	for(int i=0;i<resolution;i++){
		glVertex2d(posx+radius*cos(2*PI*i/resolution),
		posy+radius*sin(2*PI*i/resolution));
	}
	glEnd();
}

void drawMarker(int x,int y,double r,double g,double b){
	glColor3d(r,g,b);

	int originX=80+x*80;
	int originY=80+y*80;
	glBegin(GL_QUADS);
		glVertex2i(originX,originY);
		glVertex2i(originX,originY+80);
		glVertex2i(originX+80,originY+80);
		glVertex2i(originX+80,originY);
	glEnd();
}

void display(){
    switch(state){
        case select:
            disp_select();
        case reverse:
            disp_reverse();
        default:
            disp_select();
    }
    if(last_state!=state) elapsed_time=0;
    else elapsed_time+=1000/fps;
    last_state=state;
}

void disp_select(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//選択肢の表示
	othello->updateAble();
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(othello->able[i][j]!=0){
				drawMarker(j,i,0.5,0.8,1.0);
			}
		}
	}

	//カーソル
	drawMarker(cursorX,cursorY,1.0,1.0,0.0);

	//ラインを描く
	glColor3f(0,0,0);
	glLineWidth(3);//線幅の指定。省略可。指定しなければ1。
	glBegin(GL_LINES);
	for(int i=0;i<9;i++){
		glVertex2i(80+80*i,720);//縦線上端
		glVertex2i(80+80*i,80);//縦線下端
		glVertex2i(80,80+80*i);//横線左端
		glVertex2i(720,80+80*i);//横線右端
	}
	glEnd();

	//点を4箇所描く
	glColor3f(0,0,0);
	glPointSize(10);
	glBegin(GL_POINTS);
		glVertex2i(240,240);
		glVertex2i(240,560);
		glVertex2i(560,240);
		glVertex2i(560,560);
	glEnd();

	
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			int state=othello->board[i][j];
			switch(state){
				case 1:
					drawCircle(30,80+40+j*80,80+40+i*80,0,0,0);
					break;
				case 2:
					drawCircle(30,80+40+j*80,80+40+i*80,1,1,1);
					break;
				default:
					break;
			}
		}
	}

	glutSwapBuffers();
}

void disp_reverse(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//ラインを描く
	glColor3f(0,0,0);
	glLineWidth(3);//線幅の指定。省略可。指定しなければ1。
	glBegin(GL_LINES);
	for(int i=0;i<9;i++){
		glVertex2i(80+80*i,720);//縦線上端
		glVertex2i(80+80*i,80);//縦線下端
		glVertex2i(80,80+80*i);//横線左端
		glVertex2i(720,80+80*i);//横線右端
	}
	glEnd();

	//点を4箇所描く
	glColor3f(0,0,0);
	glPointSize(10);
	glBegin(GL_POINTS);
		glVertex2i(240,240);
		glVertex2i(240,560);
		glVertex2i(560,240);
		glVertex2i(560,560);
	glEnd();

	//
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			int state=othello->board[i][j];
			switch(state){
				case 1:
					drawCircle(30,80+40+j*80,80+40+i*80,0,0,0);
					break;
				case 2:
					drawCircle(30,80+40+j*80,80+40+i*80,1,1,1);
					break;
				default:
					break;
			}
		}
	}


}