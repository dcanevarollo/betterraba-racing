#include "choose_map.h"


/* Mapas disponíveis. */
#define URBAN 0 
#define DESERT 1
#define FLOREST 2


short int currentMap = DESERT;


short int getCurrentMap() {
  return currentMap;
}

void setCurrentMap(short int value) {
  currentMap = value;
}

/**
 * Cria o cenário de acordo com a escolha do jogador.
 * 
 * @param scenario          : define qual cenário será renderizado.
 * @param renderizationPos  : indica a posição em que a matriz do cenário será renderizada.
 */
void renderScenario(short int scenario, float renderizationPos) {
  glPushMatrix();

  glTranslatef(0, 0, renderizationPos);

  switch (scenario) {
    case 0:
      buildUrbanScenario();
      break;

    case 1:
      buildDesertScenario();
      break;

    case 2:
      buildFlorestScenario();
      break;

    default:
      printf("Erro na inicializacao do cenario.\n\n");
      glutExit();
      exit(1);
      break;
  }

  glPopMatrix();
}

/**
 * Exibe o menu de escolha de mapa (mapa estático).
 */
void runMapMenu() {
  /* Define a cor de fundo (o "céu"). */
  glClearColor(204.0f/255.0f, 229.0f/255.0f,  1.0f, 1.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, 1, 1, 500);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(0, 20, 200, 0, 10, 0, 0, 1, 0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  renderText(-15, 80, 0, "ESCOLHA SEU MAPA", text(), LARGE);
  renderText(-9, 75, 0, "Escolher: -> ou <-", text(), REGULAR);
  renderText(-8, 70, 0, "Avancar: PgUp", text(), REGULAR);
  
  renderTextBox(20, 90, -20, 65, -1);

  renderScenario(currentMap, 0);
}
