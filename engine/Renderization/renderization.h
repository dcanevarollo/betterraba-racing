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

#include "../../menu/ChooseCar/choose_car.h"
#include "../../menu/ChooseMap/choose_map.h"

#include "../Animation/animation.h"
#include "../Collision/collision.h"


Properties getCarProperties();

void setCarProperties(Properties value);

Properties *getObstaclesProperties();

void setObstaclesProperties(Properties *value);

int getObstaclesRendPosition();

int getObstaclesQuantity();

bool isFirstRender();

void setFirstRender(bool value);

void defineCarProperties();

void defineObstaclesProperties();

void renderMainCar(short int carColor);

void renderObstacles();

void toInfiniteAndBeyond(short int scenario);


#endif
