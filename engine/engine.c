/**
 * @author Douglas Canevarollo
 * Motor gráfico do jogo.
 */


#include "engine.h"


#define INIT_POS -20  // Negativo pois a função de translação para os carros inverte o sinal.

/* Constantes de troca de faixas. */
#define TO_LEFT -1
#define TO_RIGHT 1

#define MIDDLE_LANE 0
#define RIGHT_LANE 12
#define LEFT_LANE -12



/* Variáveis de manipulação dos objetos do jogo. */
Boundary carBoundary;
Boundary obstaclesBoundaries[6];  // Uma posição para cada obstáculo renderizado.

/* Variáveis de controle. */
bool paused = true;  // Utilizada para pausar o jogo.
bool firstRender = true;  // Define a primeira renderização para controle dos boundaries.
bool shouldRenderNewScenario = false;  // Define se um novo cenário deve ser construído a frente.
bool carAnimationEnabled = false;  // Ativa a animação do carrinho (para troca de faixas).

int currentLane = MIDDLE_LANE;  // Faixa atual que o carro está.
int animationSide;  // Lado em que o carro ia se movimentar.
int nextLane;  // Próxima pista (na movimentação do carrinho).

float scenarioPos = 0;


/**
 * Trata a renderização dos obstáculos na pista. A distância em z e a faixa que aparecerão serão aleatórios. Cada limite
 * para cada obstáculo é uma posição do vetor de limites.
 */
void obstaclesGraphicEngine() {
  glPushMatrix();
  
  buildRandomCar(obstaclesBoundaries[0].lane, obstaclesBoundaries[0].distance);
  buildStone(obstaclesBoundaries[1].lane, obstaclesBoundaries[1].distance);
  buildBox(obstaclesBoundaries[2].lane, obstaclesBoundaries[2].distance);
  buildTrafficCone(obstaclesBoundaries[3].lane, obstaclesBoundaries[3].distance);
  buildRandomCar(obstaclesBoundaries[4].lane, obstaclesBoundaries[4].distance);
  buildStone(obstaclesBoundaries[5].lane, obstaclesBoundaries[5].distance);

  glPopMatrix();
}

/** 
 * Trata a renderização e animação do carro.
 */
void carGraphicEngine() {
  glPushMatrix();

  if (carAnimationEnabled)
    changeLanes(animationSide);

  buildCar(green(), carBoundary.lane, carBoundary.distance);

  glPopMatrix();
}

/**
 * Troca o carro de faixa. Se a troca é para a direita e a faixa atual é a central, então a próxima faixa é a da 
 * direita. Se não, a faixa atual será a da esquerda, o que significa que a próxima será a central. A mesma ideia se 
 * aplica para transições à esquerda.
 * 
 * @param side  : indica para qual lado será a troca. Se esquerda, side == -1, se direita, side == 1.
 */
void changeLanes(int side) {
  carBoundary.lane += side * 0.1;

  if (side == TO_RIGHT) {
    nextLane = currentLane == MIDDLE_LANE ? RIGHT_LANE : MIDDLE_LANE;

    if (carBoundary.lane >= nextLane) {
      carAnimationEnabled = false;
      currentLane = nextLane;
    }
  } else if (side == TO_LEFT) {
    nextLane = currentLane == MIDDLE_LANE ? LEFT_LANE : MIDDLE_LANE;

    if (carBoundary.lane <= nextLane) {
      carAnimationEnabled = false;
      currentLane = nextLane;
    }
  }

  glutPostRedisplay();
}

/**
 * Cria os limites para o carro principal. No caso, ele será renderizado inicialmente na faixa do meio, na posição 20
 * em z.
 */
void createCarBoundary() {
  carBoundary.lane = MIDDLE_LANE;
  carBoundary.distance = INIT_POS;
}

/**
 * Cria os limites para cadad obstáculo. É utilizado uma função de geração aleatória, tanto para definir qual faixa 
 * tanto para definir em qual distância em z ele será criado.
 */
void createObstacleBoundary() {
  int i;
  int lane;
  float distance;
  time_t seed;

  srand((unsigned) time(&seed));

  for (i = 0; i < 6; i++) {
    lane = rand() % 3;
    distance = rand() % 30 + i * 50;  // Os objetos ficarão mais distantes de acordo com sua posição i do vetor.

    switch(lane) {
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

    obstaclesBoundaries[i].lane = lane;
    obstaclesBoundaries[i].distance = distance;
  }
}

/**
 * Define as ações de algumas teclas do teclado.
 * 
 * @param key : tecla pressionada.
 * @param x   : posição x do mouse na tela.
 * @param y   : posição y do mouse na tela.
 */
void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'd':
      if (!carAnimationEnabled && currentLane != RIGHT_LANE) {
        carAnimationEnabled = true;
        animationSide = TO_RIGHT;
      }
      break;

    case 'a':
      if (!carAnimationEnabled && currentLane != LEFT_LANE) {
        carAnimationEnabled = true;
        animationSide = TO_LEFT;
      }
      break;

    case 'p':
      paused = !paused;
      break;

    case 'q':
      glutExit();
      exit(0);
      break;

    default:
      break;
  }

  glutPostRedisplay();
}

/**
 * Cria o cenário de acordo com a escolha do jogador.
 * 
 * @param scenario  : define qual cenário será renderizado.
 */
void buildScenario(short int scenario) {
  switch(scenario) {
    case 0:
      buildUrbanScenario();
      break;

    // case 1:
    //   buildDesertScenario();
    //   break;

    // case 2:
    //   buildFlorestScenario();
    //   break;

    default:
      printf("Erro na inicialização do cenário\n\n");
      glutExit();
      exit(1);
      break;
  }
}

/**
 * Função que executa o motor gráfico.
 * 
 * @param scenario  : define qual cenário será renderizado (recebido do arquivo main.c).
 */
void runEngine(short int scenario) {
  /* Definição dos limites dos objetos (na primeira renderização). */
  if (firstRender) {
    createCarBoundary();
    createObstacleBoundary();

    firstRender = false;
  }

  glPushMatrix();

  glTranslatef(0, 0, scenarioPos);
  scenarioPos += 0.1;

  shouldRenderNewScenario = scenarioPos >= 200 ? true : false;

  /* Cenários e objetos a serem construídos. */
  buildScenario(scenario);

  /* Renderização dos obstáculos do cenário. */
  obstaclesGraphicEngine();

  if (shouldRenderNewScenario) {
    glPushMatrix();

    glTranslatef(0, 0, -300);
    buildScenario(scenario);

    glPopMatrix();
  }

  glPopMatrix();

  /* Renderização do carro ("fixo"). */
  carGraphicEngine();

  if (!paused)
    glutPostRedisplay();
}
