#include "engine.h"


#define bool char
#define true 1
#define false 0

/* Constantes de troca de faixas. */
#define TO_LEFT -1
#define TO_RIGHT 1

#define MIDDLE_LANE 0
#define RIGHT_LANE 12
#define LEFT_LANE -12


/* Variáveis de manipulação dos objetos do jogo. */
float carPosX = 0;

/* Variáveis de controle. */
bool carAnimationEnabled = false;
int currentLane = MIDDLE_LANE;
int animationSide;
int nextLane;


void obstaclesGraphicEngine() {
  int lane;
  float distance;

  glPushMatrix();
  
  buildTrafficCone(lane, distance);

  glPopMatrix();
}

/** 
 * Trata a renderização e animação do carro.
 */
void carGraphicEngine() {
  glPushMatrix();

  if (carAnimationEnabled)
    changeLanes(animationSide);

  buildCar(green(), carPosX);

  glPopMatrix();
}

/**
 * Troca o carro de faixa. Se a troca é para a direita e a faixa atual é a central, então a próxima faixa é a da 
 * direita. Se não, a faixa atual será a da esquerda, o que significa que a próxima será a central. A mesma ideia se 
 * aplica para transições à esquerda.
 * 
 * @param side  : indica para qual lado será a troca. Se esquerda, side == -1, se direita, side == 1.
 */
void changeLanes(int side) {
  carPosX += side * 0.1;

  if (side == TO_RIGHT) {
    nextLane = currentLane == MIDDLE_LANE ? RIGHT_LANE : MIDDLE_LANE;

    if (carPosX >= nextLane) {
      carAnimationEnabled = false;
      currentLane = nextLane;
    }
  } else if (side == TO_LEFT) {
    nextLane = currentLane == MIDDLE_LANE ? LEFT_LANE : MIDDLE_LANE;

    if (carPosX <= nextLane) {
      carAnimationEnabled = false;
      currentLane = nextLane;
    }
  }

  glutPostRedisplay();
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
    case 'd':
      if (!carAnimationEnabled && currentLane != RIGHT_LANE) {
        carAnimationEnabled = true;
        animationSide = TO_RIGHT;
      }
      break;

    case 'a':
      if (!carAnimationEnabled && currentLane != LEFT_LANE) {
        carAnimationEnabled = true;
        animationSide = TO_LEFT;
      }
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
