#ifndef CHOOSE_CAR_H
#define CHOOSE_CAR_H


#include <stdlib.h>
#include <GL/freeglut.h>

#include "../../utils/Defines/defines.h"
#include "../../utils/Color/color.h"

#include "../../objects/Car/car.h"

#include "../../engine/Interface/interface.h"


short int getCurrentColor();

void setCurrentColor(short int value);

void buildMainCar(short int color, float posX, float posZ);

void runCarMenu();


#endif
