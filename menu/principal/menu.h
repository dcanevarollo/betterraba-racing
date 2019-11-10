#ifndef MENU_H
#define MENU_H 

#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>
#include <string.h>

#include "../utils/Color/color.h"

void imprimir(int x, int y,int z, char *string);
void makeBlock(int x, int y, int z, Color color);
void buildMenu();
int main(int argc,char **argv);
void keyboard (unsigned char key, int x, int y);

#endif