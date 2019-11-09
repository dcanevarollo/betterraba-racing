#include "desert_scenario.h"

/**
 * @author Rafael Campos
 * Arquivo que define o método para construir a pista Deserto. 
 */

void buildDesertScenario() {
    buildStreet();
    buildDesertFloor();

    glPushMatrix();
        glTranslatef(25, 0, 5);
        buildCactus();
        glTranslatef(0, 2, -25);
        buildDesertHay();
        glTranslatef(0, 0, -25);
        buildCactus();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-25, 2, 5);
        buildDesertHay();
        glTranslatef(0, 0, -25);
        buildCactus();
        glTranslatef(0, 2, -25);
        buildDesertHay();

    glPopMatrix();
}

void buildDesertFloor() {
    glPushMatrix();

        Color desertFloorColor = sand();
        glScalef(2, 3, 2);
        glColor3ub(desertFloorColor.red, desertFloorColor.green, desertFloorColor.blue);

        glBegin(GL_QUADS);
            glVertex3f(10, 0, -100);
            glVertex3f(10, 0, 100);
            glVertex3f(40, 0, 100);
            glVertex3f(40, 0, -100);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(-10, 0, -100);
            glVertex3f(-10, 0, 100);
            glVertex3f(-40, 0, 100);
            glVertex3f(-40, 0, -100);
        glEnd();

    glPopMatrix();
}