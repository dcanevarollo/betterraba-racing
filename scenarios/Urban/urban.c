#include "urban.h"
#include <stdio.h>


#define STREET_EDGE 10


void positionBulding(bool leftSidewalk, float distance, Color color, float heightScale, float size);
void createAllBuildings();


/**
 * @author Douglas Canevarollo
 * Cria o cenário urbano do frame renderizado.
 */
void buildUrbanScenario() {
  Color sidewalkColor = darkGrey();

  glPushMatrix();

  buildStreet();

  /* Monta as calçadas laterais. */
  glScalef(2, 3, 2);
  glColor3ub(sidewalkColor.red, sidewalkColor.green, sidewalkColor.blue);
  
  glBegin(GL_QUADS);

  glVertex3f(STREET_EDGE, 0, -500);
  glVertex3f(STREET_EDGE, 0, 150);
  glVertex3f(100, 0, 150);
  glVertex3f(100, 0, -500);

  glEnd();

  glBegin(GL_QUADS);

  glVertex3f(-STREET_EDGE, 0, -500);
  glVertex3f(-STREET_EDGE, 0, 150);
  glVertex3f(-100, 0, 150);
  glVertex3f(-100, 0, -500);

  glEnd();

  /* Cria os prédios decorativos. */
  createAllBuildings();

  glPopMatrix();
}

/**
 * @author Douglas Canevarollo
 * Cria e posiciona um prédio no cenário.
 * 
 * @param leftSidewalk  : caso verdadeiro, o prédio será posicionado na calçada esquerda. Caso falso, na direita.
 * @param distance      : representa a distância em z em que o prédio será constrúido.
 * @param color         : cor do prédio a ser construído.
 * @param heightScale   : altura do prédio. Utilizar valor entre 1 e 4.
 * @param size          : tamanho do cubo. Utilizar valor entre 6 e 7. */
void positionBulding(bool leftSidewalk, float distance, Color color, float heightScale, float size) {
  glPushMatrix();

  if (leftSidewalk)
    glTranslatef(-size/2 - STREET_EDGE - 2, 0, -distance);
  else
    glTranslatef(size/2 + STREET_EDGE + 2, 0, -distance);

  buildBuilding(color, heightScale, size);

  glPopMatrix();
}

/**
 * Cria todos os prédios que aparecerão na tela.
 */
void createAllBuildings() {
  glPushMatrix();

  glTranslatef(0, 0, 0);

  positionBulding(true, 5, grey(), 2, 6);
  positionBulding(false, 10, yellow(), 2, 7);
  positionBulding(true, 25, lightOrange(), 4, 6);
  positionBulding(false, 35, grey(), 3, 6);
  positionBulding(true, 50, purple(), 4, 7);
  positionBulding(false, 60, lightOrange(), 2, 6);
  positionBulding(true, 75, darkGreen(), 2, 6);
  positionBulding(false, 85, purple(), 4, 7);
  positionBulding(true, 100, beige(), 4, 6);
  positionBulding(false, 110, grey(), 3, 6);
  positionBulding(true, 125, lightOrange(), 2, 7);
  positionBulding(false, 135, yellow(), 3, 7);
  positionBulding(true, 150, purple(), 4, 7);
  positionBulding(false, 160, yellow(), 2, 7);
  positionBulding(true, 175, lightOrange(), 4, 6);
  positionBulding(false, 185, grey(), 3, 6);
  positionBulding(true, 200, purple(), 4, 7);
  positionBulding(false, 210, lightOrange(), 2, 6);
  positionBulding(true, 225, darkGreen(), 2, 6);
  positionBulding(false, 235, purple(), 4, 7);
  positionBulding(true, 250, beige(), 4, 7);
  positionBulding(false, 260, yellow(), 2, 7);
  positionBulding(true, 275, lightOrange(), 4, 6);
  positionBulding(false, 285, grey(), 3, 6);
  positionBulding(true, 300, purple(), 4, 7);
  positionBulding(false, 210, lightOrange(), 2, 6);
  positionBulding(true, 325, darkGreen(), 2, 6);
  positionBulding(false, 335, purple(), 4, 7);

  glPopMatrix();
}
