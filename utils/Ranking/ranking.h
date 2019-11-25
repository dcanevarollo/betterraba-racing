#ifndef RANKING_H
#define RANKING_H

#include <stdlib.h>

/**
 * @author Rafael Campos
 * Estrutura que auxilia no armazenamento dos valores para o ranking.
 */
typedef struct Ranking {
    int collocation;
    char name[100];
    int point;
} Ranking;

#endif
