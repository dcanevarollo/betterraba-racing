/**
 * @author Douglas Canevarollo
 * Motor gráfico do jogo.
 */

#include "root.h"


#define VIEW_DISTANCE 500  // Distância de visualização da câmera.


/* Protótipos de funções encapsuladas. */
void configView();


bool paused = true;  // Utilizada para pausar o jogo.

/* Variáveis de controle da câmera e perspectiva. */
bool perspective = true;

int camPosX = 0, camPosY = 20, camPosZ = 200;
int camLookX = 0, camLookY = 10, camLookZ = 0;
int camAxisX = 0, camAxisY = 1, camAxisZ = 0;


void setPaused(bool value) {
  paused = value;
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
void runEngine(short int scenario, char username) {
  configView();

  /* Definição das propriedades do carro (apenas na primeira renderização). */
  if (isFirstRender()) {
    defineCarProperties();
    renderObstacles();

    setFirstRender(false);
  }
  

  // setPlayerName(username);

  /* Cenários e objetos a serem construídos. */
  toInfiniteAndBeyond(scenario);

  /* Renderiza o contador de pontos. */
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
