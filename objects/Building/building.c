#include "building.h"

/**
 * @author Douglas Canevarollo
 * Cria um objeto que simula um prédio para uma das pistas.
 * 
 * @param color   : cor do prédio.
 * @param height  : altura do prédio.
 * @param size    : tamanho da diagonal do cubo que serve como base do prédio.
 */
void buildBuilding(Color color, float height, float size) {
  glPushMatrix();

  glColor3ub(color.red, color.green, color.blue);
  glScalef(1, height, 1);
  glutSolidCube(size);

  glPopMatrix();
}
