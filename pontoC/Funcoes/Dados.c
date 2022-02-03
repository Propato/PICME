#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Dados.h"

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

    return norma = sqrt(soma);
}

void Dados(char* metodo, char* entrada, double tempo, int loops, double norma){

    FILE* dados = fopen("Saidas/Dados.txt", "a+");

    fprintf(dados, "%s - dados de %s:\n    Tempo: %lf Segundos.\n    Norma: %.15lf\n", metodo, entrada, tempo, norma);

    if(loops != 0)
        fprintf(dados, "    loops: %i\n\n", loops);
        else
            fprintf(dados, "\n");

    fclose(dados);
}