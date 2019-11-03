#include "obstacles.h"

#define CUBE_SIZE 3
#define SPHERE_RADIUS 2
#define CONE_HEIGHT 5
#define CONE_BASE 1.5

/**
 * @author Douglas Canevarollo
 * Arquivo responsável por criar os obstáculos nas pistas.
 */

/**
 * Cria uma caixa marrom.
 */
void buildBox() {
  glPushMatrix();

  Color boxColor = brown();
  glColor3ub(boxColor.red, boxColor.green, boxColor.blue);

  glTranslatef(0, 1.5, 0);
  glutSolidCube(CUBE_SIZE);

  glPopMatrix();
}

/**
 * Cria um cone de trânsito.
 */
void buildTrafficCone() {
  glPushMatrix();

  Color coneColor = orange();
  glColor3ub(coneColor.red, coneColor.green, coneColor.blue);

  glRotatef(-90.0, 1.0, 0, 0);
  glutSolidCone(CONE_BASE, CONE_HEIGHT, 50, 1);

  glPopMatrix();
}

/**
 * Cria uma pedra (apenas uma esfera cinza).
 */
void buildStone() {
  glPushMatrix();

  Color stoneColor = grey();
  glColor3ub(stoneColor.red, stoneColor.green, stoneColor.blue);

  glTranslatef(0, SPHERE_RADIUS, 0);
  glutSolidSphere(SPHERE_RADIUS, 40, 25);

  glPopMatrix();
}


/**
 * Cria um carro de cor aleatória como obstáculo.
 */
void buildRandomCar() {
  Color randomColor = random();

  buildCar(randomColor);
}
