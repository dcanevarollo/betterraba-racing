/**
 * @author Douglão the legend,  Andrey the machine.
*/ 
#include "menu.h"

#include "../objects/Car/car.h"

void imprimir(int x, int y,int z, char *string){
    glColor3f(1, 1, 1);          //era pra controlar a cor mas nao consigo fzer funcionar
    glRasterPos2f(x,y);
    
    int len = (int) strlen(string);         //Pega o tamanho da string
    
    //loop to display character by character
    for (int i = 0; i <len; i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
    }
}

void makeBlock(int x, int y, int z, Color color){
    glPushMatrix();                     // pra não cagar td depois
    glTranslatef(x, y, z);              //translada a base
    glScalef(3,1,1);                    // deformação no sistema de coordenadas
    glColor3ub(color.red, color.green, color.blue );
    glutSolidCylinder(20,20,20,20);
    glPopMatrix();                      // volta ao normal o sistema de coordenadas
}

void buildMenu(){   
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();   
    gluOrtho2D(-400,400,-400,400);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    
    imprimir(-80, 200, 0, "BetterRaba Racing");
    
    makeBlock(0, 100, 0, red());
    imprimir(-20,90,0,"Start");
    
    makeBlock(0,0,0, green());  
    imprimir(-40,-10, 0,"Options");

         
    glutSwapBuffers(); 
}


