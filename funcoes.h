#ifndef FUNCS_H_
#define FUNCS_H_
#include "estruturas.h"

void inicioJogo();
void addBombas(int QTD_BOMBAS,  Celulas campoMinado[10][20]);
bool coordValid(int l, int c);
int quantBombasVizinhas(int x, int y);
void contarBombas();
void campoVisualPrint();
void revelar(int x, int y);
int resultado();
void interacao(int *x, int *y);
void troca(int *x , int a);

#endif
