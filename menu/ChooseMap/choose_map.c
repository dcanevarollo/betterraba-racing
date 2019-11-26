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


void showMapMenu() {
  renderText(-15, 80, 0, "ESCOLHA SEU MAPA", text(), LARGE);
  renderText(-9, 75, 0, "Escolher: -> ou <-", text(), REGULAR);
  renderText(-8, 70, 0, "Avancar: PgUp", text(), REGULAR);
  
  renderTextBox(20, 90, -1, -20, 65);

  renderScenario(currentMap, 0);
}
