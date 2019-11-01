#include "building.h"

#define WINDOW_SIZE 2

/**
 * @author Douglas Canevarollo
 * Cria um objeto que simula um prédio para uma das pistas. As cores e tamanhos serão definidas aleatoriamente, visto
 * que serão utilizados para compor o cenário do jogo.
 * 
 * @param color       : cor do prédio a ser construído.
 * @param heightScale : altura do prédio (multiplicará, em y, o parâmetro size). Utilizar valor entre 1 e 4.
 * @param size        : tamanho do cubo que desenhará o prédio. Utilizar valor entre 6 e 8.
 */
void buildBuilding(Color color, float heightScale, float size) {
  glPushMatrix();

  /* Estrutura principal. */
  glColor3ub(color.red, color.green, color.blue);
  glScalef(1, heightScale, 1);
  glutSolidCube(size);

  /* Janelas. */
  Color windowColor = black();
  glColor3ub(windowColor.red, windowColor.green, windowColor.blue);

  /* Retorna a escala em y para o valor original da matriz. */
  glScalef(1, 1/heightScale, 1);

  /* Em z, acrescentamos 1.1 à coordenada para que a janela fique levemente sobreposta ao prédio. */
  glTranslatef(-(size/4), 0, size/4 + 1.1);
  glutSolidCube(WINDOW_SIZE);

  glTranslatef(size/2, 0, 0);
  glutSolidCube(WINDOW_SIZE);

  glTranslatef(0, size/2, 0);
  glutSolidCube(WINDOW_SIZE);

  glTranslatef(-(size/2), 0, 0);
  glutSolidCube(WINDOW_SIZE);

  /* Cria mais um par de janelas em y caso seja um prédio bem alto. */
  if (heightScale >= 3) {
    glTranslatef(0, size/2, 0);
    glutSolidCube(WINDOW_SIZE);

    glTranslatef(size/2, 0, 0);
    glutSolidCube(WINDOW_SIZE);
  }

  glPopMatrix();
}
