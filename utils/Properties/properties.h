#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <stdlib.h>

/**
 * @author Douglas Canevarollo
 * Estrutura que auxilia no armazenamento dos valores de criação dos obstáculos.
 */
typedef struct Properties {
  float lane;
  float distance;
  float collisionX[4];
  float collisionZ[4];
} Properties;

#endif
