#include "florest.h"

/**
 * @author Rafael Campos
 * Arquivo que define o método para construir a pista floresta. 
 */

/*  Método para construir o cenário da floresta, chama as funções para construir a rua, 
    as partes da floresta na direita e esquerda e as funções para criar as árvores e arbustos. 
*/
void buildFlorestScenario() {
    buildStreet();
    buildFlorestFloor();

    glPushMatrix();
        glTranslatef(35, 0, 225);
        buildPineTree();
        glTranslatef(0, 0, -25);
        buildRoundBush();
        glTranslatef(0, 0, -25);
        buildRoundTree();
        glTranslatef(0, 0, -25);
        buildPineBush();
        glTranslatef(10, 0, -25);
        buildPineTree();
        glTranslatef(-10, 0, -25);
        buildRoundTree();
        glTranslatef(0, 0, -25);
        buildPineBush();
        glTranslatef(0, 0, -25);
        buildRoundBush();
        glTranslatef(0, 0, -25);
        buildPineBush();
        glTranslatef(10, 0, -25);
        buildRoundTree();
        glTranslatef(0, 0, -25);
        buildRoundBush();
        glTranslatef(-10, 0, -25);
        buildPineTree();
        glTranslatef(0, 0, -25);
        buildPineBush();
        glTranslatef(0, 0, -25);
        buildRoundBush();
        glTranslatef(0, 0, -25);
        buildPineTree();
        glTranslatef(10, 0, -25);
        buildRoundTree();

        glTranslatef(0, 0, -25);
        buildPineTree();
        glTranslatef(-10, 0, -25);
        buildRoundTree();
        glTranslatef(0, 0, -25);
        buildPineBush();
        glTranslatef(0, 0, -25);
        buildRoundBush();
        glTranslatef(10, 0, -25);
        buildPineBush();
        glTranslatef(0, 0, -25);
        buildRoundTree();
        glTranslatef(-10, 0, -25);
        buildRoundBush();
        glTranslatef(0, 0, -25);
        buildPineTree();
        glTranslatef(0, 0, -25);
        buildPineBush();
        glTranslatef(0, 0, -25);
        buildRoundBush();
        glTranslatef(10, 0, -25);
        buildPineTree();
        glTranslatef(0, 0, -25);
        buildRoundTree();
        glTranslatef(0, 0, -25);
        buildPineBush();
        glTranslatef(-10, 0, -25);
        buildRoundBush();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-35, 0, 225);
        buildPineTree();
        glTranslatef(0, 0, -25);
        buildRoundBush();
        glTranslatef(0, 0, -25);
        buildRoundTree();
        glTranslatef(0, 0, -25);
        buildPineBush();
        glTranslatef(-10, 0, -25);
        buildPineTree();
        glTranslatef(10, 0, -25);
        buildRoundTree();
        glTranslatef(0, 0, -25);
        buildPineBush();
        glTranslatef(0, 0, -25);
        buildRoundBush();
        glTranslatef(0, 0, -25);
        buildPineBush();
        glTranslatef(-10, 0, -25);
        buildRoundTree();
        glTranslatef(0, 0, -25);
        buildRoundBush();
        glTranslatef(10, 0, -25);
        buildPineTree();
        glTranslatef(0, 0, -25);
        buildPineBush();
        glTranslatef(0, 0, -25);
        buildRoundBush();
        glTranslatef(0, 0, -25);
        buildPineTree();
        glTranslatef(-10, 0, -25);
        buildRoundTree();

        glTranslatef(0, 0, -25);
        buildPineTree();
        glTranslatef(10, 0, -25);
        buildRoundTree();
        glTranslatef(0, 0, -25);
        buildPineBush();
        glTranslatef(0, 0, -25);
        buildRoundBush();
        glTranslatef(-10, 0, -25);
        buildPineBush();
        glTranslatef(0, 0, -25);
        buildRoundTree();
        glTranslatef(10, 0, -25);
        buildRoundBush();
        glTranslatef(0, 0, -25);
        buildPineTree();
        glTranslatef(0, 0, -25);
        buildPineBush();
        glTranslatef(0, 0, -25);
        buildRoundBush();
        glTranslatef(-10, 0, -25);
        buildPineTree();
        glTranslatef(0, 0, -25);
        buildRoundTree();
        glTranslatef(0, 0, -25);
        buildPineBush();
        glTranslatef(10, 0, -25);
        buildRoundBush();

    glPopMatrix();
}

/* Método para criar o chão da floresta que ficará ao redor da rua. */
void buildFlorestFloor() {
    glPushMatrix();

        Color florestFloorColor = darkGreen();
        glScalef(2, 3, 2);
        glColor3ub(florestFloorColor.red, florestFloorColor.green, florestFloorColor.blue);

         glBegin(GL_QUADS);
            glVertex3f(10, 0, -100);
            glVertex3f(10, 0, 100);
            glVertex3f(40, 0, 100);
            glVertex3f(40, 0, -100);
            glVertex3f(10, 0, -500);
            glVertex3f(10, 0, 150);
            glVertex3f(100, 0, 150);
            glVertex3f(100, 0, -500);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(-10, 0, -100);
            glVertex3f(-10, 0, 100);
            glVertex3f(-40, 0, 100);
            glVertex3f(-40, 0, -100);
            glVertex3f(-10, 0, -500);
            glVertex3f(-10, 0, 150);
            glVertex3f(-100, 0, 150);
            glVertex3f(-100, 0, -500);
        glEnd();

    glPopMatrix();
}