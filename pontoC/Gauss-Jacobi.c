#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Funcoes/Dados.h"

void Gauss_jacobi(int n, double **matriz, double *vet, double *x){

  double soma, aux[n];
  int i, j;

  for(i=0; i<n; i++)
    aux[i] = x[i];

  for(i=0; i<n; i++){

    soma = vet[i] + x[i]*matriz[i][i];

    for(j=0; j<n; j++){
      soma = soma - aux[j]*matriz[i][j];
    }
    x[i] = soma/matriz[i][i];
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

int erro(int n, double *x, double *y){

  double aux, X, Y, somaX=0, somaY=0;
  int i;

  for(i=0; i<n; i++){

    aux = x[i] - y[i];
    somaX = somaX + (aux*aux);
    somaY = somaY + (y[i]*y[i]);
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
  
  FILE* entrada = fopen(argv[1], "r");
  FILE* saida = fopen(argv[2], "w");
  FILE* normas = fopen(argv[3], "w");

  int n, i, j;

  double *x, **matriz, *vet, *aux;

  fscanf(entrada, "%d", &n);

  matriz = (double**)malloc(sizeof(double*)*n);

  x = (double*)malloc(sizeof(double)*n);
  vet = (double*)malloc(sizeof(double)*n);
  aux = (double*)malloc(sizeof(double)*n);

  for(i=0; i<n; i++){

    matriz[i] = (double*)malloc(sizeof(double)*n);

    for(j=0; j<n; j++){
      fscanf(entrada, "%lf,", &matriz[i][j]);
    }
  }

  for(i=0; i<n; i++){
    fscanf(entrada, "%lf", &vet[i]);
    x[i] = 0.5;
  }

  int igualdade = 0;

  i=0;
  while(!igualdade && i< (n*6)){
  i++;

    for(j=0; j<n; j++){
      aux[j] = x[j];
    }

    Gauss_jacobi(n, matriz, vet, x);

    if(i%10 == 0)
      fprintf(normas, "%.15lf\n", Norma(n, x));

    igualdade = erro(n, x, aux);
  }
    if(i%10 != 0)
      fprintf(normas, "%.15lf\n", Norma(n, x));

  imprime_vet(n, x, saida);

  fclose(entrada);
  fclose(saida);

  tempo = clock() - tempo;

  Dados("GJ", argv[1], ((double)tempo)*2/CLOCKS_PER_SEC, i, Norma(n, x));
  
  clean(n, matriz, vet, x, aux);

  return 0;
}