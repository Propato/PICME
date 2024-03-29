#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "../include/dados.h"
#include "../include/gauss_seidel.h"

void Gauss_Seidel(Dados* dados){

  double soma;
  int i, j;

  for(i=0; i<dados->n; i++){
    soma = dados->b[i] + dados->x[i]*dados->A[i][i];

    for(j=0; j<dados->n; j++){
      soma = soma - dados->x[j]*dados->A[i][j];
    }
    dados->ant[i] = dados->x[i];
    dados->x[i] = soma/dados->A[i][i];
  }
}

int erro_GS(Dados* dados){

  double aux, X, Y, somaX=0, somaY=0;
  int i;

  for(i=0; i<dados->n; i++){

    aux = dados->x[i] - dados->ant[i];
    somaX = somaX + (aux*aux);
    somaY = somaY + (dados->ant[i]*dados->ant[i]);
  }
  
  X = sqrt(somaX);
  Y = sqrt(somaY);

  aux = X/Y;

  if((aux <= 0.0000001) || (aux == 0)){
    return 1;
  }else return 0;
}

void main_GS(char** argv){

  time_t tempo;
  tempo = clock();
  
  char* nome_saida = (char*)malloc(sizeof(char)*30);
  strcpy(nome_saida, "Saidas/GS/vet");
  strcat(nome_saida, &argv[1][strlen(argv[1])-5]);

  char* nome_normas = (char*)malloc(sizeof(char)*30);
  strcpy(nome_normas, "Saidas/GS/normas_vet");
  strcat(nome_normas, &argv[1][strlen(argv[1])-5]);

  Dados* dados = lerEntrada(argv[1]);
  FILE* normas = fopen(nome_normas, "w");

  int i=0;

  int igualdade = 0;

  while(!igualdade && i< (dados->n*6)){
    i++;
    Gauss_Seidel(dados);

    if(i%10 == 0)
      fprintf(normas, "%.10lf\n", Norma(dados->n, dados->x));

    igualdade = erro_GS(dados);
  }
    if(i%10 != 0)
      fprintf(normas, "%.10lf\n", Norma(dados->n, dados->x));

  imprimeVet(nome_saida, dados->n, dados->x);

  tempo = clock() - tempo;

  Infos("GS", argv[1], ((double)tempo)*2/CLOCKS_PER_SEC, i*3, Norma(dados->n, dados->x));
  
  cleanDados(dados);
  free(nome_saida);
  free(nome_normas);
  fclose(normas);
}