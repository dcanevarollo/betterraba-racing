#include "trees.h"

/**
 * Arquivo que define os métodos para construir árvores, arbustos, cacto e feno do deserto. 
 */


/** 
*   Método que constrói genericamente os troncos das árvores.
*/
void buildTrunk() {
    Color trunkColor = brown();
    glPushMatrix();
    
        glScalef(2, 3, 2);
        glColor3ub(trunkColor.red, trunkColor.green, trunkColor.blue);
        GLUquadricObj *quadratic;
        quadratic = gluNewQuadric();
        glRotatef(-90, 1, 0, 0);
        gluCylinder(quadratic, 0.5, 0.5, 3, 30, 30);

    glPopMatrix();

}

/** 
*   Método que constrói um pinheiro.
*/
void buildPineTree() {
    Color canopyColor = green();
   
    // Chama a função que cria o tronco
    buildTrunk();   

    glPushMatrix();

        glTranslatef(0, 12, 0);    
        glScalef(2, 6, 2);
        glColor3ub(canopyColor.red, canopyColor.green, canopyColor.blue);

        // Monta a pirâmide que é a copa do pinheiro.
        glBegin(GL_TRIANGLES);         
        
            glVertex3f( 0.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, 1.0f);
        
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);
        
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
        
            glVertex3f( 0.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f,-1.0f,-1.0f);
            glVertex3f(-1.0f,-1.0f, 1.0f);
            
        glEnd(); 
    
    glPopMatrix();
}

/** 
*   Método que constrói uma árvore com copa esférica.
*/
void buildRoundTree() {
    Color canopyColor = green();

    // Chama a função que cria o tronco
    buildTrunk();
    
    glPushMatrix();

        // Monta a esfera.
        glTranslatef(-0.2, 12, 0);    
        glScalef(6, 6, 6);
        glColor3ub(canopyColor.red, canopyColor.green, canopyColor.blue);
        glutSolidSphere(0.8, 20, 20);
     
    glPopMatrix();

}

/** 
*   Método que constrói um arbusto em forma de pirâmide.
*/
void buildPineBush() {
    Color pineBushColor = green();  

    glPushMatrix();
  
        glScalef(2, 3, 2);
        glColor3ub(pineBushColor.red, pineBushColor.green, pineBushColor.blue);

        // Monta a pirâmide.
        glBegin(GL_TRIANGLES);          
        
            glVertex3f( 0.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, 1.0f);
        
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);
        
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
        
            glVertex3f( 0.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f,-1.0f,-1.0f);
            glVertex3f(-1.0f,-1.0f, 1.0f);
        
        glEnd(); 
    
    glPopMatrix();
}

/** 
*   Método que constrói um arbusto em forma de esfera.
*/
void buildRoundBush() {
    Color roundBushColor = green();

    glPushMatrix();
    
        // Monta a esfera.
        glScalef(3, 3, 3);
        glColor3ub(roundBushColor.red, roundBushColor.green, roundBushColor.blue);
        glutSolidSphere(0.8, 20, 20);
     
    glPopMatrix();
}

/** 
*   Método que constrói um cacto.
*/
void buildCactus() {
    Color cactusColor = darkGreen();

    glPushMatrix();

        // Monta o tronco central do cacto.
        glScalef(2, 3, 2);
        glColor3ub(cactusColor.red, cactusColor.green, cactusColor.blue);
        GLUquadricObj *quadratic;
        quadratic = gluNewQuadric();
        glRotatef(-90, 1, 0, 0);
        gluCylinder(quadratic, 0.5, 0.5, 3, 30, 30);

        glTranslatef(0, 0, 3);
        glutSolidSphere(0.5, 20, 20);

    glPopMatrix();

    glPushMatrix();

        // Monta o "braço" direito do cacto.
        glScalef(1, 1, 1);
        glTranslatef(0, 7, 0);
        glColor3ub(cactusColor.red, cactusColor.green, cactusColor.blue);
        glRotatef(90, 0, 1, 0);
        gluCylinder(quadratic, 0.5, 0.5, 3, 30, 30);
        
        glTranslatef(0, -0.4, 3);
        glColor3ub(cactusColor.red, cactusColor.green, cactusColor.blue);
        glRotatef(-90, 1, 0, 0);
        gluCylinder(quadratic, 0.5, 0.5, 3, 30, 30);

        glTranslatef(0, 0, 3);
        glutSolidSphere(0.5, 20, 20);

    glPopMatrix();

    glPushMatrix();

        // Monta o "braço" esquerdo do cacto.
        glScalef(1, 1, 1);
        glTranslatef(0, 5, 0);
        glColor3ub(cactusColor.red, cactusColor.green, cactusColor.blue);
        glRotatef(-90, 0, 1, 0);
        gluCylinder(quadratic, 0.5, 0.5, 3, 30, 30);
        
        glTranslatef(0, -0.4, 3);
        glColor3ub(cactusColor.red, cactusColor.green, cactusColor.blue);
        glRotatef(-90, 1, 0, 0);
        gluCylinder(quadratic, 0.5, 0.5, 3, 30, 30);

        glTranslatef(0, 0, 3);
        glutSolidSphere(0.5, 20, 20);
    
    glPopMatrix();

}

/** 
*   Método que constrói o feno para a pista no deserto.
*/
void buildDesertHay() {
    Color desertHayColor = beige();

    glPushMatrix();

        // Monta a esfera.    
        glScalef(3, 3, 3);
        glColor3ub(desertHayColor.red, desertHayColor.green, desertHayColor.blue);
        glutSolidSphere(0.8, 20, 20);
     
    glPopMatrix();
}

/** 
*   Método que constrói uma duna de areia em forma de pirâmide.
*/
void buildSandDune() {
    Color sandDuneColor = darkSand();  

    glPushMatrix();
  
        glScalef(50, 6, 50);
        glColor3ub(sandDuneColor.red, sandDuneColor.green, sandDuneColor.blue);

        // Monta a pirâmide.
        glBegin(GL_TRIANGLES);          
        
            glVertex3f( 0.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, 1.0f);
        
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);
        
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
        
            glVertex3f( 0.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f,-1.0f,-1.0f);
            glVertex3f(-1.0f,-1.0f, 1.0f);
        
        glEnd(); 
    
    glPopMatrix();
}
