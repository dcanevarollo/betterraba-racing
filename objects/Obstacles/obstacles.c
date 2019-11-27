#include "obstacles.h"

#define CUBE_SIZE 3
#define SPHERE_RADIUS 2
#define CONE_HEIGHT 5
#define CONE_BASE 1.5

/**
 * Arquivo responsável por criar os obstáculos nas pistas.
 */

/**
 * Cria uma caixa marrom.
 */
void buildBox(float posX, float posZ) {
  glPushMatrix();
    glTranslatef(posX, 0, -posZ);

    glPushMatrix();

    Color boxColor = brown();
    glColor3ub(boxColor.red, boxColor.green, boxColor.blue);

    glTranslatef(0, 1.5, 0);
    glutSolidCube(CUBE_SIZE);

    glPopMatrix();
  glPopMatrix();
}

/**
 * Cria um cone de trânsito.
 * 
 * @param posX  : posição no eixo X em que o cone será criado.
 * @param posZ  : posição no eixo Z em que o cone será criado.
 */
void buildTrafficCone(float posX, float posZ) {
  glPushMatrix();
    glTranslatef(posX, 0, -posZ);

    glPushMatrix();

    Color coneColor = orange();
    glColor3ub(coneColor.red, coneColor.green, coneColor.blue);

    glRotatef(-90.0, 1.0, 0, 0);
    glutSolidCone(CONE_BASE, CONE_HEIGHT, 50, 1);

    glPopMatrix();
  glPopMatrix();
}

/**
 * Cria uma pedra (apenas uma esfera cinza).
 */
void buildStone(float posX, float posZ) {
  glPushMatrix();
    glTranslatef(posX, 0, -posZ);

    glPushMatrix();

    Color stoneColor = darkGrey();
    glColor3ub(stoneColor.red, stoneColor.green, stoneColor.blue);

    glTranslatef(0, SPHERE_RADIUS, 0);
    glutSolidSphere(SPHERE_RADIUS, 40, 25);

    glPopMatrix();
  glPopMatrix();
}


/**
 * Cria um carro de cor aleatória como obstáculo.
 */
void buildRandomCar(float posX, float posZ) {
  glPushMatrix();

  buildCar(red(), posX, posZ);

  glPopMatrix();
}
