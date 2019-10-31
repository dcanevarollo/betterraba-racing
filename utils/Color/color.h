#ifndef COLOR_H
#define COLOR_H

#include <stdlib.h>

/**
 * @author Douglas Canevarollo
 * Estrutura de cores do jogo. Todas as cores utilizadas na criação de objetos deve ser definida neste arquivo.
 */
typedef struct Color {
  short int red;
  short int green;
  short int blue;
} Color;

Color red();

Color green();

Color blue();

Color white();

Color black();

Color grey();
 
Color yellow();

Color purple();

Color lilac();

Color orange();

#endif
