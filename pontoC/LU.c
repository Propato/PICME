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

int main(int argc, char** argv){

  time_t tempo;
  tempo = clock();
  
  FILE* entrada = fopen(argv[1], "r");
  FILE* saida = fopen(argv[2], "w");

  int n, i, j, a=0, x=0, y=0;

  double **U, *X, aux;

  fscanf(entrada, "%d", &n);

  U = (double**)malloc(sizeof(double*)*n);
  X = (double*)malloc(sizeof(double)*n);
  
  for(i=0; i<n; i++){

    U[i] = (double*)malloc(sizeof(double)*n);

    for(j=0; j<n; j++){
      fscanf(entrada, "%lf,", &U[i][j]);}
  }

  for(i=0; i<n; i++){
   fscanf(entrada, "%lf", &X[i]);
  }

i = 1; j = 0;
while(y<n && x<n){

//checa elemento lider nulo na linha y
while(U[y][j] == 0 && x < n){

    if(U[i][j] != 0){

    for(a = 0; a < n; a++){
      aux = U[y][a];
      U[y][a] = U[i][a];
      U[i][a] = aux;
    }

    aux = X[i];
    X[i] = X[y];
    X[y] = aux;
    }

    i++;

    if(U[y][j] == 0 && i >= n){
      i = y+1;
      x++;
      j = x;}
  }

//faz as operaçoes elementares na matriz U e no vetor Y e preenche a matriz L 
  for(i = y+1; i < n; i++){

   X[i] = X[i] - ((U[i][x]/U[y][x]) * X[y]);

    for(j=n-1; j>=x; j--){
      U[i][j] = U[i][j] - ((U[i][x]/U[y][x]) * U[y][j]);
     }
  }

   y++;
   x++;
   j = x;
   i = y;
 }

//calcula o vetor solucao do sistema
multiplica_U(n, U, X);

//print
  for(i=0; i<n; i++){
    fprintf(saida, "%.15lf\n", X[i]);
  }

  fclose(entrada);
  fclose(saida);

  tempo = clock() - tempo;

  Dados("GS", argv[1], ((double)tempo)*2/CLOCKS_PER_SEC, 0, Norma(n, X));
  
  free(X);

  for(i=0;i<n;i++){
    free(U[i]);
  }
  free(U);


  return 0;
}