#ifndef DEFINES_H
#define DEFINES_H


#ifdef WIN32
    #define CLEAR_SCREEN system("cls")
    #define CLEAR_BUFFER fflush(stdin)
#else
    #define CLEAR_SCREEN system("clear")
    #define CLEAR_BUFFER __fpurge(stdin)

    #include <stdio_ext.h>
#endif


#define bool char
#define true 1
#define false 0

#define MIDDLE_LANE 0  // Posição em x da faixa central.
#define RIGHT_LANE 12  // Posição em x da faixa da direita.
#define LEFT_LANE -12  // Posição em x da faixa da esquerda.

#define TO_LEFT -1  // Define a troca de faixa para a esquerda.
#define TO_RIGHT 1  // Define a troca de faixa para a direita.

#define INIT_POS -150  // Posição inicial do carro. Negativa pois a função de translação para os carros inverte o sinal.

#define LARGE 18  // Tamanho de fonte grande.
#define REGULAR 12  // Tamanho de fonte normal.


#endif
