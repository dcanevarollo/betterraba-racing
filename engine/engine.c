/**
 * @author Douglas Canevarollo
 * Motor gráfico do jogo.
 */

#include "engine.h"

/* Protótipos de funções encapsuladas. */
void changeLanes();
void toInfiniteAndBeyond(short int scenario);
void renderScenario(short int scenario, float renderizationPos);
void renderObstacles();
void renderMainCar();
void setObstaclesProperties();
void setCarProperties();
void configView();
void collisionTreatment();
void setPositionElements();

#define VIEW_DISTANCE 500  // Distância de visualização da câmera.
#define INIT_POS -150  // Negativo pois a função de translação para os carros inverte o sinal.
#define CLOSE_LIMIT -300  // Limite de aproximação do carro com o horizonte da cena.
#define SAFE_LIMIT 300    // Limite de segurança para criação de novos obstáculos.
#define SCENE_LIMIT 200   // Limite da cena (a partir de múltiplos deste são renderizados novos objetos).
#define SCENE_HORIZON 400 // "Horizonte" imaginário da cena.

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

int points = 0;

char userName[50];


int collisionControl = 0; // Define qual objeto do vetor de obstáculos sera analisado na colisão

/* Variáveis de manipulação dos objetos do jogo. */
Properties carProperties;           // Armazena as propriedades do carro principal.
Properties obstaclesProperties[10]; // Cada posição do vetor armazenará as propriedades de um obstáculo.

/* Variáveis de controle. */
bool paused = true;               // Utilizada para pausar o jogo.
bool firstRender = true;          // Define a primeira renderização para controle dos boundaries.
bool needNewScenario = false;     // Define se é necessário a renderização de um novo cenário a frente.
bool refreshScene = true;         // Define se é necessário criar novas propriedades para novos obstáculos.
bool carAnimationEnabled = false; // Ativa a animação do carrinho (para troca de faixas).

short int currentLane = MIDDLE_LANE; // Faixa atual que o carro está.
short int animationSide;             // Lado em que o carro ia se movimentar.
short int nextLane;                  // Próxima pista (na movimentação do carrinho).

float currentPositionHorizon = INIT_POS;   // posição atual do carro em relação ao horizonte da cena.
float currentPositionObstacles = INIT_POS; // posição atual do carro em relação ao último obstáculo renderizado.
float scenarioRendPosition = 0;            // Posição de renderização do cenário.
float newScenarioRendPosition;             // Posição de renderização do novo cenário (impressão de "ambiente infinito").
float obstaclesRendPosition = 0;           // Posição de renderização dos obstáculos.
float lastObstacleRendPosition;            // Posição do último obstáculo renderizado.
float difficulty = 1;                      // Dificuldade do jogo. Incrementada a cada superação de ondas de obstáculos.

/**
 * Troca o carro de faixa. Se a troca é para a direita e a faixa atual é a central, então a próxima faixa é a da 
 * direita. Se não, a faixa atual será a da esquerda, o que significa que a próxima será a central. A mesma ideia se 
 * aplica para transições à esquerda.
 * 
 * @param side  : indica para qual lado será a troca. Se esquerda, side == -1, se direita, side == 1.
 */
void changeLanes(int side) {
  carProperties.lane += side * 2;
  carProperties.collisionX[0] = carProperties.lane - 1.5;
  carProperties.collisionX[1] = carProperties.lane + 1.5;

  if (side == TO_RIGHT) {
    nextLane = currentLane == MIDDLE_LANE ? RIGHT_LANE : MIDDLE_LANE;

    if (carProperties.lane >= nextLane) {
      carAnimationEnabled = false;
      currentLane = nextLane;
    }
  }
  else if (side == TO_LEFT) {
    nextLane = currentLane == MIDDLE_LANE ? LEFT_LANE : MIDDLE_LANE;

    if (carProperties.lane <= nextLane) {
      carAnimationEnabled = false;
      currentLane = nextLane;
    }
  }

  glutPostRedisplay();
}

void savePoints() {
  FILE *file;
  char string[12];

  char numberOfLines;

  file = fopen("file.txt", "a");

  for (int c = getc(file); c != EOF; c = getc(file))
    if (c == '\n') // Increment count if this character is newline
      numberOfLines = numberOfLines + 1;

  intToString(points, string);

  fprintf(file , "%s ; %s\n", userName, string);

  fclose(file);
}

/**
 * Função responsável por renderizar um texto em tela
 * @param x     : posição do texto em X
 * @param y     : posição do texto em Y
 * @param string: array de char contendo o texto a ser renderizado
 */
void renderText(int x, int y, char *string) {
  glColor3f(1, 1, 1);
  glRasterPos2f(x, y);

  int stringSize = (int)strlen(string);

  for (int i = 0; i < stringSize; i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
  }
}

