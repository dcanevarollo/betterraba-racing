#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>

#include "../engine.h"
#include "../../utils/Conversions/conversions.h"
#include "../../utils/Ranking/ranking.h"

void setPlayerName(char *playerName);

void gameOver();

void renderPoints();

void savePoints();

void renderText(int x, int y, char *string);

#endif
