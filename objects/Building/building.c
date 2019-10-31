#include "building.h"
#include "../../utils/Color/color.h"
#include <math.h>

#define RADIAN_INCR 0.017453293

int cameraRadius = 40;
int camPosX = 0, camPosY = 10, camPosZ = 40;
int camLookX = 0, camLookY = 0, camLookZ = 0;
int camAxisX = 0, camAxisY = 1, camAxisZ = 0;
float camAngle = 0;

/**
 * @author Douglas Canevarollo
 * Cria um objeto que simula um prédio para uma das pistas.
 * 
 * @param color   : cor do prédio.
 * @param height  : altura do prédio.
 * @param size    : tamanho da diagonal do cubo que serve como base do prédio.
 */
void buildBuilding(Color color, float height, float size) {
  glPushMatrix();

  glColor3ub(color.red, color.green, color.blue);
  glScalef(1, height, 1);
  glutSolidCube(size);

  glPopMatrix();
}

void display() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_SMOOTH);
  glEnable(GL_BLEND);

  Color backgroundColor = white();
  glClearColor(backgroundColor.red, backgroundColor.green, backgroundColor.blue, 0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45, 1, 1, 50);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(camPosX, camPosY, camPosZ, camLookX, camLookY, camLookZ, camAxisX, camAxisY, camAxisZ);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Color buildingColor = purple();
  buildBuilding(buildingColor, 15, 10);

  glutSwapBuffers();
}

void rotateCamera(int multiplier) {
  camAngle += (multiplier * RADIAN_INCR);

  camPosX = cameraRadius * sin(camAngle);
  camPosZ = cameraRadius * cos(camAngle);
}

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

int main(int argc,char **argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(800, 800);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("The Bouncing Ball");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);

  glutMainLoop();

  return 0;
}