/**
 * Função responsável por renderizar a pontuação do jogo
 */
void renderPoints() {
  char string[12];

  points++;

  intToString(points, string);

  renderText(3, 80, string);
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

  scenarioRendPosition += difficulty + 3;
  
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
    difficulty += 0.08;
    refreshScene = true;
    currentPositionObstacles = 0;
  }
  
  renderObstacles();
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
 * Trata a renderização dos obstáculos na pista. A distância em z e a faixa que aparecerão serão aleatórios. Cada pro-
 * priedade para cada obstáculo é uma posição do vetor de propriedades.
 */
void renderObstacles() {
  /* Define as propriedades dos obstáculos a serem criados. */
  if (refreshScene) {
    setObstaclesProperties();

    if (!firstRender)
      obstaclesRendPosition = -lastObstacleRendPosition + SAFE_LIMIT;

    lastObstacleRendPosition = obstaclesProperties[9].distance - obstaclesRendPosition;

    refreshScene = false;
  }

  glPushMatrix();

  glTranslatef(0, 0, obstaclesRendPosition);

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
 
 obstaclesRendPosition += difficulty + 0.1;
 setPositionElements();
 
}

/** 
* Esta função configura a posição do elemento em relação a renderização atual, 
* auxiliando a função colisão e na variavel controle_colisão
*/
void setPositionElements() {
  int i = 0;
  for(i=0; i<10; i++)
    obstaclesProperties[i].collisionZ[0] = obstaclesProperties[i].distance - obstaclesRendPosition; 
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
 * Cria os limites para cadad obstáculo. É utilizado uma função de geração aleatória, tanto para definir qual faixa 
 * tanto para definir em qual distância em z ele será criado.
 */
void setObstaclesProperties() {
  int i;
  int lane;
  float distance;
  time_t seed;

  srand((unsigned)time(&seed));

  for (i = 0; i < 10; i++) {
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
 * Cria os limites para o carro principal. No caso, ele será renderizado inicialmente na faixa do meio, na posição 20
 * em z.
 */
void setCarProperties() {
  carProperties.lane = MIDDLE_LANE;
  carProperties.distance = INIT_POS;
  carProperties.collisionX[0] = MIDDLE_LANE - 1.5;
  carProperties.collisionX[1] = MIDDLE_LANE + 1.5;
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
 * Função que executa o motor gráfico.
 * 
 * @param scenario  : define qual cenário será renderizado (recebido do arquivo main.c).
 */
void collisionTreatment() {
  
  for(int i=0; i<10; i++) {

    if(obstaclesProperties[i].collisionZ[0] < -130 && obstaclesProperties[i].collisionZ[0] > -158) {      
      collisionControl = i;

      if(obstaclesProperties[collisionControl].lane == LEFT_LANE && 
              carProperties.collisionX[0] <= obstaclesProperties[collisionControl].collisionX[1]) 
        paused = true;

      if(obstaclesProperties[collisionControl].lane == RIGHT_LANE && 
              carProperties.collisionX[1] >= obstaclesProperties[collisionControl].collisionX[0]) 
        paused = true;
        
      if(obstaclesProperties[collisionControl].lane == MIDDLE_LANE && 
              carProperties.collisionX[0] <= obstaclesProperties[collisionControl].collisionX[1] && 
              carProperties.lane >= 0) // indo para a direita
        paused = true;
        
      if(obstaclesProperties[collisionControl].lane == MIDDLE_LANE && 
              carProperties.collisionX[1] >= obstaclesProperties[collisionControl].collisionX[0] && 
              carProperties.lane < 0)
        paused = true; 
      
    }

  }

}

void runEngine(short int scenario, char username[]) {
  configView();

  /* Definição das propriedades do carro (apenas na primeira renderização). */
  if (firstRender) {
    setCarProperties();
    renderObstacles();

    firstRender = false;
  }
  

  strcpy(userName, username);

  /* Cenários e objetos a serem construídos. */
  toInfiniteAndBeyond(scenario);

  /* Renderia o contador de pontos*/
  renderText(-14, 80, "Pontos: ");
  renderPoints();

  /* Renderização do carro ("fixo"). */
  renderMainCar();
  collisionTreatment();
  
  if (!paused)
    glutPostRedisplay();
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
        camPosY = 20;
        camPosZ = 200;
      } else {
        camPosY = 30;
        camPosZ = 100;
      }

      if (perspective) {
        camPosY = 20;
        camPosZ = 200;
      } else {
        camPosY = 30;
        camPosZ = 100;
      }

      break;

    /* Sai do jogo. */
    case 'q':
      savePoints();
      glutExit();
      exit(0);
      
      break;

    default:
      printf("Tecla invalida pressionada.\n\n");
      break;
  }

  glutPostRedisplay();
}
