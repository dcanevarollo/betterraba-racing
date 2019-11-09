#include "urban.h"

#define STREET_EDGE 10

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

  glVertex3f(STREET_EDGE, 0, -100);
  glVertex3f(STREET_EDGE, 0, 100);
  glVertex3f(40, 0, 100);
  glVertex3f(40, 0, -100);

  glEnd();

  glBegin(GL_QUADS);

  glVertex3f(-STREET_EDGE, 0, -100);
  glVertex3f(-STREET_EDGE, 0, 100);
  glVertex3f(-40, 0, 100);
  glVertex3f(-40, 0, -100);

  glEnd();

  /* Retorna o sistema à origem. */
  glTranslatef(0, 0, 0);

  /* Cria os prédios decorativos. */
  positionBulding(true, 0, grey(), 2, 6);
  positionBulding(false, 5, yellow(), 2, 7);
  positionBulding(true, 15, lightOrange(), 4, 6);
  positionBulding(false, 20, grey(), 3, 6);
  positionBulding(true, 30, beige(), 4, 7);
  positionBulding(false, 35, lightOrange(), 4, 6);

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