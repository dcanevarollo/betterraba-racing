#ifndef ROOT_H
#define ROOT_H


#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#include "../../utils/Defines/defines.h"
#include "../../utils/Properties/properties.h"
#include "../../utils/Conversions/conversions.h"

#include "../../scenarios/Urban/urban.h"
#include "../../scenarios/Desert/desert.h"
#include "../../scenarios/Florest/florest.h"

#include "../../objects/Car/car.h"
#include "../../objects/Obstacles/obstacles.h"

#include "../Interface/interface.h"
#include "../Animation/animation.h"
#include "../Renderization/renderization.h"
#include "../Collision/collision.h"


void setPaused(bool value);

void runEngine(short int scenario, char username);

void keyboard(unsigned char key, int x, int y);


#endif
