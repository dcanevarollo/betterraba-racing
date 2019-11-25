#include "animation.h"


bool carAnimationEnabled = false;  // Ativa a animação do carrinho (para troca de faixas).

short int currentLane = MIDDLE_LANE;  // Faixa atual que o carro está.
short int animationSide;  // Lado em que o carro ia se movimentar.
short int nextLane;  // Próxima pista (na movimentação do carrinho).


bool isAnimationEnabled() {
  return carAnimationEnabled;
}

void setAnimationEnabled(bool value) {
  carAnimationEnabled = value;
}

short int getAnimationSide() {
  return animationSide;
}

void setAnimationSide(short int value) {
  animationSide = value;
}

short int getCurrentLane() {
  return currentLane;
}

void setCurrentLane(short int value) {
  currentLane = value;
}

/**
 * Troca o carro de faixa. Se a troca é para a direita e a faixa atual é a central, então a próxima faixa é a da 
 * direita. Se não, a faixa atual será a da esquerda, o que significa que a próxima será a central. A mesma ideia se 
 * aplica para transições à esquerda.
 * 
 * @param side  : indica para qual lado será a troca. Se esquerda, side == -1, se direita, side == 1.
 */
void changeLanes(int side) {
  Properties carProperties = getCarProperties();

  carProperties.lane += side * 1.5;
  carProperties.collisionX[0] = carProperties.lane - 1.5;
  carProperties.collisionX[1] = carProperties.lane + 1.5;

  if (side == TO_RIGHT) {
    nextLane = currentLane == MIDDLE_LANE ? RIGHT_LANE : MIDDLE_LANE;

    if (carProperties.lane >= nextLane) {
      carAnimationEnabled = false;
      currentLane = nextLane;
    }
  } else if (side == TO_LEFT) {
    nextLane = currentLane == MIDDLE_LANE ? LEFT_LANE : MIDDLE_LANE;

    if (carProperties.lane <= nextLane) {
      carAnimationEnabled = false;
      currentLane = nextLane;
    }
  }

  setCarProperties(carProperties);

  glutPostRedisplay();
}
