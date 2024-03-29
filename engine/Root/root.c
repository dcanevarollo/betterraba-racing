/**
 * Motor gráfico principal do jogo.
 */

#include "root.h"


#define VIEW_DISTANCE 500  // Distância de visualização da câmera.


/* Protótipos de funções encapsuladas. */
void configView();


bool paused = true;  // Utilizada para pausar o jogo.
bool finished = false;  // Define se o jogo terminou.
bool mustShowRanking = false;  // Define se o ranking deve ser exibido.

/* Variáveis de controle da câmera e perspectiva. */
bool perspective = true;

int camPosX = 0, camPosY = 20, camPosZ = 200;
int camLookX = 0, camLookY = 10, camLookZ = 0;
int camAxisX = 0, camAxisY = 1, camAxisZ = 0;

char userName[100];


void setPaused(bool value) {
  paused = value;
}

void setFinished(bool value) {
  finished = value;
}

/**
 * Faz as configurações de câmera e perspectiva do frame.
 */
void configView() {
  /* Define a cor de fundo (o "céu"). */
  glClearColor(204.0f/255.0f, 229.0f/255.0f,  1.0f, 1.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  /* Se o jogo não estiver finalizado, o usuário pode mudar a câmera. */
  if (finished == false) {
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
}


/**
 * Função que executa o motor gráfico.
 * 
 * @param scenario  : define qual cenário será renderizado (recebido do arquivo main.c).
 */
void runEngine(short int scenario, short int carColor, char const *username) {
  if (mustShowRanking)
    showRanking();
  else {
    configView();

    /* Definição das propriedades do carro (apenas na primeira renderização). */
    if (isFirstRender()) {
      defineCarProperties();
      renderObstacles();

      setFirstRender(false);
    }
    
    strcpy(userName, username);

    /* Cenários e objetos a serem construídos. */
    toInfiniteAndBeyond(scenario);
    
    /* Renderia o contador de pontos*/
    renderPoints(perspective, paused);

    /* Renderização do carro ("fixo"). */
    renderMainCar(carColor);

    /* Tratamento de colisões. */
    collisionTreatment(userName, perspective);
    
    if (!paused)
      glutPostRedisplay();
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
      if (!paused && !isAnimationEnabled() && getCurrentLane() != RIGHT_LANE) {
        setAnimationEnabled(true);
        setAnimationSide(TO_RIGHT);
      }

      break;

    /* Vai para a pista à esquerda. */
    case 'a':
      if (!paused && !isAnimationEnabled() && getCurrentLane() != LEFT_LANE) {
        setAnimationEnabled(true);
        setAnimationSide(TO_LEFT);
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

      glutPostRedisplay();
      break;

    /* Sai do jogo. */
    case 'q':
      glutExit();
      exit(0);
      break;

    case 13:
      if (finished && !mustShowRanking)
        mustShowRanking = true;
        glutPostRedisplay();
      break;

    default:
      printf("Tecla invalida\n");
      break;
  }

  if (!finished)
    glutPostRedisplay();
}
