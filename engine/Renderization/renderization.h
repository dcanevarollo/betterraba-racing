#ifndef RENDERIZATION_H
#define RENDERIZATION_H


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <GL/freeglut.h>

#include "../../utils/Defines/defines.h"
#include "../../utils/Properties/properties.h"

#include "../../scenarios/Urban/urban.h"
#include "../../scenarios/Desert/desert.h"
#include "../../scenarios/Florest/florest.h"

#include "../Animation/animation.h"
#include "../Collision/collision.h"


Properties getCarProperties();

void setCarProperties(Properties value);

Properties *getObstaclesProperties();

void setObstaclesProperties(Properties *value);

int getObstaclesRendPosition();

bool isFirstRender();

void setFirstRender(bool value);

void defineCarProperties();

void defineObstaclesProperties();

void renderMainCar();

void renderScenario(short int scenario, float renderizationPos);

void renderObstacles();

void toInfiniteAndBeyond(short int scenario);


#endif
