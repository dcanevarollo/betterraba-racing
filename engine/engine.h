#ifndef ENGINE_H
#define ENGINE_H


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <GL/freeglut.h>

#include "../utils/Defines/defines.h"
#include "../utils/Properties/properties.h"
#include "../scenarios/Urban/urban.h"
// #include "../scenarios/Desert/desert.h"
// #include "../scenarios/Florest/florest.h"
#include "../objects/Car/car.h"
#include "../objects/Obstacles/obstacles.h"


void runEngine(short int scenario, char userName[50]);

void keyboard(unsigned char key, int x, int y);

#endif
