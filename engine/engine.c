/**
 * @author Douglas Canevarollo
 * Motor gráfico do jogo.
 */


#include "engine.h"


/* Protótipos de funções encapsuladas. */
void configView();
void toInfiniteAndBeyond(short int scenario);
void renderObstacles();
void renderMainCar();
void renderScenario(short int scenario, float renderizationPos);
void changeLanes();
void setCarProperties();
void setObstaclesProperties();


#define VIEW_DISTANCE 500  // Distância de visualização da câmera.
#define INIT_POS -150  // Negativo pois a função de translação para os carros inverte o sinal.
#define SCENE_LIMIT 150  // Limite da cena (a partir de múltiplos deste são renderizados novos objetos).
#define CLOSE_LIMIT 100  // Limite de aproximação do carro com o horizonte da cena.
#define SCENE_HORIZON 400  // "Horizonte" imaginário da cena.

/* Constantes de troca de faixas. */
#define TO_LEFT -1
#define TO_RIGHT 1

#define MIDDLE_LANE 0
#define RIGHT_LANE 12
#define LEFT_LANE -12


/* Variáveis de controle da câmera e perspectiva. */
bool perspective = true;

int camPosX = 0, camPosY = 20, camPosZ = 200;
int camLookX = 0, camLookY = 10, camLookZ = 0;
int camAxisX = 0, camAxisY = 1, camAxisZ = 0;

/* Variáveis de manipulação dos objetos do jogo. */
Properties carProperties;  // Armazena as propriedades do carro principal.
Properties obstaclesProperties[10];  // Cada posição do vetor armazenará as propriedades de um obstáculo.

/* Variáveis de controle. */
bool paused = true;  // Utilizada para pausar o jogo.
bool firstRender = true;  // Define a primeira renderização para controle dos boundaries.
bool needNewScenario = false;  // Define se é necessário a renderização de um novo cenário a frente.
bool refreshScene = true;  // Define se novos obstáculos devem ser criados na tela.
bool carAnimationEnabled = false;  // Ativa a animação do carrinho (para troca de faixas).

int currentLane = MIDDLE_LANE;  // Faixa atual que o carro está.
int animationSide;  // Lado em que o carro ia se movimentar.
int nextLane;  // Próxima pista (na movimentação do carrinho).

float currentPosition = INIT_POS;  // Posição atual do carro no jogo.
float renderizationPosition = 0;  // Posição de renderização do cenário e objetos.
float newRenderizationPosition;  // Posição de renderização do novo cenário (impressão de "ambiente infinito").


/**
 * Trata a renderização dos obstáculos na pista. A distância em z e a faixa que aparecerão serão aleatórios. Cada pro-
 * priedade para cada obstáculo é uma posição do vetor de propriedades.
 */
void renderObstacles() {
  glPushMatrix();
  
  buildRandomCar(obstaclesProperties[0].lane, obstaclesProperties[0].distance);
  buildStone(obstaclesProperties[1].lane, obstaclesProperties[1].distance);
  buildBox(obstaclesProperties[2].lane, obstaclesProperties[2].distance);
  buildTrafficCone(obstaclesProperties[3].lane, obstaclesProperties[3].distance);
  buildRandomCar(obstaclesProperties[4].lane, obstaclesProperties[4].distance);
  buildStone(obstaclesProperties[5].lane, obstaclesProperties[5].distance);
  buildTrafficCone(obstaclesProperties[6].lane, obstaclesProperties[6].distance);
  buildStone(obstaclesProperties[7].lane, obstaclesProperties[7].distance);
  buildBox(obstaclesProperties[8].lane, obstaclesProperties[8].distance);
  buildTrafficCone(obstaclesProperties[9].lane, obstaclesProperties[9].distance);

  glPopMatrix();
}

/** 
 * Trata a renderização e animação do carro.
 */
