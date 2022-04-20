#ifdef __APPLE__
	#include <GLUT/glut.h>
#else 
	// #include <glut.h> 
	#include <GL/glut.h> 
#endif
// #include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "othello.hpp"
#include "display.hpp"

#define WIDTH 800
#define HEIGHT 800

void Idle() {
	// glutPostRedisplay(); //これはGPU使用率がマズそう
}

void timer(int value) {
	glutTimerFunc(10 , timer , 0);
	glutPostRedisplay();
}

void mouseMotion(int x,int y){
	// ウィンドウサイズを取得し、盤面に座標圧縮
	int sizeWX=glutGet(GLUT_WINDOW_WIDTH);
	int sizeWY=glutGet(GLUT_WINDOW_HEIGHT);
	int unitX=sizeWX/10;
	int unitY=sizeWY/10;
	if((unitX<x && x<sizeWX-unitX) && (unitY<y && y<sizeWY-unitY)){
		cursorX=(x-unitX)/unitX;
		cursorY=(y-unitY)/unitY;
		// glutPostRedisplay();
	}
}

void mouseClick(int button, int state, int x, int y){
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		if(scState==reverse) return;
		bool res=othello->put_stone(cursorY,cursorX);
		if(res){
			putted_stone=vec2d<int>(cursorY,cursorX);
			printf("CLICK\n");
			change_scState(reverse);
		}
	}
}

// 面倒なのでウィンドウの大きさを固定
void fixedWindow(int width,int height){
	// glutReshapeWindow(windowWidth,windowHeight);
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);	
	glutInitWindowSize(windowWidth,windowHeight);//ウィンドウの画面の幅と高さを指定
	// glutInitWindowSize(800,800);//ウィンドウの画面の幅と高さを指定
	glutInitWindowPosition(0, 0);//ウィンドウの場所を指定
	glutCreateWindow("Othello");//ウィンドウの名前
	glClearColor( 0 , 0.7, 0, 1);//オセロ盤の色
	// gluOrtho2D(0, 800, 800,0);//座標系の設定 ←使えない
    glOrtho(0, 800, 800, 0, -1, 1); //代わり
	glutDisplayFunc(display);//描画関数を指定
	glutIdleFunc(Idle);
	glutTimerFunc(10 , timer , 0);
	glutPassiveMotionFunc(mouseMotion); //マウスが動くと実行
	// glutReshapeFunc(fixedWindow);
	glutMouseFunc(mouseClick);

	glutMainLoop();
	return 0;
}