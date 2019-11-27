#include "car.h"

/**
 * Função de criação dos objetos que modelam os carros.
 * 
 * @param color   : cor do carro a ser criado.
 * @param posX    : posição (eixo x) em que o carro será desenhado.
 * @param posZ    : posição (eixo Z) em que o carro será desenhado.
 */
void buildCar(Color color, float posX, float posZ) {
   glTranslatef(posX, 1, -posZ);  // Posiciona o carro na faixa central.
   glRotatef(90, 0, 1, 0);  // Coloca o carro virado para frente.

   glPushMatrix();

   Color lightColor = darkRed();

   // Rodas
   Color wheelColor = black();

   glColor3ub(wheelColor.red, wheelColor.green, wheelColor.blue);
   glTranslatef(2, 0, 2);
   glScalef(1, 1, 1);
   glutSolidSphere(1, 50, 50);

   glTranslatef(-5, 0, 0);
   glScalef(1, 1, 1);
   glutSolidSphere(1, 50, 50);

   glTranslatef(0, 0, -4);
   glScalef(1, 1, 1);
   glutSolidSphere(1, 50, 50);

   glTranslatef(5, 0, 0);
   glScalef(1, 1, 1);
   glutSolidSphere(1, 50, 50);
   
   // Chassi
   glTranslatef(-2, 2, 2);
   glScalef(10, 3, 6);
   glColor3ub(color.red, color.green, color.blue);
   glutSolidCube(1);

   // Teto
   glTranslatef(-0.15, 0.8, 0);
   glScalef(0.8, 1.5, 2);
   glColor3ub(color.red, color.green, color.blue);
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

   glPopMatrix();

   glPushMatrix();
      glTranslatef(-4.8, 2, 2.3);
      glColor3ub(lightColor.red, lightColor.green, lightColor.blue);
      glScalef(1, 1, 1);
      glutSolidSphere(0.5, 50, 50);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-4.8, 2, -2.3);
      glColor3ub(lightColor.red, lightColor.green, lightColor.blue);
      glScalef(1, 1, 1);
      glutSolidSphere(0.5, 50, 50);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-3.6, 4, 0);
      glScalef(0, 3.5, 7);
      glColor3ub(20, 20, 20);
      glutSolidCube(0.8);
   glPopMatrix();
}
