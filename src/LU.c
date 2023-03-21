#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "../include/dados.h"
#include "../include/LU.h"

void multiplica_U_LU(Dados* dados){

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

void main_LU(char** argv){

  time_t tempo;
  tempo = clock();

  char* nome_saida = (char*)malloc(sizeof(char)*30);
  strcpy(nome_saida, "Saidas/LU/vet");
  strcat(nome_saida, &argv[1][strlen(argv[1])-5]);
  printf("%s", nome_saida);
  
  Dados* dados = lerEntrada(argv[1]);

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
  multiplica_U_LU(dados);

  imprimeVet(nome_saida, dados->n, dados->b);

  tempo = clock() - tempo;

  Infos("LU", argv[1], ((double)tempo)*2/CLOCKS_PER_SEC, 0, Norma(dados->n, dados->b));

  cleanDados(dados);
  free(nome_saida);
}