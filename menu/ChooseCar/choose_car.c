/**
 * Funções para escolha de carro no menu.
 */

#include "choose_car.h"


/* Cores disponíveis para o carro principal. */
#define GREEN 0
#define BLUE 1
#define YELLOW 2
#define PURPLE 3
#define LILAC 4
#define ORANGE 5


short int currentColor = GREEN;  // Cor atual do carro exibido.

float carAngle = 0;  // Ângulo de exibição do carro (para sua rotação).

int carAngleDivider = 0;  // Divisor inteiro do ângulo de rotação (para ser possível utilizar a função mod).


short int getCurrentColor() {
  return currentColor;
}

void setCurrentColor(short int value) {
  currentColor = value;
}


/**
 * Constrói o carro principal com a cor escolhida.
 * 
 * @param color : cor escolhida.
 * @param posX  : posição x de renderização.
 * @param posZ  : posição -z de renderização.
 */
void buildMainCar(short int color, float posX, float posZ) {
  switch (color) {
    case GREEN:
      buildCar(green(), posX, posZ);
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

/**
 * Exibe o menu (o carro girando lentamente).
 */
void runCarMenu() {
  /* Define a cor de fundo (fundo escuro). */
  glClearColor(32.0f/255.0f, 32.0f/255.0f,  32.0/255.0f, 1.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, 1, 1, 70);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(0, 20, 40, 0, 0, 0, 0, 1, 0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  renderText(-3, 15, 0, "ESCOLHA SEU CARRO", text(), LARGE);
  renderText(-1.8, 14, 0, "Escolher: -> ou <-", text(), REGULAR);
  renderText(-1.5, 13, 0, "Avancar: PgUp", text(), REGULAR);

  glPushMatrix();

  glRotatef(carAngle, 0, 1, 0);

  glTranslatef(0, -5, 0);
  buildMainCar(currentColor, 0, 0);

  glPopMatrix();

  carAngle += 0.0001 * (++carAngleDivider % 360);

  glutPostRedisplay();
}
