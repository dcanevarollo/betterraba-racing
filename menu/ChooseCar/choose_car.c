#include "choose_car.h"


#define GREEN 0
#define RED 1
#define BLUE 2
#define YELLOW 3
#define PURPLE 4
#define LILAC 5
#define ORANGE 6


short int currentColor = 0;

float carAngle = 0;

int carAngleDivider = 0;


short int getCurrentColor() {
  return currentColor;
}

void setCurrentColor(short int value) {
  currentColor = value;
}


void buildMainCar(short int color, float posX, float posZ) {
  switch (color) {
    case GREEN:
      buildCar(green(), posX, posZ);
      break;

    case RED:
      buildCar(red(), posX, posZ);
      break;

    case BLUE:
      buildCar(blue(), posX, posZ);
      break;

    case YELLOW:
      buildCar(yellow(), posX, posZ);
      break;
    
    case PURPLE:
      buildCar(purple(), posX, posZ);
      break;

    case LILAC:
      buildCar(lilac(), posX, posZ);
      break;

    case ORANGE:
      buildCar(orange(), posX, posZ);
      break;

    default:
      buildCar(blue(), posX, posZ);
      break;
  }
}

void showCarMenu() {
  glPushMatrix();

  glRotatef(carAngle, 0, 1, 0);
  buildMainCar(currentColor, 0, 0);

  glPopMatrix();

  carAngle += 0.0001 * (++carAngleDivider % 360);

  glutPostRedisplay();
}
