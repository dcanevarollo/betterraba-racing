#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>

//Declaração de Variáveis Globais
int posx=0, posy=10, posz=20; //Variáveis que definem a posição da câmera
int oy=0,ox=0,oz=0;  //Variáveis que definem para onde a câmera olha
int lx=0, ly=1,  lz=0; //Variáveis que definem qual eixo estará na vertical do monitor.
int eixoDeRotacao = 0; //Variável que define em qual eixo o braço será rotacionado
int projecao = 0;

/* Radian angle increment value. */
#define RADIAN_INCR 0.017453293

#define CAMERA_RADIUS 30
/* Camera angle. */
float camAngle = 0;

//Protótipos das Funções
void Inicializa();
void Display();
void Mouse(int botao, int estado, int x, int y);
void keyboard (unsigned char key, int x, int y);
void TeclasEspeciais (int key, int x, int y);
void buildCar();
void rotateCamera();

void Display()
{   
   glEnable(GL_DEPTH_TEST);
   
   glEnable(GL_LINE_SMOOTH);
   glEnable(GL_POLYGON_SMOOTH); 

   glEnable(GL_SMOOTH);
   glEnable(GL_BLEND);
   
   // Inicializa parâmetros de rendering
   // Define a cor de fundo da janela de visualização como preta
   glClearColor(0.0, 0.0, 0.0, 0.0);    
   
   glMatrixMode(GL_PROJECTION);//glMatrixMode()- define qual matriz será alterada.
   glLoadIdentity();//"Limpa" ou "transforma" a matriz em identidade, reduzindo possíveis erros.

   if (projecao == 1)
      gluPerspective(45,1,1,150); //Define a projeção como perspectiva
   else
      glOrtho(-25, 25, -25, 25, -25, 25);
   
   glMatrixMode(GL_MODELVIEW);//glMatrixMode()- define qual matriz será alterada
   glLoadIdentity(); //"Limpa" ou "transforma" a matriz em identidade, reduzindo possíveis erros.

   gluLookAt(posx,posy,posz,ox,oy,oz,lx,ly,lz); //Define a pos da câmera, para onde olha e qual eixo está na vertical.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // "limpa" um buffer particular.
   
   buildCar();
   glutSwapBuffers(); //Executa a Cena.
}

void rotateCamera(int multiplier) {
  camAngle += (multiplier * RADIAN_INCR);

  posx = CAMERA_RADIUS * sin(camAngle);
  posz = CAMERA_RADIUS * cos(camAngle);
}

void buildCar(){
   
   // Rodas
   glTranslatef(2, 0, 2);
   glScalef(1, 1, 1);
   glColor3ub(0, 255, 0);
   glutSolidSphere(1, 50, 50);

   glTranslatef(-5, 0, 0);
   glScalef(1, 1, 1);
   glColor3ub(0, 255, 0);
   glutSolidSphere(1, 50, 50);

   glTranslatef(0, 0, -4);
   glScalef(1, 1, 1);
   glColor3ub(0, 255, 0);
   glutSolidSphere(1, 50, 50);

   glTranslatef(5, 0, 0);
   glScalef(1, 1, 1);
   glColor3ub(0, 255, 0);
   glutSolidSphere(1, 50, 50);
   
   // Chassi
   glTranslatef(-2, 2, 2);
   glScalef(10, 3, 6);//Escala, tamanho, do cubo 1.
   glColor3ub(0, 0, 255);//Cor do cubo 1
   glutSolidCube(1);//Definição (criação) do cubo 1

   // Teto
   glTranslatef(-0.15, 0.8, 0);
   glScalef(0.8, 1.5, 2);//Escala, tamanho, do cubo 1.
   glColor3ub(0, 0, 255);//Cor do cubo 1
   glutSolidCube(0.5);
   
   // Vidro da frente
   glTranslatef(0.21, 0, 0);
   glScalef(2, 3.5, 4.9);
   glRotatef(45, 0, 0, 1);
   glColor3ub(20, 20, 20);
   glutSolidCube(0.1);
   glTranslatef(0, -0.1, 0);
   glScalef(1, 1, 1);
   glColor3ub(20, 20, 20);
   glutSolidCube(0.1);

}

void keyboard (unsigned char key, int x, int y){
   switch (key) {
    case 'a':
      rotateCamera(-1);  // Rotates the camera to the left.
      break;

    case 'd':
      rotateCamera(1);  // Rotates the camera to the right.
      break;
   }
   glutPostRedisplay();
}

void TeclasEspeciais (int key, int x, int y)
{
   //Movimenta o braço no espaço, utilizando as "setas" do teclado
   if (key==GLUT_KEY_RIGHT)
   {
      posx+=5; ox+=5;
   }
   else if (key==GLUT_KEY_PAGE_UP)
   {
      posy+=5; oy+=5;
   }
   else if (key==GLUT_KEY_UP)
   {
      posz-=5; oz-=5;
   }
   else if (key==GLUT_KEY_LEFT)    
   { 
      posx-=5; ox-=5;
   }
   else if (key==GLUT_KEY_PAGE_DOWN)
   {
      posy-=5; oy-=5;
   }
   else if (key==GLUT_KEY_DOWN)
   {      
      posz+=5; oz+=5;
   }
   glutPostRedisplay();
}

void Mouse(int botao, int estado, int x, int y)
{  //botão - recebe o código do botão pressionado
   //estado - recebe se está pressionado ou não
   //x, y - recebem respectivamente as posições do mouse na tela
   switch (botao)
   {
      case GLUT_LEFT_BUTTON:
      if (estado == GLUT_DOWN)
      {                  
         projecao=1;
         posx=0; posy=10; posz=20;
         ox=0,oy=0,oz=0;
         lx=0, ly=1,lz=0;
         glutPostRedisplay();
      }
      break;

      case GLUT_RIGHT_BUTTON:
      if(estado == GLUT_DOWN)
      {
         projecao=0;
         posx=0; posy=10; posz=20;
         oy=0; ox=0;  oz=0;
         lx=0, ly=1, lz=0;
         glutPostRedisplay();
      }
      break;
   }
}


int main(int argc,char **argv) {
   glutInit(&argc, argv); // Initializes glut    
   
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Define as características do espaço vetorial.
   
   glutInitWindowSize(300, 300);
   glutInitWindowPosition(10, 10);
   glutCreateWindow("Braço mecânico");
   
   //Chamada das funções de formação da cena
   glutDisplayFunc(Display);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(Mouse);
   glutSpecialFunc(TeclasEspeciais);
   
   glutMainLoop();
   
   return 0; 
}