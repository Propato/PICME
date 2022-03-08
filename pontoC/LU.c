#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Funcoes/Dados.h"

void multiplica_U(Dados* dados){

  int i, j;

  for(i=dados->n-1; i>=0; i--){
  
    for(j=dados->n-1; j>=0;j--)
      dados->ant[i] = dados->ant[i] + dados->x[j]*dados->A[i][j];
    
    dados->ant[i] = dados->ant[i] - dados->A[i][i];
    dados->x[i] = dados->b[i] - dados->ant[i];
    
    if(dados->A[i][i] != 0 && dados->A[i][i] != 1){
      dados->x[i] = dados->x[i]/dados->A[i][i];}

    dados->b[i] = dados->x[i];
  }
}

int main(int argc, char** argv){

  time_t tempo;
  tempo = clock();

  Dados* dados = lerEntrada(argv[1]);
  FILE* saida = fopen(argv[2], "w");

  int i=1, j=0, a=0, x=0, y=0;
  double aux;

  while(y<dados->n && x<dados->n){

    //checa elemento lider nulo na linha y
    while(dados->A[y][j] == 0 && x<dados->n){

      if(dados->A[i][j] != 0){

        for(a = 0; a<dados->n; a++){
          aux = dados->A[y][a];
          dados->A[y][a] = dados->A[i][a];
          dados->A[i][a] = aux;
        }

        aux = dados->b[i];
        dados->b[i] = dados->b[y];
        dados->b[y] = aux;
        }

      i++;

      if(dados->A[y][j] == 0 && i>=dados->n){
        i = y+1;
        x++;
        j = x;}
    }

    //faz as operaçoes elementares na matriz A e no vetor b 
    for(i = y+1; i<dados->n; i++){

      dados->b[i] = dados->b[i] - ((dados->A[i][x]/dados->A[y][x]) * dados->b[y]);

      for(j=dados->n-1; j>=x; j--){
        dados->A[i][j] = dados->A[i][j] - ((dados->A[i][x]/dados->A[y][x]) * dados->A[y][j]);
      }
    }

    y++;
    x++;
    j = x;
    i = y;
  }

  //calcula o vetor solucao do sistema
  multiplica_U(dados);

  imprimeVet(argv[2], dados->n, dados->b);

  fclose(saida);

  tempo = clock() - tempo;

  Infos("LU", argv[1], ((double)tempo)*2/CLOCKS_PER_SEC, 0, Norma(dados->n, dados->b));

  cleanDados(dados);

  return 0;
}