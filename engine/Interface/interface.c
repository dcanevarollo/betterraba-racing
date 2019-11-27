/**
 * @author Rafael Campos e Douglas Brandão
 * Arquivo com as funções de interface do usuário.
 */


#include "interface.h"



char *playerName;

Ranking playerRank;
Ranking *ranking;

int points = 0;
int rankingSize;


void savePoints() {
  FILE *rankingFile;
  char stringPts[12];
  int lineCounter = 0;
  
  char name[100];
  char point[20];

  int numberOfLines = 0;

  strcpy(playerRank.name, playerName);
  playerRank.point = points;

  rankingFile = fopen("./ranking.txt", "a");
    intToString(playerRank.point, stringPts);
    
    fprintf(rankingFile, "%s %s\n", playerRank.name, stringPts);
  fclose(rankingFile);

  rankingFile = fopen("./ranking.txt", "r");
  
  while (!feof(rankingFile)) {
    fscanf(rankingFile, "%s %s", name, point);
    lineCounter++;
  }

  rewind(rankingFile);
  
  rankingSize = lineCounter - 1;
  ranking = (Ranking *) malloc(rankingSize * sizeof(Ranking));
  
  int i = 0;
  while (!feof(rankingFile)) {
    fscanf(rankingFile, "%s %d", ranking[i].name, &ranking[i].point);
    i++;
  }

  fclose(rankingFile);

  int k, j; 
  Ranking tempRank;
  for (k = 0; k < rankingSize; k++)
    for (j = 0; j < rankingSize - k; j++)
      if (ranking[j].point < ranking[j + 1].point) {
          tempRank.point = ranking[j].point;
          strcpy(tempRank.name, ranking[j].name);

          ranking[j].point = ranking[j + 1].point;
          strcpy(ranking[j].name, ranking[j + 1].name);

          ranking[j + 1].point = tempRank.point;
          strcpy(ranking[j + 1].name, tempRank.name);
      }

  for (j = 0; j < rankingSize && j < 5; j++)
    ranking[j].collocation = j + 1;

  if (rankingSize > 5)
    rankingSize = 5;
}

void gameOver(const char *playerName, bool perspective) {
  savePoints();

  setPaused(true);
  setFinished(true);
  
  if (perspective) {
    renderTextBox(20, 50, -20, 30, -1);

    renderText(-9.5, 40, 0, "GAME OVER", text(), LARGE);
    renderText(-11, 35, 0, "Pressione a tecla ENTER", text(), REGULAR);
  } else {
    renderTextBox(-10, 10, 10, 4, -40);

    renderText(-4, 11, -20, "GAME OVER", text(), LARGE);
    renderText(-6, 9.5, -20, "Pressione a tecla ENTER", text(), REGULAR);
  }
}

void showRanking() {
  /* Define a cor de fundo (fundo escuro). */
  glClearColor(32.0f/255.0f, 32.0f/255.0f,  32.0/255.0f, 1.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, 1, 1, 70);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(0, 0, 40, 0, 0, 0, 0, 1, 0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  char points[12], collocation[5];

  renderText(-0.5, 11, 0, "TOP 5", text(), LARGE);
  renderText(-4, 9, 0, "COLOCACAO", text(), REGULAR);
  renderText(0, 9, 0, "NOME", text(), REGULAR);
  renderText(3, 9, 0, "PONTOS", text(), REGULAR);
  
  int i;
  int j = 8;
  for (i = 0; i < rankingSize; i++, j -= 2) {
    intToString(ranking[i].collocation, collocation);
    intToString(ranking[i].point, points);

    renderText(-3, j, 0, collocation, text(), REGULAR);
    renderText(0, j, 0, ranking[i].name, text(), REGULAR);
    renderText(3, j, 0, points, text(), REGULAR);
  }

  j -= 2;
  renderText(-1, j, 0, "JOGADOR", text(), LARGE);
  renderText(-2, j - 2, 0, "NOME", text(), REGULAR);
  renderText(2, j - 2, 0, "PONTOS", text(), REGULAR);

  intToString(playerRank.point, points);

  renderText(-2, j - 3, 0, playerRank.name, text(), REGULAR);
  renderText(2, j - 3, 0, points, text(), REGULAR);
}

void renderPoints(bool perspective, bool paused) {
  char stringPts[12];

  if (!paused)
    points++;

  intToString(points, stringPts);

  /* Se for perpectiva, mantém os valores que estávamos usando antes. */
  if (perspective) {
    renderText(-15, 80, 0, "PONTOS: ", text(), LARGE);
    renderText(7, 80, 0, stringPts, text(), LARGE);

    renderTextBox(20, 90, -20, 75, -1);
  } else {
    renderText(25, 20, -10, "PONTOS: ", text(), LARGE);
    renderText(32, 20, -10, stringPts, text(), LARGE);

    renderTextBox(37, 20, 23, 14, -30);
  }
}

/**
 * Função responsável por renderizar uma caixa de textos.
 */
void renderTextBox(float x1, float y1, float x2, float y2, float z) {
  Color quadColor = darkGrey();
  glColor3ub(quadColor.red, quadColor.green, quadColor.blue);

  glBegin(GL_QUADS);         

    glVertex3f(x1, y1, z);
    glVertex3f(x2, y1, z);
    glVertex3f(x2, y2, z);
    glVertex3f(x1, y2, z);
      
  glEnd(); 
}

/**
 * Função responsável por renderizar um texto em tela.
 * 
 * @param x       : posição do texto em X.
 * @param y       : posição do texto em Y.
 * @param z       : posição do texto em Z.
 * @param string  : array de char contendo o texto a ser renderizado.
 * @param color   : cor do texto.
 * @param size    : tamanho do texto.
 */
void renderText(float x, float y, float z, char *string, Color color, short int size) {
  glColor3f(color.red, color.green, color.blue);
  glRasterPos3f(x, y, z);

  int stringSize = (int) strlen(string);

  for (int i = 0; i < stringSize; i++) {
    if (size == LARGE)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    else if (size == REGULAR)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
  }
}
