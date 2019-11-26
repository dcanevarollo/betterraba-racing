/**
 * @author Douglas Canevarollo, Rafel Campos, Gabriel Andrey e Douglas Brandão.
 * Arquivo principal do jogo.
 */


#define MAX_COLOR 5  // Índice máximo de cores.
#define MIN_COLOR 0  // Índice mínimo de cores.

#define MAX_MAP 2  // Índice máximo de mapas.
#define MIN_MAP 0  // Índice mínimo de cores.


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>

#include "./utils/Defines/defines.h"

#include "./engine/Root/root.h"

#include "./menu/ChooseCar/choose_car.h"
#include "./menu/ChooseMap/choose_map.h"


/* Controla qual tela estará visível ao jogador. */
bool carMenuActive = true;
bool mapMenuActive = false;
bool engineActive = false;


void display();
void runCarMenu();
void runMapMenu();
void specialKeyboard(int key, int x, int y);


/**
 * Função de exibição principal.
 */
void display() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_SMOOTH);
  glEnable(GL_BLEND);

  if (carMenuActive)
    runCarMenu();
  else if (mapMenuActive)
    runMapMenu();
  else if (engineActive)
    runEngine(getCurrentMap(), getCurrentColor(), "Douglas");

  glutSwapBuffers();
}

/**
 * Define as ações das teclas especiais do jogo.
 * 
 * @param key : tecla especial pressionada.
 * @param x   : posição x do mouse na tela.
 * @param y   : posição y do mouse na tela.
 */
void specialKeyboard(int key, int x, int y) {
  /* Essa função só estará ativa nos menus. */
  if (carMenuActive || mapMenuActive) {
    short int currentColor = getCurrentColor();
    short int currentMap = getCurrentMap();

    switch (key) {
      /* Escolhe a cor do carro ou o mapa. */
      case GLUT_KEY_RIGHT:
        if (carMenuActive) {
          if (currentColor < MAX_COLOR)
            currentColor++;
          else
            currentColor = MIN_COLOR;

          setCurrentColor(currentColor);
        } else {
          if (currentMap < MAX_MAP)
            currentMap++;
          else
            currentMap = MIN_MAP;

          setCurrentMap(currentMap);
        }

        break;

      /* Escolhe a cor do carro ou o mapa. */
      case GLUT_KEY_LEFT:
        if (carMenuActive) {
          if (currentColor > MIN_COLOR)
            currentColor--;
          else
            currentColor = MAX_COLOR;

          setCurrentColor(currentColor);
        } else {
          if (currentMap > MIN_MAP)
            currentMap--;
          else
            currentMap = MAX_MAP;

          setCurrentMap(currentMap);
        }

        break;

      /* Avança a tela. */
      case GLUT_KEY_UP:
        if (carMenuActive) {
          carMenuActive = false;
          mapMenuActive = true;
        } else {
          mapMenuActive = false;
          engineActive = true;
        }

        break;

      default:
        printf("Tecla invalida pressionada.\n\n");
        break;
    }

    glutPostRedisplay();
  }
}

/**
 * Função principal de inicialização do jogo.
 */
int main(int argc, char **argv) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(1024, 768);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Betterraba Racing");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeyboard);

  glutMainLoop();

  return 0;
}
