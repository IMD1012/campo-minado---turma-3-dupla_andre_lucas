#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct Celulas_t
{
    bool temBomba;   // pode ser true ou false
    bool estaAberta; // pode ser true ou false
    int vizinhos;    // vai de 0 a 8
    char campo;
} Celulas;

// Variavel Global da Matriz referente ao campo

int l, c; // l->linhas e c->colunas
const int LINHAS = 10;
const int COLUNAS = 20;
const int QTD_BOMBAS = 40;
Celulas campoMinado[LINHAS][COLUNAS];
// função para iniciarcampo
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

void campovisualinicial(Celulas campoMinado[LINHAS][COLUNAS]){
  for(int i = 0 ; i < LINHAS ; i++){
     for(int j = 0 ; j < COLUNAS ; j++){
       campoMinado[i][j].campo = '.';
       printf("%c" , campoMinado[i][j].campo);
     } 
    printf("\n");
  }
  
}

void campovisual(Celulas campoMinado[LINHAS][COLUNAS] , int x , int y ){
  if(campoMinado[x][y].temBomba != true){
    
    campoMinado[x][y].campo = '_';
    for(int i = 0 ; i < LINHAS ; i++ ){
      for(int j = 0 ; j < COLUNAS ; j++){
        printf("%c", campoMinado[i][j].campo);
    }
      printf("\n");
  }
    
  }
  else{
    
    campoMinado[x][y].campo = '*';
    for(int i = 0 ; i < LINHAS ; i++ ){
      for(int j = 0 ; j < COLUNAS ; j++){
        printf("%c", campoMinado[i][j].campo);
    }
      printf("\n");
  }
  }
  
}

int main(int argc, char const *argv[])
{   
    int x,y;
  
    inicioJogo();
    addBombas(QTD_BOMBAS, campoMinado);
    campovisualinicial(campoMinado);
    scanf("%d %d" , &x ,&y);

    while(campoMinado[x][y].temBomba != true){
      campovisual(campoMinado,x,y);
      
      scanf("%d %d" , &x ,&y);
    }

    return 0;
}
