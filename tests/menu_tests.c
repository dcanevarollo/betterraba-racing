/***
 * @author Gabriel Andrey
 * Aqui deverão ser realizados os testes dos objetos e cenários desenvolvidos.
 */

#include <stdlib.h>
#include <math.h>
#include <GL/freeglut.h>
#include <string.h>

#include "../utils/Color/color.h"

/**
 * Inclua o arquivo que deseja testar aqui. Por exemplo:
 * #include "../objects/Car/car.h"
 */
// #include "../objects/Building/building.h"
 #include "../objects/Car/car.h"

void display();
void drawProjectionCube();
void rotateCamera();
void keyboard(unsigned char key, int x, int y);

#define CAMERA_RADIUS 40
#define RADIAN_INCR 0.017453293

int camPosX = 0, camPosY = 40, camPosZ = CAMERA_RADIUS;
int camLookX = 0, camLookY = 10, camLookZ = 0;
int camAxisX = 0, camAxisY = 1, camAxisZ = 0;
float camAngle = 0;
int color = 0;

/**
 * Função de exibição principal.
 */

void renderCarro(int color){
   
   if( color == 0 )
      buildCar(green(), 0, 0);
   if( color == 1 )
      buildCar(red(), 0, 0);
   if( color == 2 )
      buildCar(blue(), 0, 0);
   if( color == 3 )
      buildCar(white(), 0, 0);
   if( color == 4 )
      buildCar(black(), 0, 0);
   if( color == 5 )
      buildCar(grey(), 0, 0);
   if( color == 6 )
      buildCar(yellow(), 0, 0);
   if( color == 7 )
      buildCar(purple(), 0, 0);
   if( color == 8 )
      buildCar(lilac(), 0, 0);
   if( color == 9 )
      buildCar(orange(), 0, 0);
   if( color == 10 )
      buildCar(brown(), 0, 0);
   if( color == 11 )
      buildCar(darkGreen(), 0, 0);
   if( color == 12 )
      buildCar(beige(), 0, 0);
   if( color == 13 )
      buildCar(sand(), 0, 0);
   if( color == 14 )
      buildCar(darkGrey(), 0, 0);
   if( color == 15 )
      buildCar(lightOrange(), 0, 0);
         
}

void display() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_SMOOTH);
  glEnable(GL_BLEND);

  /* A cor de fundo será preta. */
  glClearColor(0, 0, 0, 0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, 1, 1, 70);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(camPosX, camPosY, camPosZ, camLookX, camLookY, camLookZ, camAxisX, camAxisY, camAxisZ);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* Objetos e eixos auxiliares. */
  drawProjectionCube();
 
  renderCarro(color);
 
  glutSwapBuffers();
}

/**
 * Cria um cubo auxiliar para trabalhar com os objetos. Isto ajudará no posicionamento dos mesmos.
 */
void drawProjectionCube() {
  glPushMatrix();

  Color tempCubeColor = yellow();
  glColor3ub(tempCubeColor.red, tempCubeColor.green, tempCubeColor.blue);
  glScalef(1, 3, 1);
  glTranslatef(0, -10, 0);
  glutSolidCube(20);

  glPopMatrix();
}

/**
 * Define as ações de algumas teclas do teclado.
 * 
 * @param key : tecla pressionada.
 * @param x   : posição x do mouse na tela.
 * @param y   : posição y do mouse na tela.
 */
void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'a':
      rotateCamera(-1);  // Rotates the camera to the left.
      break;

    case 'd':
      rotateCamera(1);  // Rotates the camera to the right.
      break;

    case 'q':
      glutExit();
      exit(0);
      break;

    case 'b':
      if(color >= 15)
         color = -1;
      color+= 1;  

    default:
      break;
  }

  glutPostRedisplay();
}

/**
 * Método para rotacionar a câmera em torno do centro de projeção.
 * 
 * @param multiplier  : define o sentido da rotação. 1 -> gira para a direita; -1 -> gira para a esquerda.
 */
void rotateCamera(int multiplier) {
  camAngle += (multiplier * RADIAN_INCR);

  camPosX = CAMERA_RADIUS * sin(camAngle);
  camPosZ = CAMERA_RADIUS * cos(camAngle);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(800, 600);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Test");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);

  glutMainLoop();

  return 0;
}
