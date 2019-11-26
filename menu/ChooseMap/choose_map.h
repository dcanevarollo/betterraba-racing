#ifndef CHOOSE_MAP_H
#define CHOOSE_MAP_H


#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#include "../../utils/Defines/defines.h"
#include "../../utils/Color/color.h"

#include "../../scenarios/Urban/urban.h"
#include "../../scenarios/Desert/desert.h"
#include "../../scenarios/Florest/florest.h"

#include "../../engine/Interface/interface.h"


short int getCurrentMap();

void setCurrentMap(short int value);

void renderScenario(short int scenario, float renderizationPos);

void runMapMenu();


#endif
