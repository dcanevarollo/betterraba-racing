#include "interface.h"

int points = 0;

void savePoints(char const *userName) {
  FILE *file;
  char string[12];
  int line = 0;

  char name[100];
  char point[20];

  int numberOfLines = 0;

  Ranking player;
  strcpy(player.name, userName);
  player.point = points;

  file = fopen("ranking.txt", "a");
    intToString(player.point, string);
    
    fprintf(file, "%s %s\n", player.name, string);
  fclose(file);

  file = fopen("ranking.txt", "r");
  
  int n;
  while (!feof(file)) {
      fscanf(file, "%s %s", name, point);
      line++;
  }
  rewind(file);
  
  int size = line - 1;
  Ranking rank[size];
  if (size >= 5) {
    Ranking rank[5];
  }

  int i = 0;
  while (!feof(file)) {
      fscanf(file, "%s %d", rank[i].name, &rank[i].point);
      i++;
  }

  fclose(file);

  int k, j; 
  Ranking aux;
  for (k = 0; k < size; k++) {
    for (j = 0; j < size - k; j++) {
      if (rank[j].point < rank[j + 1].point) {
          aux.point = rank[j].point;
          strcpy(aux.name, rank[j].name);
          rank[j].point = rank[j + 1].point;
          strcpy(rank[j].name, rank[j + 1].name);
          rank[j + 1].point = aux.point;
          strcpy(rank[j + 1].name, aux.name);
      }
    }
  }

  for (j = 0; j < size && j < 5; j++) {
    rank[j].collocation = j + 1;
  }
  gameOver(player, rank, size);

}

void gameOver(Ranking player, Ranking rank[5], int size) {
  setPaused(true);

  char points[12], collocation[5];

  renderTextBox(10, 50, -10, -10, 150);

  renderText(-2, 29, 170, "RANKING", text(), LARGE);
  renderText(-4, 28, 170, "Colocacao", text(), REGULAR);
  renderText(0, 28, 170, "Nome", text(), REGULAR);
  renderText(3, 28, 170, "Pontos", text(), REGULAR);
  
  int j = 27;
  for (int i = 0; i < size - 1; i++) {
    j = j - 2;

    intToString(rank[i].collocation, collocation);
    intToString(rank[i].point, points);

    renderText(-3, j, 170, collocation, text(), REGULAR);
    renderText(0, j, 170, rank[i].name, text(), REGULAR);
    renderText(3, j, 170, points, text(), REGULAR);
  }
}

void renderPoints() {
  renderText(-15, 80, 0, "PONTOS: ", text(), LARGE);

  char stringPts[12];

  points++;

  intToString(points, stringPts);

  renderText(7, 80, 0, stringPts, text(), LARGE);

  renderTextBox(20, 90, -20, 75, -1);
}

/**
 * Função responsável por renderizar a textos em um quadrado.
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
