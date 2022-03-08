#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Funcoes/Dados.h"

void Gauss_jacobi(Dados* dados){

  double soma;
  int i, j;

  for(i=0; i<dados->n; i++)
    dados->ant[i] = dados->x[i];

  for(i=0; i<dados->n; i++){

    soma = dados->b[i] + dados->x[i]*dados->A[i][i];

    for(j=0; j<dados->n; j++){
      soma = soma - dados->ant[j]*dados->A[i][j];
    }
    dados->x[i] = soma/dados->A[i][i];
  }
}

int erro(Dados* dados){

  double aux, X, Y, somaX=0, somaY=0;

  for(int i=0; i<dados->n; i++){

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

int main(int argc, char** argv){

  time_t tempo;
  tempo = clock();
  
  Dados* dados = lerEntrada(argv[1]);
  FILE* normas = fopen(argv[3], "w");

  int i=0;

  int igualdade = 0;

  while(!igualdade && i< (dados->n*6)){
    i++;
    Gauss_jacobi(dados);

    if(i%10 == 0)
      fprintf(normas, "%.10lf\n", Norma(dados->n, dados->x));

    igualdade = erro(dados);
  }
    if(i%10 != 0)
      fprintf(normas, "%.10lf\n", Norma(dados->n, dados->x));

  imprimeVet(argv[2], dados->n, dados->x);

  tempo = clock() - tempo;

  Infos("GJ", argv[1], ((double)tempo)*2/CLOCKS_PER_SEC, i*3, Norma(dados->n, dados->x));
  
  cleanDados(dados);
  fclose(normas);

  return 0;
}