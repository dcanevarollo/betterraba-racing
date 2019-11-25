#ifndef DEFINES_H
#define DEFINES_H


#define bool char
#define true 1
#define false 0

#define URBAN 0  // Define o cenário urbano.
#define DESERT 1  // Define o cenário desértico.
#define FLOREST 2  // Define o cenário florestal.

#define MIDDLE_LANE 0  // Posição em x da faixa central.
#define RIGHT_LANE 12  // Posição em x da faixa da direita.
#define LEFT_LANE -12  // Posição em x da faixa da esquerda.

#define TO_LEFT -1  // Define a troca de faixa para a esquerda.
#define TO_RIGHT 1  // Define a troca de faixa para a direita.

#define INIT_POS -150  // Posição inicial do carro. Negativa pois a função de translação para os carros inverte o sinal.


#endif
