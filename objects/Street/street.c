#include "street.h"

/**
 * Arquivo que define os métodos para construir a rua. 
 */

void buildStreet() {
    Color streetColor = grey();
    Color lineColor = yellow();

    glPushMatrix();
    
        // Monta a rua.
        glScalef(2, 3, 2);
        glColor3ub(streetColor.red, streetColor.green, streetColor.blue);
        glBegin(GL_POLYGON);         
        
            glVertex3f(10, 0, -500);
            glVertex3f(10, 0, 150);
            glVertex3f(-10, 0, 150);
            glVertex3f(-10, 0, -500);
        
            
        glEnd();

        // Monta as 2 linhas que dividem a rua.
        glTranslatef(0, 0.1, 0);
        glColor3ub(lineColor.red, lineColor.green, lineColor.blue);
        glBegin(GL_QUADS);         
        
            glVertex3f(3.6, 0, -500);
            glVertex3f(3.8, 0, -500);
            glVertex3f(3.8, 0, 150);
            glVertex3f(3.6, 0, 150);
        
            
        glEnd(); 
        
        glBegin(GL_QUADS);         
        
            glVertex3f(-3.6, 0, -500);
            glVertex3f(-3.8, 0, -500);
            glVertex3f(-3.8, 0, 150);
            glVertex3f(-3.6, 0, 150);
        
            
        glEnd(); 

    glPopMatrix();
}