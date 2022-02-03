#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Funcoes/Dados.h"

void multiplica_U(int n, double **U, double *Y){

  int i, j;
  double A[n], X[n];

  for(i=0; i<n; i++){
    A[i] = 0;
    X[i] = 1;
    for(j=i+1; j<n; j++){
      U[i][j] = U[j][i];
      U[j][i] = 0;
    }
  }

  for(i=n-1; i>=0; i--){
  
  for(j=n-1; j>=0;j--)
  {A[i] = A[i] + X[j]*U[i][j];}
    
  A[i] = A[i] - U[i][i];
  X[i] = Y[i] - A[i];
  if(U[i][i] != 0 && U[i][i] != 1){
  X[i] = X[i]/U[i][i];}

  Y[i] = X[i];
  }
}

void multiplica_L(int n, double **L, double *Y){

  int i, j;
  double A[n], X[n];

  for(i=0; i<n; i++){
    A[i] = 0;
    X[i] = 1;
  }

  for(i = 0; i<n; i++){
  
  for(j = 0; j<n; j++)
  {A[i] = A[i] + X[j]*L[i][j];}
    
  A[i] = A[i] - L[i][i];
  X[i] = Y[i] - A[i];
  if(L[i][i] != 0 && L[i][i] != 1){
  X[i] = X[i]/L[i][i];}

  Y[i] = X[i];
  }
}

int main(int argc, char** argv){

  time_t tempo;
  tempo = clock();
  
  FILE* entrada = fopen(argv[1], "r");
  FILE* saida = fopen(argv[2], "w");

  int n, i, j, k, l;
  
  double **L, *X;

//le tamanho da matriz
  fscanf(entrada, "%d", &n);

  L = (double**)malloc(sizeof(double*)*n);
  X = (double*)malloc(sizeof(double)*n);
  
//le matriz e preenche matriz L
  for(i=0; i<n; i++){

   L[i] = (double*)malloc(sizeof(double)*n);

    for(j=0; j<n; j++){
      fscanf(entrada, "%lf,", &L[i][j]);}
  }

  for(i=0; i<n; i++){
    fscanf(entrada, "%lf", &X[i]);
  }
 
  for(i = 0; i<n; i++){
    
    L[i][i] = sqrt(L[i][i]);
    
    for(j = i+1; j<n; j++){
      L[j][i] = L[j][i]/L[i][i];
    }

    for(k = i+1; k<n; k++){
      for(l = k; l<n; l++){
        L[l][k] = L[l][k] - L[l][i] * L[k][i];
      }
    }
  }

  for(i = 0; i<n; i++){
    for(j = i; j<n; j++){
      if(j != i)
      L[i][j] = 0;
    }
  }

  multiplica_L(n, L, X);
  multiplica_U(n, L, X);

//print
  for(i=0; i<n; i++){
    fprintf(saida, "%.15lf\n", X[i]);
  }

  fclose(entrada);
  fclose(saida);

  tempo = clock() - tempo;

  Dados("C", argv[1], ((double)tempo)*2/CLOCKS_PER_SEC, 0, Norma(n, X));
 
  free(X);

  for(i=0;i<n;i++){
    free(L[i]);
  }
  free(L);

  return 0;
}