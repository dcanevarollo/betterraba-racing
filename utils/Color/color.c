#include "color.h"

/**
 * @author Douglas Canevarollo
 * Arquivo com funções que retornam determinada cor para usar no cenário.
 */

Color construtor(short int red, short int green, short int blue) {
  Color color;

  color.red = red;
  color.green = green;
  color.blue = blue;

  return color;
}

Color red() {
  return construtor(255, 0, 0);
}

Color green() {
  return construtor(0, 255, 0);
}

Color blue() {
  return construtor(0, 0, 255);
}

Color white() {
  return construtor(255, 255, 255);
}

Color black() {
  return construtor(64, 64, 64);
}

Color grey() {
  return construtor(160, 160, 160);
}
 
Color yellow() {
  return construtor(255, 255, 52);
}

Color purple() {
  return construtor(153, 51, 255);
}

Color lilac() {
  return construtor(255, 51, 255);
}

Color orange() {
  return construtor(255, 128, 0);
}

Color brown() {
  return construtor(63, 10, 10);
}

Color darkGreen() {
  return construtor(2, 47, 13);
}

Color beige() {
  return construtor(192, 122, 30);
}

Color sand() {
  return construtor(219, 159, 129);
}

Color darkSand() {
  return construtor(210, 150, 120);
}

Color darkGrey() {
  return construtor(96, 96, 96);
}

Color lightOrange() {
  return construtor(255, 204, 153);
}

Color darkRed() {
  return construtor(153, 0, 0);
}
