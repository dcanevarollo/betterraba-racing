#include "renderization.h"


#define CLOSE_LIMIT -300  // Limite de aproximação do carro com o horizonte da cena.
#define SAFE_LIMIT 200  // Limite de segurança para criação de novos obstáculos.
#define SCENE_LIMIT 200  // Limite da cena (a partir de múltiplos deste são renderizados novos objetos).
#define SCENE_HORIZON 400  // "Horizonte" imaginário da cena.
#define OBSTACLE_INCREMENT 10  // Sempre adicionaremos 5 obstáculos por onda.
#define MAX_INCREMENT 40  // Não produziremos mais de 50 obstáculos.


void renderAllObstacles();


Properties carProperties;  // Armazena as propriedades do carro principal.
Properties *obstaclesProperties;  // Cada posição do vetor armazenará as propriedades de um obstáculo.

bool firstRender = true;  // Define a primeira renderização para controle dos boundaries.
bool needNewScenario = false;  // Define se é necessário a renderização de um novo cenário a frente.
bool refreshScene = true;  // Define se é necessário criar novas propriedades para novos obstáculos.

float scenarioRendPosition = 0;  // Posição de renderização do cenário.
float newScenarioRendPosition;  // Posição de renderização do novo cenário (impressão de "ambiente infinito").
float obstaclesRendPosition = 0;  // Posição de renderização dos obstáculos.
float lastObstacleRendPosition;  // Posição do último obstáculo renderizado.
float currentPositionHorizon = INIT_POS;  // posição atual do carro em relação ao horizonte da cena.
float currentPositionObstacles = INIT_POS;  // posição atual do carro em relação ao último obstáculo renderizado.
float difficulty = 0.5;  // Dificuldade do jogo. Incrementada a cada superação de ondas de obstáculos.

int obstaclesQuantity = 10;  // Quantidade de obstáculos renderizados.


Properties getCarProperties() {
  return carProperties;
}

void setCarProperties(Properties value) {
  carProperties = value;
}

Properties *getObstaclesProperties() {
  return obstaclesProperties;
}

void setObstaclesProperties(Properties *value) {
  obstaclesProperties = value;
}

int getObstaclesRendPosition() {
  return obstaclesRendPosition;
}

bool isFirstRender() {
  return firstRender;
}

void setFirstRender(bool value) {
  firstRender = value;
}

/**
 * Cria os limites para o carro principal. No caso, ele será renderizado inicialmente na faixa do meio, na posição 20
 * em z.
 */
void defineCarProperties() {
  carProperties.lane = MIDDLE_LANE;
  carProperties.distance = INIT_POS;
  carProperties.collisionX[0] = -1.5;
  carProperties.collisionX[1] = 1.5;
}

/**
 * Cria os limites para cadad obstáculo. É utilizado uma função de geração aleatória, tanto para definir qual faixa 
 * tanto para definir em qual distância em z ele será criado.
 */
void defineObstaclesProperties() {
  int i;
  int lane;
  float distance;
  time_t seed;

  srand((unsigned) time(&seed));

  if (!isFirstRender())
    free(obstaclesProperties);

  obstaclesProperties = (Properties *) malloc(obstaclesQuantity * sizeof(Properties));

  for (i = 0; i < obstaclesQuantity; i++) {
    lane = rand() % 3;
    distance = rand() % 30 + i * 50; // Os objetos ficarão mais distantes de acordo com sua posição i do vetor.

    switch (lane) {
      case 0:
        lane = LEFT_LANE;
        break;

      case 1:
        lane = MIDDLE_LANE;
        break;

      case 2:
        lane = RIGHT_LANE;
        break;

      default:
        lane = MIDDLE_LANE;
        break;
    }

    obstaclesProperties[i].distance = distance;
    obstaclesProperties[i].lane = lane;
    obstaclesProperties[i].collisionX[0] = lane - 1.5;
    obstaclesProperties[i].collisionX[1] = lane + 1.5;
    obstaclesProperties[i].collisionZ[0] = obstaclesRendPosition + distance;
  }
}

/** 
 * Trata a renderização e animação do carro.
 */
void renderMainCar(short int carColor) {
  glPushMatrix();

  if (isAnimationEnabled())
    changeLanes(getAnimationSide());

  buildMainCar(carColor, carProperties.lane, carProperties.distance);

  glPopMatrix();
}

/**
 * Trata a renderização dos obstáculos na pista. A distância em z e a faixa que aparecerão serão aleatórios. Cada pro-
 * priedade para cada obstáculo é uma posição do vetor de propriedades.
 */
