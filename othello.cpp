// #ifdef __APPLE__
// 	#include <GLUT/glut.h>
// #else 
// 	#include <glut.h> 
// 	//#include <GL/glut.h> 
// #endif
#include <GL/glut.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800

#define PI 3.1415926535

int pos_othello=0;

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

void display(void)
{	
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

	
	drawCircle(30,80+40+pos_othello*80,80+40,1,1,1);
	glutSwapBuffers();
}

void Idle() {
	// glutPostRedisplay(); これはGPU使用率がマズそう
}

void timer(int value) {
	pos_othello=(pos_othello+1)%8;
	glutTimerFunc(100 , timer , 0);
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);	
	glutInitWindowSize(800,800);//ウィンドウの画面の幅と高さを指定
	glutInitWindowPosition(0, 0);//ウィンドウの場所を指定
	glutCreateWindow("Othello");//ウィンドウの名前
	glClearColor( 0 , 0.7, 0, 1);//オセロ盤の色
	// gluOrtho2D(0, 800, 800,0);//座標系の設定 ←使えない
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1); //代わり
	glutDisplayFunc(display);//描画関数を指定
	glutIdleFunc(Idle);
	glutTimerFunc(1000 , timer , 0);

	glutMainLoop();
	return 0;
}