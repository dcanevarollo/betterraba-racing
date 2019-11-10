#include "../utils/Color/color.h"


#include <stdlib.h>
#include <math.h>
#include <GL/freeglut.h>

#include "../menu/principal/menu.h"



int main(int argc,char **argv)
{
   glutInit(&argc, argv); // Initializes glut
    
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   /*Avisa a GLUT que modo de exibição deve ser usado quando a janela é criada. 
   //  Nesse caso, permite: uma única janela; cores compostas por Verm. Verde e Azul; e, */
   glutInitWindowSize(800,800);
   glutInitWindowPosition(500,200);
   glutCreateWindow("Menu do caralho");
   glutDisplayFunc(buildMenu);
  
   glutMainLoop();
   return 0;
}
