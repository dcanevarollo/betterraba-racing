#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>

#include "../../utils/Conversions/conversions.h"
#include "../../utils/Ranking/ranking.h"

#include "../Root/root.h"


void gameOver(char const *playerName, bool perspective);

void showRanking();

void renderPoints(bool perspective, bool paused);

void renderTextBox(float x1, float y1, float x2, float y2, float z);

void renderText(float x, float y, float z, char *string, Color color, short int size);


#endif
