#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
// #include <GL/freeglut.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 320
#define HEIGHT 240

class BMP
{
public:
 unsigned long sizeX;  //横
 unsigned long sizeY; //縦
 char *Data;  //画像データ格納
 bool Load(char *filename);
 GLuint texture;
 void TexSet();
 BMP(char *FileName);
};

BMP::BMP(char *FileName){
 Load(FileName);
 TexSet();
}
bool BMP::Load(char *FileName) {
 FILE *File;
 unsigned long size;// イメージのバイトサイズ
 unsigned long i;// カウンタ
 unsigned short int planes;        //デバイス面数
 unsigned short int bpp;            // ピクセル数
 char temp;                         // カラー関係作業用
 //ファイルオープン
 if ((File = fopen(FileName, "rb"))==NULL){
  printf("ファイルがありません");
  return false;
 }
 //ビットマップの幅データ部分へ移動
 fseek(File, 18, SEEK_CUR);
 //横幅を読み込む
 if ((i = fread(&sizeX, 4, 1, File)) != 1) {
  printf("読み込みエラー");
  return false;
 }
 //縦幅を読み込む
 if ((i = fread(&sizeY, 4, 1, File)) != 1) {
  printf("読み込みエラー");
  return false;
 }
 //画像サイズの計算
 size = sizeX * sizeY * 3;//プレーン数を読み込む
 if ((fread(&planes, 2, 1, File)) != 1) {   //bmpは「1」になる
  printf("プレーン数が読み込めません");
  return false;
 }
 if (planes != 1) {
  printf("プレーン数が1以外です");
  return false;
 }
 //ピクセル値を読み込む
 if ((i = fread(&bpp, 2, 1, File)) != 1) {
  printf("ビット数が読めません");
  return false;
 }
 if (bpp != 24) {//24bppでなければエラー
   printf("24ビット画像ではありません");
   return false;
  }
  //24ビット飛ばして、カラーデータ(RGB)部分へ
  fseek(File, 24, SEEK_CUR);    //データ読み込み
  Data = (char *) malloc(size);
  if (Data == NULL) {
   printf("メモリが確保できません");
   return false;
  }
  if ((i = fread(Data, size, 1, File)) != 1) {
   printf("データが読めません");
   return false;
  }
  for (i=0;i<size;i+=3) { //bgr -> rgb
   temp = Data[i];
   Data[i] = Data[i+2];
   Data[i+2] = temp;
  }
  return true;
}

void BMP::TexSet()
{
 glEnable( GL_TEXTURE_2D );
 glGenTextures( 1, &texture );
 glBindTexture( GL_TEXTURE_2D, texture );
 glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
 glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
 glTexImage2D( GL_TEXTURE_2D, 0, 3, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, Data );
 glBindTexture( GL_TEXTURE_2D, 0 );
}

BMP *bmp;

void display(void)
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 glOrtho(0.0, WIDTH, HEIGHT, 0.0, -1.0, 1.0);

 glEnable(GL_TEXTURE_2D);//テクスチャ有効
 glBindTexture( GL_TEXTURE_2D, bmp->texture );
    glEnable(GL_ALPHA_TEST);//アルファテスト開始
    glBegin(GL_POLYGON);
 glTexCoord2f(0.0f, 0.0f); glVertex2d(10 , 230);//左下
 glTexCoord2f(0.0f, 1.0f); glVertex2d(10 ,  10);//左上
 glTexCoord2f(1.0f, 1.0f); glVertex2d( 310 ,  10);//右上
 glTexCoord2f(1.0f, 0.0f); glVertex2d( 310 , 230);//右下
    glEnd();
    glDisable(GL_ALPHA_TEST);//アルファテスト終了
    glDisable(GL_TEXTURE_2D);//テクスチャ無効

 glutSwapBuffers();
}
void idle(void)
{
 glutPostRedisplay();
}
void Init(){
 glClearColor(0.0, 0.0, 0.0, 1.0);
 glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
 bmp = new BMP("sample.bmp");
}

int main(int argc, char *argv[])
{
 glutInitWindowPosition(100, 100);
 glutInitWindowSize(WIDTH, HEIGHT);
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
 glutCreateWindow("BMP画像を読み込んで表示");
 glutDisplayFunc(display);
 glutIdleFunc(idle);
 Init();
 glutMainLoop();
 return 0;
}