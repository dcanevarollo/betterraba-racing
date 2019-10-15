//Aula 1 de Compuação Gráfica
//Data: 11/09/2019
//Programa para criar um braço mecânico em 3D com movimentos.
//Desenvolvedores: Giovana Giardini e Rafael Campos

//Desenvolvido no Ubuntu 18.04.3 LTS. 
//Para compilar execute o comando gcc Aula1_braco_mec.c -o braco -lglut -lGLU -lGL -lm e para executar ./braco

//Controles do programa:
//botôes x, y e z escolhem em relação a qual eixo que o braço vai girar. x: eixo x, y: eixo y, z:eixo z.
//botões w e s movimentam o braço todo.
//botões a e d movimentam a partir da esfera do meio.
//setas do teclado movimentam a câmera.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>

//Declaração de Variáveis Globais
//Ângulos dos cubos que formam o braço
int anguloBola1emX = 0, anguloBola1emY = 0, anguloBola1emZ = 0, anguloBola2emX = 0, anguloBola2emY = 0, anguloBola2emZ = 0;
int posx=0, posy=10, posz=20; //Variáveis que definem a posição da câmera
int oy=0,ox=0,oz=0;  //Variáveis que definem para onde a câmera olha
int lx=0, ly=1,  lz=0; //Variáveis que definem qual eixo estará na vertical do monitor.
int eixoDeRotacao = 0; //Variável que define em qual eixo o braço será rotacionado

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

   gluPerspective(45,1,1,150); //Define a projeçãoo como perspectiva
   
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

   glScalef(6, 2, 4);//Escala, tamanho, do cubo 1.
   glColor3ub(0, 0, 255);//Cor do cubo 1
   glutWireCube(1);//Definição (criação) do cubo 1

   glTranslatef(-0.2, 1, 0);
   glScalef(0.7, 0.8, 1);//Escala, tamanho, do cubo 1.
   glColor3ub(0, 0, 255);//Cor do cubo 1
   glutSolidCube(1);

   glTranslatef(1,-2,0);
   glScalef(0.7, 0.8, 1);//Escala, tamanho, do cubo 1.
   glColor3ub(0, 255, 0);//Cor do cubo 1
   glutWireSphere(0.2, 20, 20);
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


int main(int argc,char **argv) {
   glutInit(&argc, argv); // Initializes glut    
   
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Define as características do espaço vetorial.
   
   glutInitWindowSize(300, 300);
   glutInitWindowPosition(10, 10);
   glutCreateWindow("Braço mecânico");
   
   //Chamada das funções de formação da cena
   glutDisplayFunc(Display);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(TeclasEspeciais);
   
   glutMainLoop();
   
   return 0; 
}