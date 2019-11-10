#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <stdlib.h>
#include "../../utils/Color/color.h"
#include "../Car/car.h"

void buildBox(float posX, float posZ);

void buildTrafficCone(float posX, float posZ);

void buildStone(float posX, float posZ);

void buildRandomCar(float posX, float posZ);

#endif
