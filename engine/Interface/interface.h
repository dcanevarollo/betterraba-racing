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

void renderBoxText();

void savePoints();

void renderText(int x, int y, int z, char *string);

#endif
