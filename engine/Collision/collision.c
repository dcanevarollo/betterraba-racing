/**
 * Arquivo que contém as funções para controlar as colisões do jogo.
 */

#include "collision.h"


/* Definem o range de verificação (em -z) do ponto inicial ao final de colisão com um obstáculo. */
#define FIRST_POINT -130
#define LAST_POINT -158


int collisionControl = 0;  // Define qual objeto do vetor de obstáculos será analisado na colisão.


void collisionTreatment(char const *username, bool perspective) {
  int i;
  
  Properties carProperties = getCarProperties();
  Properties *obstaclesProperties = getObstaclesProperties();

  int obstaclesQuantity = getObstaclesQuantity();

  for (i = 0; i < obstaclesQuantity; i++)
    if (obstaclesProperties[i].collisionZ[0] < FIRST_POINT && obstaclesProperties[i].collisionZ[0] > LAST_POINT) {
      collisionControl = i;

      if (obstaclesProperties[collisionControl].lane == LEFT_LANE 
          && carProperties.collisionX[0] <= obstaclesProperties[collisionControl].collisionX[1])
        gameOver(username, perspective);
      else if (obstaclesProperties[collisionControl].lane == RIGHT_LANE 
          && carProperties.collisionX[1] >= obstaclesProperties[collisionControl].collisionX[0])
        gameOver(username, perspective);
      else if (obstaclesProperties[collisionControl].lane == MIDDLE_LANE 
          && carProperties.collisionX[0] <= obstaclesProperties[collisionControl].collisionX[1] 
          && carProperties.lane >= 0)  // Indo para a direita.
        gameOver(username, perspective);
      else if (obstaclesProperties[collisionControl].lane == MIDDLE_LANE 
          && carProperties.collisionX[1] >= obstaclesProperties[collisionControl].collisionX[0] 
          && carProperties.lane < 0)
        gameOver(username, perspective);
    }                                                       
}

/** 
* Esta função configura a posição do elemento em relação a renderização atual, auxiliando a função colisão e na variável
* collisionControl.
*/
void setPositionElements() {
  int i;

  Properties *obstaclesProperties = getObstaclesProperties();

  int obstaclesQuantity = getObstaclesQuantity();

  for (i = 0; i < obstaclesQuantity; i++)
    obstaclesProperties[i].collisionZ[0] = obstaclesProperties[i].distance - getObstaclesRendPosition();

  setObstaclesProperties(obstaclesProperties);
}
