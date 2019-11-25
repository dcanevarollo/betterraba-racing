#ifndef ANIMATION_H
#define ANIMATION_H


#include <stdlib.h>
#include <GL/freeglut.h>

#include "../../utils/Defines/defines.h"
#include "../../utils/Properties/properties.h"

#include "../Renderization/renderization.h"


bool isAnimationEnabled();

void setAnimationEnabled(bool value);

short int getAnimationSide();

void setAnimationSide(short int value);

short int getCurrentLane();

void setCurrentLane(short int value);

void changeLanes(int side);


#endif
