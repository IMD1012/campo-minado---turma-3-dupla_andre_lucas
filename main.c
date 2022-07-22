#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "estruturas.h"
#include "constantes.h"
#include "funcoes.h"

int main()
{
    int x, y;

    inicioJogo();
    addBombas(QTD_BOMBAS, campoMinado);
    contarBombas();
    printf("\n\n\t\t\tCampo Minado");
    interacao(&x, &y);
    

    return 0;
}
