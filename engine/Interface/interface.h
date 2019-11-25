#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#include "../Root/root.h"

void setPlayerName(char *playerName);

void gameOver();

void renderPoints();

void savePoints();

void renderText(int x, int y, char *string);

#endif
