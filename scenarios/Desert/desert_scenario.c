#include "desert_scenario.h"

/**
 * @author Rafael Campos
 * Arquivo que define o método para construir a pista Deserto. 
 */

/*  Método para construir o cenário do deserto, chama as funções para construir a rua, 
    as partes de areia na direita e esquerda e as funções para criar os cactos e fenos. 
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

/* Método para criar o chão de areia que ficará ao redor da rua. */
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