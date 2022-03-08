#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Funcoes/Dados.h"

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

void clean(int n, double **matriz, double *vet, double *x, double *aux){
  free(vet);
  free(x);
  free(aux);

  for(int i=0; i<n; i++){
    free(matriz[i]);
  }free(matriz);
}

void imprime_vet(int n, double *vet, FILE* saida){

  for(int i=0; i<n; i++){

    fprintf(saida, "%.15lf\n", vet[i]);
  }
}

int erro(Dados* dados){

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

int main(int argc, char** argv){

  time_t tempo;
  tempo = clock();
  
  Dados* dados = lerEntrada(argv[1]);
  FILE* normas = fopen(argv[3], "w");

  int i=0;

  int igualdade = 0;

  while(!igualdade && i< (dados->n*6)){
    i++;
    Gauss_Seidel(dados);

    if(i%10 == 0)
      fprintf(normas, "%.10lf\n", Norma(dados->n, dados->x));

    igualdade = erro(dados);
  }
    if(i%10 != 0)
      fprintf(normas, "%.10lf\n", Norma(dados->n, dados->x));

  imprimeVet(argv[2], dados->n, dados->x);

  tempo = clock() - tempo;

  Infos("GS", argv[1], ((double)tempo)*2/CLOCKS_PER_SEC, i*3, Norma(dados->n, dados->x));
  
  cleanDados(dados);
  fclose(normas);

  return 0;
}