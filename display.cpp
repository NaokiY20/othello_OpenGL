#include "display.hpp"
#include <stdio.h>
#include <string.h>

int fps=100;
int cursorX=0;
int cursorY=0;
int windowWidth=800;
int windowHeight=800;
enum scene_state scState=select;
enum scene_state last_scState=select;
long long elapsed_time=0;
vec2d<int> putted_stone;
double dynamic_board[8][8];

GameOthello *othello = new GameOthello();

void drawCircle(double radius,double posx,double posy,double r,double g, double b){
	glColor3d(r,g,b);
	
	int resolution=100; //ポリゴンの頂点数
	glBegin(GL_POLYGON);
	for(int i=0;i<resolution;i++){
		glVertex2d(posx+radius*cos(2*PI*i/resolution),
		posy+radius*sin(2*PI*i/resolution));
	}
	glEnd();
}

//回転機能搭載
void drawCircle2(double radius,double posx,double posy,double rotate){
	if(rotate<PI/2 || rotate>3*PI/2) glColor3d(0.0,0.0,0.0);
	else glColor3d(1.0,1.0,1.0);

	int resolution=100;
	glBegin(GL_POLYGON);
	for(int i=0;i<resolution;i++){
		glVertex2d(posx+radius*cos(2*PI*i/resolution)*cos(rotate),
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

void change_scState(enum scene_state new_state){
	scState=new_state;
	elapsed_time=0;
	for(int i=0;i<8;i++)
	for(int j=0;j<8;j++)
	dynamic_board[i][j]=-1;
}

void display(){
    switch(scState){
        case select:
            disp_select();
			break;
        case reverse:
            disp_reverse();
			break;
        default:
            disp_select();
			break;
    }
	elapsed_time+=1000/fps;
	// printf("%lld\n",elapsed_time);
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
	if(elapsed_time>500){
		scState=select;
		// othello->updatePass();
	}
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

	//動かさない駒の表示
	int state_board[8][8];
	memcpy(state_board,othello->board,sizeof(othello->board));
	std::vector<std::vector<vec2d<int>>> stone_lists=othello->reverse_stones[putted_stone.x][putted_stone.y];
	for(auto list: stone_lists){
		for(auto vec:list){
			state_board[vec.x][vec.y]=0;
		}
	}
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			int state=state_board[i][j];
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

	// 動く駒の表示
	for(auto list: stone_lists){
		for(auto vec: list){
			if(dynamic_board[vec.x][vec.y]<0.0){
				dynamic_board[vec.x][vec.y]=0.0;
			}
		}
	}
	// for(int i=0;i<8;i++){
	// 	for(int j=0;j<8;j++){
	// 		printf("%lf ",dynamic_board[i][j]);
	// 	}
	// 	printf("\n");
	// }

	int all_flame=50; //100フレームでアニメーション終了
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(dynamic_board[i][j]>=0.0){
				dynamic_board[i][j]+=PI/all_flame;
				// printf("%lf\n",dynamic_board[i][j]);
			}
		}
	}

	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			double rotate=dynamic_board[i][j];
			if(rotate<0.0) continue;
			if(othello->turn==BLACK){
				drawCircle2(30,80+40+j*80,80+40+i*80,rotate);
			}
			else{
				drawCircle2(30,80+40+j*80,80+40+i*80,rotate+PI);
			}
		}
	}



	glutSwapBuffers();
}