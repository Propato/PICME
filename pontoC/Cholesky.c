#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Funcoes/Dados.h"

void multiplica_U(Dados* dados){

  int i, j;

  for(i=dados->n-1; i>=0; i--){
  
    for(j=dados->n-1; j>=i; j--)
      dados->ant[i] = dados->ant[i] + dados->b[j]*dados->A[j][i];
    
    dados->ant[i] = dados->ant[i] - dados->A[i][i];
    dados->b[i] = dados->x[i] - dados->ant[i];
    
    if(dados->A[i][i] != 0 && dados->A[i][i] != 1)
      dados->b[i] = dados->b[i]/dados->A[i][i];
  }
}

void multiplica_L(Dados* dados){

  int i, j;

  for(i = 0; i<dados->n; i++){
  
    for(j = 0; j<=i; j++)
      dados->ant[i] = dados->ant[i] + dados->x[j]*dados->A[i][j];
    
    dados->ant[i] = dados->ant[i] - dados->A[i][i];
    dados->x[i] = dados->b[i] - dados->ant[i];

    if(dados->A[i][i] != 0 && dados->A[i][i] != 1)
      dados->x[i] = dados->x[i]/dados->A[i][i];

    dados->ant[i] = 0;
    dados->b[i] = 1;
  }
}

int main(int argc, char** argv){

  time_t tempo;
  tempo = clock();
  
  Dados* dados = lerEntrada(argv[1]);
  FILE* saida = fopen(argv[2], "w");

  int i, j, l;

  for(i = 0; i<dados->n; i++){
    
    dados->A[i][i] = sqrt(dados->A[i][i]);
    
    for(j = i+1; j<dados->n; j++)
      dados->A[j][i] = dados->A[j][i]/dados->A[i][i];

    for(j = i+1; j<dados->n; j++){
      for(l = j; l<dados->n; l++){
        dados->A[l][j] = dados->A[l][j] - dados->A[l][i] * dados->A[j][i];
      }
    }
  }

  multiplica_L(dados);
  multiplica_U(dados);

  imprimeVet(argv[2], dados->n, dados->b);

  fclose(saida);

  tempo = clock() - tempo;

  Infos("C", argv[1], ((double)tempo)*2/CLOCKS_PER_SEC, 0, Norma(dados->n, dados->b));

  cleanDados(dados);

  return 0;
}