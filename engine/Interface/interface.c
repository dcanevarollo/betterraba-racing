#include "interface.h"


int points = 0;

char userName[50];

void setPlayerName(char *playerName) {
  strcpy(userName, playerName);
}


void savePoints() {
  FILE *file;
  char string[12];

  char numberOfLines;

  file = fopen("file.txt", "a");

  for (int c = getc(file); c != EOF; c = getc(file))
    if (c == '\n')
      numberOfLines = numberOfLines + 1;

  intToString(points, string);

  fprintf(file , "%s ; %s\n", userName, string);

  fclose(file);
}

/**
 * Função responsável por renderizar a pontuação do jogo.
 */
void renderPoints() {
  char string[12];

  points++;

  intToString(points, string);

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