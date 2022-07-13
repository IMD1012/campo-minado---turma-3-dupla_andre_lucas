#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define LINHAS 10
#define COLUNAS 20
// #define QTD_BOMBAS 40

typedef struct Celulas_t
{
    bool temBomba;   // pode ser true ou false
    bool estaAberta; // pode ser true ou false
    int vizinhos;    // vai de 0 a 8

} Celulas;

// Variavel Global da Matriz referente ao campo
Celulas campoMinado[LINHAS][COLUNAS];
int l, c; // l->linhas e c->colunas
const int QTD_BOMBAS = 40;

// função para inicair o campo
void inicioJogo()
{
    for (l = 0; l < LINHAS; l++)
    {
        for (c = 0; c < COLUNAS; c++)
        {
            campoMinado[l][c].estaAberta = false; // inicia com nenhuma celula aberta
            campoMinado[l][c].temBomba = false;   // qualquer celula que o usario escolha nao vai ter bomba;
            campoMinado[l][c].vizinhos = 0;       // possui zero vizinhos com bomba, pois ainda nao tem nenhuma posição aberta
        }
    }
}

// sortear bombas no campo
void addBombas(int QTD_BOMBAS, Celulas campoMinado[LINHAS][COLUNAS])
{
    srand(time(NULL));
    for (int i = 1; i <= QTD_BOMBAS; i++)
    {
        l = rand() % LINHAS;
        c = rand() % COLUNAS;
        if (campoMinado[l][c].temBomba == false) // checa se não tem bomba, caso nao tenha add uma bomba na coordenada
        {
            campoMinado[l][c].temBomba = true; // add bomba na coordenada
        }
        else
        {
            i--; // caso ja tenha bombana corrdenada, decrementa a contagem para que nao fiqeu com menos bomba do que deveria
        }
    }
}

int main(int argc, char const *argv[])
{
    inicioJogo();
    addBombas(QTD_BOMBAS, campoMinado);

    return 0;
}