void renderMainCar() {
  glPushMatrix();

  if (carAnimationEnabled)
    changeLanes(animationSide);

  buildCar(blue(), carProperties.lane, carProperties.distance);

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
  carProperties.lane += side * 0.1;

  if (side == TO_RIGHT) {
    nextLane = currentLane == MIDDLE_LANE ? RIGHT_LANE : MIDDLE_LANE;

    if (carProperties.lane >= nextLane) {
      carAnimationEnabled = false;
      currentLane = nextLane;
    }
  } else if (side == TO_LEFT) {
    nextLane = currentLane == MIDDLE_LANE ? LEFT_LANE : MIDDLE_LANE;

    if (carProperties.lane <= nextLane) {
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
void setCarProperties() {
  carProperties.lane = MIDDLE_LANE;
  carProperties.distance = INIT_POS;
}

/**
 * Cria os limites para cadad obstáculo. É utilizado uma função de geração aleatória, tanto para definir qual faixa 
 * tanto para definir em qual distância em z ele será criado.
 */
void setObstaclesProperties() {
  int i;
  int lane;
  float distance;
  time_t seed;

  srand((unsigned) time(&seed));

  for (i = 0; i < 10; i++) {
    lane = rand() % 3;
    distance = rand() % 30 + i * 50;  // Os objetos ficarão mais distantes de acordo com sua posição i do vetor.

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
    /* Vai para a pista à direita. */
    case 'd':
      if (!paused && !carAnimationEnabled && currentLane != RIGHT_LANE) {
        carAnimationEnabled = true;
        animationSide = TO_RIGHT;
      }
      break;

    /* Vai para a pista à esquerda. */
    case 'a':
      if (!paused && !carAnimationEnabled && currentLane != LEFT_LANE) {
        carAnimationEnabled = true;
        animationSide = TO_LEFT;
      }
      break;

    /* Pausa/despausa o jogo. */
    case 'p':
      paused = !paused;
      break;

    /* Escolhe a perspectiva (câmera). */
    case 'c':
      perspective = !perspective;

      if (perspective) {
        camPosX = 0;
        camPosY = 20;
        camPosZ = 200;
      } else {
        camPosX = 3;
        camPosY = 30;
        camPosZ = 100;
      }

      break;

    /* Sai do jogo. */
    case 'q':
      glutExit();
      exit(0);
      break;

    default:
      printf("Tecla invalida pressionada.\n\n");
      break;
  }

  glutPostRedisplay();
}

/**
 * Faz as configurações de câmera e perspectiva do frame.
 */
void configView() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  /* Faz a escolha da projeção. */
  if (perspective)
    gluPerspective(45, 1, 1, VIEW_DISTANCE);
  else
    glOrtho(-40, 40, -50, 20, -250, 500);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(camPosX, camPosY, camPosZ, camLookX, camLookY, camLookZ, camAxisX, camAxisY, camAxisZ);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * Cria o cenário de acordo com a escolha do jogador.
 * 
 * @param scenario          : define qual cenário será renderizado.
 * @param renderizationPos  : indica a posição em que a matriz do cenário será renderizada.
 */
void renderScenario(short int scenario, float renderizationPos) {
  /* Define as propriedades dos obstáculos a serem criados. */
  if (refreshScene) {
    setObstaclesProperties();

    refreshScene = false;
  }

  glPushMatrix();

  glTranslatef(0, 0, renderizationPos);

  switch (scenario) {
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
      printf("Erro na inicializacao do cenario.\n\n");
      glutExit();
      exit(1);
      break;
  }

  /* Renderização dos obstáculos do cenário. */
  renderObstacles();

  glPopMatrix();
}

/**
 * Trata a renderização infinita do cenário e dos obstáculos.
 * Nome meramente ilustrativo.
 * 
 * @param scenario  : cenário a ser renderizado.
 */
void toInfiniteAndBeyond(short int scenario) {
  /* Renderiza o cenário na posição atual e a incrementa. */
  renderScenario(scenario, renderizationPosition);
  renderizationPosition += 0.1;

  /* Se um novo cenário é necessário, renderiza-o na nova posição de renderização e a incrementa. */
  if (needNewScenario) {
    renderScenario(scenario, newRenderizationPosition);
    newRenderizationPosition += 0.1;
  }

  /* Incrementa a posição do carro para comparar a distância do carro ao horizonte da pista. */
  currentPosition += 0.1;

  float distanceToHorizon = SCENE_HORIZON - currentPosition;

  /* Se a distância atingiu seu limite, um novo cenário deve ser renderizado a frente. A nova posição de renderização, 
  no caso, será a distância para o horizonte mais um espaço de segurança, que chamaremos de limite de fechamento (ou 
  close limit). */
  if (distanceToHorizon <= SCENE_LIMIT) {
    /* Se é a primeira vez que essa condição será adentrada, a variável de controle needNewScenario terá valor falso.
    Nesse caso, setamos ela e a variável de refresh de obstáculos para verdadeiro. */
    if (!needNewScenario) {
      needNewScenario = true;
      refreshScene = true;
    }
    
    newRenderizationPosition = -distanceToHorizon + CLOSE_LIMIT;
  }
  
  /* Se a distância para o horizonte ultrapassou o oposto do limite de fechamento, significa que não é mais necessário
  renderizar o "antigo" cenário. Neste caso, a posição de renderização atual torna-se a nova posição e a posição do
  carro é resetada. */
  if (distanceToHorizon < -CLOSE_LIMIT) {
    renderizationPosition = newRenderizationPosition;
    needNewScenario = false;
    currentPosition = 0;
  }
}

/**
 * Função que executa o motor gráfico.
 * 
 * @param scenario  : define qual cenário será renderizado (recebido do arquivo main.c).
 */
void runEngine(short int scenario) {
  configView();

  /* Definição das propriedades do carro (apenas na primeira renderização). */
  if (firstRender) {
    setCarProperties();

    firstRender = false;
  }

  /* Cenários e objetos a serem construídos. */
  toInfiniteAndBeyond(scenario);

  /* Renderização do carro ("fixo"). */
  renderMainCar();

  if (!paused)
    glutPostRedisplay();
}