void renderObstacles() {
  /* Define as propriedades dos obstáculos a serem criados. */
  if (refreshScene) {
    defineObstaclesProperties();

    if (!firstRender)
      obstaclesRendPosition = -SCENE_HORIZON;

    lastObstacleRendPosition = obstaclesProperties[obstaclesQuantity - 1].distance - obstaclesRendPosition;

    refreshScene = false;
  }

  glPushMatrix();

  glTranslatef(0, 0, obstaclesRendPosition);
  renderAllObstacles();
  
  glPopMatrix();
 
  obstaclesRendPosition += difficulty + 0.1;

  setPositionElements();
}

/**
 * Trata a renderização infinita do cenário e dos obstáculos.
 * Nome meramente ilustrativo.
 * 
 * @param scenario  : cenário a ser renderizado.
 */
void toInfiniteAndBeyond(short int scenario) {
  /* Renderiza o cenário na posição atual e a incrementa. */
  renderScenario(scenario, scenarioRendPosition);

  scenarioRendPosition += difficulty + 0.1;
  
  /* Se um novo cenário é necessário, renderiza-o na nova posição de renderização e a incrementa. */
  if (needNewScenario) {
    renderScenario(scenario, newScenarioRendPosition);
    newScenarioRendPosition += difficulty + 0.1;
  }

  /* Incrementa a posição do carro para comparar a distância do carro ao horizonte da pista. */
  currentPositionHorizon += difficulty + 0.1;

  float distanceToHorizon = SCENE_HORIZON - currentPositionHorizon;

  /* Se a distância atingiu seu limite, um novo cenário deve ser renderizado a frente. A nova posição de renderização, 
  no caso, será a distância para o horizonte mais um espaço de segurança, que chamaremos de limite de fechamento (ou 
  close limit). */
  if (distanceToHorizon <= SCENE_LIMIT) {
    /* Se é a primeira vez que essa condição será adentrada, a variável de controle needNewScenario terá valor falso.
    Nesse caso, setamos ela e a variável de refresh de obstáculos para verdadeiro. */
    if (!needNewScenario)
      needNewScenario = true;

    newScenarioRendPosition = -distanceToHorizon - SCENE_LIMIT;
  }

  /* Se a distância para o horizonte ultrapassou o oposto do limite de fechamento, significa que não é mais necessário
  renderizar o "antigo" cenário. Neste caso, a posição de renderização atual torna-se a nova posição e a posição do
  carro é resetada. */
  if (distanceToHorizon <= CLOSE_LIMIT) {
    scenarioRendPosition = newScenarioRendPosition;
    needNewScenario = false;
    currentPositionHorizon = 0;
  }

  /* A renderização dos obstáculos do cenário seguirá a mesma lógica do cenário. */
  currentPositionObstacles += difficulty + 0.1;

  float distanceToLastObstacle = lastObstacleRendPosition - currentPositionObstacles + SAFE_LIMIT;

  /* A dificuldade aumentará a cada onda de obstáculos superados. */
  if (distanceToLastObstacle <= 0) {
    
    if (difficulty <= 1.40) {
      difficulty += 0.09;
      obstaclesQuantity = obstaclesQuantity ==  MAX_INCREMENT ? obstaclesQuantity : obstaclesQuantity + OBSTACLE_INCREMENT;
    }
    
    refreshScene = true;
    currentPositionObstacles = 0;
  }

  renderObstacles();
}

/**
 * Renderiza todos os obstáculos de uma onda.
 */
void renderAllObstacles() {
  int k;

  /* Serão renderizados blocos de 10 obstáculos. O limite de blocos é, naturalmente, a quantidade de obstáculos no vetor
  dividido pelo tamanho do bloco (10). Na segunda onda, por exemplo, serão renderizados 20 obstáculos em 2 blocos de 
  10 obstáculos. */
  int limit = obstaclesQuantity/OBSTACLE_INCREMENT;
  for (k = 0; k < limit; k++) {
    int dozen = k * OBSTACLE_INCREMENT;

    buildRandomCar(obstaclesProperties[dozen + 0].lane, obstaclesProperties[dozen + 0].distance);
    buildStone(obstaclesProperties[dozen + 1].lane, obstaclesProperties[dozen + 1].distance);
    buildBox(obstaclesProperties[dozen + 2].lane, obstaclesProperties[dozen + 2].distance);
    buildTrafficCone(obstaclesProperties[dozen + 3].lane, obstaclesProperties[dozen + 3].distance);
    buildRandomCar(obstaclesProperties[dozen + 4].lane, obstaclesProperties[dozen + 4].distance);
    buildStone(obstaclesProperties[dozen + 5].lane, obstaclesProperties[dozen + 5].distance);
    buildTrafficCone(obstaclesProperties[dozen + 6].lane, obstaclesProperties[dozen + 6].distance);
    buildStone(obstaclesProperties[dozen + 7].lane, obstaclesProperties[dozen + 7].distance);
    buildBox(obstaclesProperties[dozen + 8].lane, obstaclesProperties[dozen + 8].distance);
    buildTrafficCone(obstaclesProperties[dozen + 9].lane, obstaclesProperties[dozen + 9].distance);
  }
}
