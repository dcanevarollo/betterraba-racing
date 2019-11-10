/**
 * @author Rafael Campos
 * Aqui deverão ser realizados os testes dos cenários desenvolvidos.
 */

#include <stdlib.h>
#include <GL/freeglut.h>

#include "../utils/Color/color.h"

/**
 * Inclua o arquivo que deseja testar aqui. Por exemplo:
 * #include "../scenarios/Urban/urban.h"
 */
#include "../engine/engine.h"
#include "../scenarios/Urban/urban.h"


void display();


/* Variáveis de controle da câmera. */
int camPosX = 0, camPosY = 20, camPosZ = 70;
int camLookX = 0, camLookY = 10, camLookZ = 0;
int camAxisX = 0, camAxisY = 1, camAxisZ = 0;


/**
 * Função de exibição principal.
 */
void display() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_SMOOTH);
  glEnable(GL_BLEND);

  /* Define a cor de fundo (o "céu"). */
  glClearColor(204.0f/255.0f, 229.0f/255.0f,  1.0f, 1.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, 1, 1, 500);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(camPosX, camPosY, camPosZ, camLookX, camLookY, camLookZ, camAxisX, camAxisY, camAxisZ);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* Cenários e objetos a serem construídos. */  
  buildUrbanScenario();

  /* Renderização do carro. */
  carGraphicEngine();

  /* Renderização dos obstáculos. */
  obstaclesGraphicEngine();

  glutSwapBuffers();
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
