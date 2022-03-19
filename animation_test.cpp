#include <bits/stdc++.h>
#include <GL/glut.h>

#define PI 3.1415926535

using namespace std;

namespace global{
    double rotate=0;
}


void drawCircle2(double radius,double posx,double posy,double r,double g, double b,double rotate){
	glColor3d(r,g,b);
	
	int resolution=90; //ポリゴンの頂点数
	glBegin(GL_POLYGON);
	for(int i=0;i<resolution;i++){
		glVertex2d(posx+radius*cos(2*PI*i/resolution)*cos(rotate),
		posy+radius*sin(2*PI*i/resolution));
	}
	glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(global::rotate<PI/2 || global::rotate>3*PI/2)
        drawCircle2(80,400,400,1,1,1,global::rotate);
    else
        drawCircle2(80,400,400,0,0,0,global::rotate);
	glutSwapBuffers();

}

void timer(int value){
    global::rotate+=PI/100;
    while(global::rotate>2*PI)
        global::rotate-=2*PI;
    printf("%lf\n",global::rotate);
    glutPostRedisplay();
    glutTimerFunc(10 , timer , 0);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);	
	glutInitWindowSize(800,800);//ウィンドウの画面の幅と高さを指定
	// glutInitWindowSize(800,800);//ウィンドウの画面の幅と高さを指定
	glutInitWindowPosition(0, 0);//ウィンドウの場所を指定
	glutCreateWindow("Othello");//ウィンドウの名前
	glClearColor( 0 , 0.7, 0, 1);//オセロ盤の色
	// gluOrtho2D(0, 800, 800,0);//座標系の設定 ←使えない
    glOrtho(0, 800, 800, 0, -1, 1); //代わり
	glutDisplayFunc(display);//描画関数を指定
	// glutIdleFunc(Idle);
	glutTimerFunc(10 , timer , 0);
	// glutPassiveMotionFunc(mouseMotion); //マウスが動くと実行
	// glutReshapeFunc(fixedWindow);
	// glutMouseFunc(mouseClick);

	// othello = new GameOthello();

	glutMainLoop();
	return 0;
}