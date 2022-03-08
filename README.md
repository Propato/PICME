Códigos do Projeto do PICME na UFES, feitos por David Propato com auxílio do professor Fabiano Petronetto.

O projeto consiste no estudo de sistemas lineares e suas resoluções aplicadas em códigos (nesse caso, em C), focando inicialmente nos métodos LU e Cholesky e depois nos métodos iterativos de Gauss-Jacobi e Gauss-Seidel.

Analisando também os vetores soluções gerados nos métodos iterativos antes de se chegar no vetor solução final, analisando suas normas e como progridem ao longo da execução do código e da solução do sistema.

Nos arquivos se encontra:

    A pasta /Entradas com as matrizes A e vetores b e as dimensões em .txt (Ax = b) para serem lidos.
    Uma pasta GabaritosAproximados com vetores solução do sistema (valores são aproximações).
    E a pasta pontoC, que contém:

        Uma pasta Funcoes que armazena o TAD de dados das soluções dos sistemas, tendo uma struct para armazenar a matriz lida, o vetor b, o vetor solução x e um vetor auxiliar chamado ant, tem também funções para ler todas as entradas, calcular as normas e gerar um arquivo de saida com os dados importantes.
        E os .c de cada método:
            
            -LU.c
            -Cholesky.c
            -Gauss-Jacobi.c
            -Gauss-Seidel.c


E o makefile, com as seguintes regras:

    make all == carrega todos .o e executaveis, criando pastas para armazena-los e pastas de saida para cada método.
    make run == executa os códigos, armazenando o .txt com o vetor solução na pasta determinada de cada método e gerando um .txt com dados sobre os métodos, tendo o tempo que levou para terminar a execução de cada método e a norma do vetor resultante final, no caso de GJ e GS, é escrito também a quantidade de loops até encerrar a execução.
    make clean == remove todas as pastas e arquivos gerados.

E tambem um Arquivo Excel com tabelas das normas dos vetores soluções gerados nos loops dos métodos GJ e GS, junto da norma unica dos métodos LU e C, formando gráficos com os dados desses vetores para as 3 matrizes testes.