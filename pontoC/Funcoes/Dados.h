#ifndef DADOS_H
#define DADOS_H

typedef struct dados{
    int n;
    double** A;
    double* x;
    double* b;

    double* ant;
}Dados;

Dados* lerEntrada(char* arquivo);

double Norma(int n, double *vet);

void Infos(char* metodo, char* entrada, double tempo, int loops, double norma);

void imprimeVet(char* arquivo, int n, double* x);

void cleanDados(Dados* dados);

#endif