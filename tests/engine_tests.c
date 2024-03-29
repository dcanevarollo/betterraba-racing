/**
 * Teste de motor gráfico.
 */


#include <stdlib.h>
#include <GL/freeglut.h>

#include "../utils/Defines/defines.h"
#include "../engine/Root/root.h"

char userName[100];

void display();


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

  /* Passe o cenário desejado como parâmetro do motor gráfico. */
  runEngine(DESERT, userName);

  glutSwapBuffers();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(800, 600);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Beta test");

  // scanf("%s", userName);

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);

  glutMainLoop();

  return 0;
}
