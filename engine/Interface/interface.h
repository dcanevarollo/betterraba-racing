#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>

#include "../../utils/Conversions/conversions.h"
#include "../../utils/Ranking/ranking.h"
#include "../Root/root.h"

void setPlayerName(char *playerName);

void gameOver();

void savePoints();

void renderPoints();

void renderTextBox(float x1, float y1, float z, float x2, float y2);

void renderText(float x, float y, float z, char *string, Color color, short int size);

#endif
