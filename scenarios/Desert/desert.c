#include "desert.h"

/**
 * Arquivo que define o método para construir a pista Deserto. 
 */

/*  Método para construir o cenário do deserto, chama as funções para construir a rua, 
    as partes de areia na direita e esquerda e as funções para criar os cactos e fenos. 
*/
void buildDesertScenario() {
    buildStreet();
    buildDesertFloor();

    glPushMatrix();
        glTranslatef(25, 0, -100);
        buildCactus();
        glTranslatef(50, 0, -100);
        buildSandDune();
        glTranslatef(-50, 2, -100);
        buildDesertHay();
        glTranslatef(0, -2, -100);
        buildCactus();
        glTranslatef(50, 0, -100);
        buildSandDune();
        glTranslatef(-50, 0, -100);
        buildCactus();
        glTranslatef(50, 0, -100);
        buildSandDune();
        glTranslatef(-50, 2, -100);
        buildDesertHay();
        glTranslatef(0, -2, -100);
        buildCactus();
        glTranslatef(50, 0, -100);
        buildSandDune();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-25, 0, -100);
        buildCactus();
        glTranslatef(-50, 0, -100);
        buildSandDune();
        glTranslatef(50, 2, -100);
        buildDesertHay();
        glTranslatef(0, -2, -100);
        buildCactus();
        glTranslatef(-50, 0, -100);
        buildSandDune();
        glTranslatef(50, 0, -100);
        buildCactus();
        glTranslatef(-50, 0, -100);
        buildSandDune();
        glTranslatef(50, 2, -100);
        buildDesertHay();
        glTranslatef(0, -2, -100);
        buildCactus();
        glTranslatef(-50, 0, -100);
        buildSandDune();

    glPopMatrix();
}

/* Método para criar o chão de areia que ficará ao redor da rua. */
void buildDesertFloor() {
    glPushMatrix();

        Color desertFloorColor = sand();
        glScalef(2, 3, 2);
        glColor3ub(desertFloorColor.red, desertFloorColor.green, desertFloorColor.blue);

        glBegin(GL_QUADS);
            glVertex3f(10, 0, -500);
            glVertex3f(10, 0, 150);
            glVertex3f(100, 0, 150);
            glVertex3f(100, 0, -500);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(-10, 0, -500);
            glVertex3f(-10, 0, 150);
            glVertex3f(-100, 0, 150);
            glVertex3f(-100, 0, -500);
        glEnd();

    glPopMatrix();
}