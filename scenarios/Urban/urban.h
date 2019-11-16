#ifndef URBAN_H
#define URBAN_H

#define bool char
#define true 1
#define false 0

#include <stdlib.h>
#include <GL/freeglut.h>

#include "../../utils/Defines/defines.h"
#include "../../utils/Color/color.h"
#include "../../objects/Car/car.h"
#include "../../objects/Street/street.h"
#include "../../objects/Building/building.h"
#include "../../objects/Obstacles/obstacles.h"

void buildUrbanScenario();

#endif
