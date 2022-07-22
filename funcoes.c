#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "estruturas.h"
#include "constantes.h"
#include "funcoes.h"

// função para iniciarcampo
void inicioJogo()
{
    for (int l = 0; l < LINHAS; l++)
    {
        for (int c = 0; c < COLUNAS; c++)
        {
            campoMinado[l][c].estaAberta = false; // inicia com nenhuma celula aberta
            campoMinado[l][c].temBomba = false;   // qualquer celula que o usario escolha nao vai ter bomba;
            campoMinado[l][c].vizinhos = 0;       // possui zero vizinhos com bomba, pois ainda nao tem nenhuma posição aberta
        }
    }
}
void troca(int *x , int a){
  a = *x;
}
// sortear bombas no campo
void addBombas(int QTD_BOMBAS, Celulas campoMinado[LINHAS][COLUNAS])
{
    //campoMinado = malloc(sizeof(Celulas));
  
    srand(time(NULL));
    for (int i = 1; i <= QTD_BOMBAS; i++)
    {
        int l = rand() % LINHAS;
        int c = rand() % COLUNAS;
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

// função que verifica coordenadas validas
bool coordValid(int l, int c)
{
    if (l >= 0 && l < LINHAS && c >= 0 && c < COLUNAS)
        return true;
    else
        return false;
}

int quantBombasVizinhas(int x, int y)
{
    int quantidade = 0;

    if (coordValid(x - 1, y) && campoMinado[x - 1][y].temBomba)
    {
        quantidade++;
    }
    if (coordValid(x + 1, y) && campoMinado[x + 1][y].temBomba)
    {
        quantidade++;
    }
    if (coordValid(x, y + 1) && campoMinado[x][y + 1].temBomba)
    {
        quantidade++;
    }
    if (coordValid(x, y - 1) && campoMinado[x][y - 1].temBomba)
    {
        quantidade++;
    }
    if (coordValid(x - 1, y - 1) && campoMinado[x - 1][y - 1].temBomba) // DSE
    {
        quantidade++;
    }
    if (coordValid(x + 1, y - 1) && campoMinado[x + 1][y - 1].temBomba) // DIE
    {
        quantidade++;
    }
    if (coordValid(x - 1, y + 1) && campoMinado[x - 1][y + 1].temBomba) // DSD
    {
        quantidade++;
    }
    if (coordValid(x + 1, y + 1) && campoMinado[x + 1][y + 1].temBomba) // DID
    {
        quantidade++;
    }

    return quantidade;
}

void contarBombas()
{
    for (int l = 0; l < LINHAS; l++)
    {
        for (int c = 0; c < COLUNAS; c++)
        {
            campoMinado[l][c].vizinhos = quantBombasVizinhas(l, c);
        }
    }
}

void campoVisualPrint()
{

    printf("\n\n ");
    for (int l = 0; l < COLUNAS; l++)
        printf("%4d", l); // índices das colunas
    printf("\n  ---------------------------------------------------------------------------------\n");
    for (int l = 0; l < LINHAS; l++)
    {
        printf("%d |", l); // índices das linhas
        for (int c = 0; c < COLUNAS; c++)
        {
            if (campoMinado[l][c].estaAberta)
            {
                if (campoMinado[l][c].temBomba)
                {
                    printf(" * ");
                }
                else
                {
                    if (campoMinado[l][c].vizinhos == 0)
                    {
                        printf(" : ");
                    }
                    else
                    {
                        printf(" %d ", campoMinado[l][c].vizinhos);
                    }
                }
            }
            else
            {
                printf("   ");
            }

            printf("|");
        }

        printf("\n  ---------------------------------------------------------------------------------\n");
    }
}

void revelar(int x, int y)
{
  
    
    if (coordValid(x, y) == true && campoMinado[x][y].estaAberta == false)
    {
        campoMinado[x][y].estaAberta = true;
        if (campoMinado[x][y].vizinhos == 0)
        {
            revelar(x - 1, y - 1);
            revelar(x - 1, y);
            revelar(x - 1, y + 1);
            revelar(x, y - 1);
            revelar(x, y + 1);
            revelar(x + 1, y - 1);
            revelar(x + 1, y);
            revelar(x + 1, y + 1);
        }
    }
}

int resultado()
{
    int cont = 0;
    for (int l = 0; l < LINHAS; l++)
    {
        for (int c = 0; c < COLUNAS; c++)
        {
            if (campoMinado[l][c].estaAberta == false && campoMinado[l][c].temBomba == false)
            {
                cont++;
            }
        }
    }
    return cont;
}

void interacao(int *x, int *y)
{
    time_t begin = time(NULL);
    int decisao, limite = 0, libera = 0;
    
    do
    {
        campoVisualPrint();
        printf("Digite 1 para se deseja revelar alguma celula\n");
        printf("Digite 2 para pedir ajuda ao jogo\n");
        printf("Digite 3 para saber quanto tempo ja se passou ate agora\n");
        printf("Digite o numero desejado: ");
        scanf("%d", &decisao);

        if (limite == 0)
        {
            if (decisao == 1)
            {
                printf("\nDigite a coordenada da celula que deseja revelar: ");
                scanf("%d %d", *&x, *&y);

                revelar(*x, *y);
            }
            else if (decisao == 2)
            {
                // regra das quina, 3 casas seguidas
                do
                {
                    *x = rand() % LINHAS;
                    *y = rand() % COLUNAS;
                } while (campoMinado[*x][*y].estaAberta == true || campoMinado[*x - 1][*y - 1].estaAberta == true && campoMinado[*x - 1][*y].estaAberta == true && campoMinado[*x - 1][*y + 1].estaAberta == true && campoMinado[*x][*y - 1].estaAberta == true && campoMinado[*x][*y + 1].estaAberta == true && campoMinado[*x + 1][*y - 1].estaAberta == true && campoMinado[*x + 1][*y].estaAberta == true && campoMinado[*x + 1][*y + 1].estaAberta == true || campoMinado[*x][*y].temBomba == true || campoMinado[*x][*y].vizinhos > 0);
                revelar(*x,*y);
                limite++;
            }
            else if (decisao == 3)
            {
                time_t endParcial = time(NULL);
                printf("\n\nO tempo gasto ate agora foi %ld segundos", (endParcial - begin));
            }
        }
        else
        {
            if (decisao == 1)
            {
                printf("\nDigite a coordenada da celula que deseja revelar: ");
                scanf("%d %d", x, y);

                revelar(*x, *y);
            }
            else if (decisao == 2)
            {

                printf("\nEssa função ja foi usada");
            }
            else if (decisao == 3)
            {
                time_t endParcial = time(NULL);
                printf("\n\nO tempo gasto ate agora foi %ld segundos", (endParcial - begin));
            }
        }

    } while (resultado() != 0 && campoMinado[*x][*y].temBomba == false);
    if (campoMinado[*x][*y].temBomba == true)
    {
        time_t end = time(NULL);
        campoVisualPrint();
        printf("\nVOCE PERDEU! \n");
        printf("Voce gastou %ld segundos no campo minado \n", (end - begin));
        
    }
    else
    {
        time_t end = time(NULL);
        campoVisualPrint();
        printf("VOCE GANHOU! \n");
        printf("Voce gastou %ld segundos no campo minado \n", (end - begin));
    }
}
