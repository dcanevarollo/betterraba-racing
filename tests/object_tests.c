/**
 * @author Douglas Canevarollo
 * Aqui deverão ser realizados os testes dos objetos e cenários desenvolvidos.
 */

#include <stdlib.h>
#include <math.h>
#include <GL/freeglut.h>

#include "../utils/Color/color.h"

/**
 * Inclua o arquivo que deseja testar aqui. Por exemplo:
 * #include "../objects/Car/car.h"
 */
// #include "../objects/Building/building.h"
#include "../objects/Car/car.h"

void display();
void drawProjectionCube();
void drawAxis();
void rotateCamera();
void keyboard(unsigned char key, int x, int y);

#define CAMERA_RADIUS 40
#define RADIAN_INCR 0.017453293

int camPosX = 0, camPosY = 40, camPosZ = CAMERA_RADIUS;
int camLookX = 0, camLookY = 10, camLookZ = 0;
int camAxisX = 0, camAxisY = 1, camAxisZ = 0;
float camAngle = 0;

/**
 * Função de exibição principal.
 */
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
  drawAxis();

  /* Insira a função de construção que quer testar aqui. Por exemplo:
  buildCar(); */
<<<<<<< HEAD
  // glTranslatcleef(-10, 0, 0);
  //buildCar(green(), 0, 0);
=======
  // glTranslatef(-10, 0, 0);
  buildCar(green(), 0, 0);
>>>>>>> master
  // glTranslatef(20, 0, 0);
  // buildBuilding(purple(), 4, 7);

  glutSwapBuffers();
}

/**
 * Cria um cubo auxiliar para trabalhar com os objetos. Isto ajudará no posicionamento dos mesmos.
 */
void drawProjectionCube() {
  glPushMatrix();

  Color tempCubeColor = yellow();
  glColor3ub(tempCubeColor.red, tempCubeColor.green, tempCubeColor.blue);

  glTranslatef(0, 12.5, 0);
  glutWireCube(25);

  glPopMatrix();
}

/**
 * Cria os eixos x, y e z para auxiliar na construção dos objetos.
 */
void drawAxis() {
  glPushMatrix();

  Color xColor = red();
  Color yColor = green();
  Color zColor = blue(); 

  glTranslatef(0, 0, 0);

  glBegin(GL_LINES);
    /* Eixo x. */
    glColor3f(xColor.red, xColor.green, xColor.blue);
    glVertex3f(0, 0, 0);
    glVertex3f(12.5, 0, 0);
    
    /* Eixo y. */
    glColor3f(yColor.red, yColor.green, yColor.blue);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 25, 0);
    
    /* Eixo z. */
    glColor3f(zColor.red, zColor.green, zColor.blue);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 12.5);
  glEnd();

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
