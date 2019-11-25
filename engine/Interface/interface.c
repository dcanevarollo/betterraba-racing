#include "interface.h"


int points = 0;

char userName[50];

void setPlayerName(char *playerName) {
  strcpy(userName, playerName);
}

void savePoints() {
  FILE *file;
  char string[12];
  int line = 0;
  
  char name[100];
  char point[20];

  int numberOfLines = 0;


  file = fopen("../engine/Interface/ranking.txt", "a");
    conversion(points, string);
    
    fprintf(file, "%s %s", userName, string);
  fclose(file);

  file = fopen("../engine/Interface/ranking.txt", "r");
  
  while (!feof(file)) {
      fscanf(file, "%s %s", name, point);
      line++;
  }

  rewind(file);
  
  Ranking rank[line - 1];
  int i = 0;
  while (!feof(file)) {
      fscanf(file, "%s %d", rank[i].name, &rank[i].point);
      i++;
  }

  fclose(file);

  int k, j; 
  Ranking aux;

  for (k = 0; k < line - 1; k++) {
    for (j = 0; j < line - k - 1; j++) {
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

  rewind(file);
  file = fopen("../engine/Interface/ranking.txt", "w");

  for (j = 0; j < line - 1; j++) {
    rank[j].collocation = j + 1;
    
    conversion(rank[j].point, string);

    fprintf(file, "%d %s %s\n", rank[j].collocation, rank[j].name, string);

  }

  fclose(file);


}

/**
 * Função responsável por renderizar a pontuação do jogo.
 */
void renderPoints() {
  char string[12];

  points++;

  conversion(points, string);

  renderText(3, 80, string);
}

/**
 * Função responsável por renderizar um texto em tela.
 * 
 * @param x       : posição do texto em X.
 * @param y       : posição do texto em Y.
 * @param string  : array de char contendo o texto a ser renderizado.
 */
void renderText(int x, int y, char *string) {
  glColor3f(1, 1, 1);
  glRasterPos2f(x, y);

  int stringSize = (int) strlen(string);

  for (int i = 0; i < stringSize; i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
}

void gameOver() {
  setPaused();
  renderText(-20, 130, "SE FODEU");
}