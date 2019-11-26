#include "interface.h"

int points = 0;

void savePoints(char userName[100]) {
  FILE *file;
  char string[12];
  int line = 0;
  
  char name[100];
  char point[20];

  int numberOfLines = 0;

  Ranking player;
  strcpy(player.name, userName);
  player.point = points;

  file = fopen("../engine/Interface/ranking.txt", "a");
    intToString(player.point, string);
    
    fprintf(file, "%s %s\n", player.name, string);
  fclose(file);

  file = fopen("../engine/Interface/ranking.txt", "r");
  
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

/**
 * Função responsável por renderizar a pontuação do jogo.
 */
void renderBoxText() {
  char string[12];

  points++;

  intToString(points, string);

  glColor3ub(230, 230, 230);
  glBegin(GL_QUADS);         
  
      glVertex3f(20, 90, -1);
      glVertex3f(-20, 90, -1);
      glVertex3f(-20, 75, -1);
      glVertex3f(20, 75, -1);
  
      
  glEnd(); 

  renderText(7, 80, 0, string);
}

/**
 * Função responsável por renderizar um texto em tela.
 * 
 * @param x       : posição do texto em X.
 * @param y       : posição do texto em Y.
 * @param string  : array de char contendo o texto a ser renderizado.
 */
void renderText(int x, int y, int z, char *string) {
  glColor3f(0, 0, 0);
  glRasterPos3f(x, y, z);

  int stringSize = (int) strlen(string);

  for (int i = 0; i < stringSize; i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
}

void gameOver(Ranking player, Ranking rank[5], int size) {
  setPaused(true);

  char points[12], collocation[5];


  glColor3ub(230, 230, 230);
  glBegin(GL_QUADS);         
  
      glVertex3f(10, 50, 150);
      glVertex3f(-10, 50, 150);
      glVertex3f(-10, -10, 150);
      glVertex3f(10, -10, 150);
  
      
  glEnd(); 

  renderText(-2, 29, 170, "RANKING");
  renderText(-4, 28, 170, "Colocacao");
  renderText(0, 28, 170, "Nome");
  renderText(3, 28, 170, "Pontos");
  int j = 27;
  for (int i = 0; i < size - 1; i++) {
    j = j - 2;

    intToString(rank[i].collocation, collocation);
    intToString(rank[i].point, points);
    renderText(-3, j, 170, collocation);
    renderText(0, j, 170, rank[i].name);
    renderText(3, j, 170, points);
  }
}
