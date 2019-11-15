#ifndef ENGINE_H
#define ENGINE_H


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <GL/freeglut.h>

#include "../utils/Queue/queue.h"
#include "../utils/Boundary/boundary.h"
#include "../scenarios/Urban/urban.h"
#include "../objects/Car/car.h"
#include "../objects/Obstacles/obstacles.h"


void obstaclesGraphicEngine();

void carGraphicEngine();

void changeLanes();

void createCarBoundary();

void createObstacleBoundary();

void keyboard(unsigned char key, int x, int y);

void runEngine(short int scenario);

#endif
