#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../include/dados.h"

Dados* lerEntrada(char* arquivo){

    Dados* dados = (Dados*)malloc(sizeof(Dados));

    FILE* entrada = fopen(arquivo, "r");

    fscanf(entrada, "%d", &dados->n);

    dados->A = (double**)malloc(sizeof(double*)*dados->n);
    dados->x = (double*)malloc(sizeof(double)*dados->n);
    dados->b = (double*)malloc(sizeof(double)*dados->n);
    dados->ant = (double*)malloc(sizeof(double)*dados->n);

    for(int i=0; i<dados->n; i++){

        dados->A[i] = (double*)malloc(sizeof(double)*dados->n);

        for(int j=0; j<dados->n; j++){
            fscanf(entrada, "%lf,", &dados->A[i][j]);
        }
    }

    for(int i=0; i<dados->n; i++){
        fscanf(entrada, "%lf", &dados->b[i]);
        dados->x[i] = 1;
        dados->ant[i] = 0;
    }
    fclose(entrada);

return dados;
}

FILE* Abre_arquivo(char *arquivo){

    char *saida = (char*)malloc(sizeof(char)*15);
    
    strcpy(saida, "Normas/");
    strcat(saida, arquivo);

    FILE* Saida = fopen(saida, "a");

    free(saida);

return Saida;
}

double Norma(int n, double *vet){

    double soma=0, norma;

    for(int i=0; i<n ; i++){
        
        soma = soma + (vet[i]*vet[i]);
    }
    
    norma = sqrt(soma);

    return norma;
}

void Infos(char* metodo, char* entrada, double tempo, int loops, double norma){

    FILE* dados = fopen("Saidas/Dados.txt", "a+");

    fprintf(dados, "%s - dados de %s:\n    Tempo: %lf Segundos.\n    Norma: %.10lf\n", metodo, entrada, tempo, norma);

    if(loops != 0)
        fprintf(dados, "    loops: %i\n\n", loops);
        else
            fprintf(dados, "\n");

    fclose(dados);
}

void imprimeVet(char* arquivo, int n, double* x){

    FILE* saida = fopen(arquivo, "w");

    for(int i=0; i<n; i++){
        fprintf(saida, "%.15lf\n", x[i]);
    }
  fclose(saida);
}

void cleanDados(Dados* dados){

    for(int i=0; i<dados->n; i++){
        free(dados->A[i]);
    }
    free(dados->A);
    free(dados->x);
    free(dados->b);
    free(dados->ant);

    free(dados);
}