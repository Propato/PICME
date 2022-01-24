Códigos do Projeto do PICME, feitos por David Propato com auxílio do professor Fabiano Petronetto.

O projeto consiste no estudo de sistemas lineares e suas resoluções aplicadas em códigos (nesse caso, em C), focando inicialmente nos métodos LU e Cholesky e depois nos métodos interativos de Gauss-Jacobi e Gauss-Seidel.

Nos arquivos se encontra:
A pasta /Entradas com as matrizes A e vetores b em .txt (Ax = b) para ser lido.
Um gabarito com vetores solução do sistema (valores são aproximações).
Os .c de cada método:
-LU.c
-Cholesky.c
-Gauss-Jacobi.c
-Gauss-Seidel.c

E o makefile, com as seguintes regras:
-make all == carrega todos .o e executaveiis, criando pastas para armazena-los e pastas de saida para cada método.
                
-make LU  (LU)
-make C   (Cholesky)
-make GJ  (Gauss-Jacobi)
-make GS  (Gauss-Seidel)

regras que rodam o executavel de cada arquivo, armazenando o .txt com o vetor solução na pasta determinada de cada método e gerando um .txt com o tempo que cada método levou para terminar a execução, no caso de GJ e GS, é escrito também a quantidade de loops até encerrar a execução.

-make clean == remove todas as pastas e arquivos gerados.