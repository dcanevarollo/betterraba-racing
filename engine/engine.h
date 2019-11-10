#ifndef ENGINE_H
#define ENGINE_H


#include <stdlib.h>
#include <GL/freeglut.h>

#include "../objects/Car/car.h"
#include "../objects/Obstacles/obstacles.h"


void obstaclesGraphicEngine();

void carGraphicEngine();

void changeLanes();

void keyboard(unsigned char key, int x, int y);

#endif
