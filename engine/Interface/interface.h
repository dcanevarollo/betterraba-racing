#ifndef PUNCTUATION_H
#define PUNCTUATION_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#include "../engine.h"

void setPlayerName(char *playerName);

void gameOver();

void renderPoints();

void savePoints();

void renderText(int x, int y, char *string);

#endif
