#include "car.h"

/**
 * @author Rafael Campos
 * Função de criação dos objetos que modelam os carros.
 * 
 * @param carColor   : cor do carro a ser criado. 
 */
void buildCar(Color carColor) {
   // Rodas
   glTranslatef(2, 0, 2);
   glScalef(1, 1, 1);
   glColor3ub(0, 255, 0);
   glutSolidSphere(1, 50, 50);

   glTranslatef(-5, 0, 0);
   glScalef(1, 1, 1);
   glColor3ub(0, 255, 0);
   glutSolidSphere(1, 50, 50);

   glTranslatef(0, 0, -4);
   glScalef(1, 1, 1);
   glColor3ub(0, 255, 0);
   glutSolidSphere(1, 50, 50);

   glTranslatef(5, 0, 0);
   glScalef(1, 1, 1);
   glColor3ub(0, 255, 0);
   glutSolidSphere(1, 50, 50);
   
   // Chassi
   glTranslatef(-2, 2, 2);
   glScalef(10, 3, 6);
   glColor3ub(carColor.red, carColor.green, carColor.blue);
   glutSolidCube(1);

   // Teto
   glTranslatef(-0.15, 0.8, 0);
   glScalef(0.8, 1.5, 2);
   glColor3ub(carColor.red, carColor.green, carColor.blue);
   glutSolidCube(0.5);
   
   // Vidro da frente
   glTranslatef(0.21, 0, 0);
   glScalef(2, 3.5, 4.9);
   glRotatef(45, 0, 0, 1);
   glColor3ub(20, 20, 20);
   glutSolidCube(0.1);
   glTranslatef(0, -0.1, 0);
   glScalef(1, 1, 1);
   glColor3ub(20, 20, 20);
   glutSolidCube(0.1);
}
