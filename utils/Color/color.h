#ifndef COLOR_H
#define COLOR_H

/**
 * @author Douglas Canevarollo
 * Estrutura de cores do jogo. Todas as cores utilizadas na criação de objetos deve ser definida neste arquivo.
 */
typedef struct Color {
  short int red;
  short int green;
  short int blue;
} Color;

Color construtor(short int red, short int green, short int blue) {
  Color color;

  color.red = red;
  color.green = green;
  color.blue = blue;

  return color;
}

Color red();

Color green();

Color blue();

#endif
