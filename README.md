# Programa de Iniciação Científica e Mestrado

Aqui estão os códigos do Projeto do PICME na UFES, feitos por David Propato com auxílio do professor Fabiano Petronetto.

O projeto consiste no estudo de sistemas lineares e suas resoluções aplicadas em códigos (nesse caso, em C), focando inicialmente nos métodos LU e Cholesky e depois nos métodos iterativos de Gauss-Jacobi e Gauss-Seidel.

Analisando também os vetores soluções gerados nos métodos iterativos antes de se chegar no vetor solução final, analisando suas normas e como progridem ao longo da execução do código e da solução do sistema.

Nos arquivos se encontra:

* A pasta /Entradas com as matrizes A e vetores b e as dimensões em .txt (Ax = b) para serem lidos.
* Uma pasta GabaritosAproximados com vetores solução do sistema (valores são aproximações).
* E as pastas src e include, que contém os arquivos .c e .h dos métodos
* E o makefile, com as seguintes regras:
* E tambem um Arquivo Excel com tabelas das normas dos vetores soluções gerados nos loops dos métodos GJ e GS, junto da norma unica dos métodos LU e C, formando gráficos com os dados desses vetores para as 3 matrizes testes.

## Makefile

- `make all` carrega todos .o e executaveis, criando pastas para armazena-los e pastas de saida para cada método.
- `make run` executa os códigos, armazenando um .txt com o vetor solução na pasta determinada de cada método e gerando um .txt com dados sobre os métodos, tendo o tempo que levou para terminar a execução de cada método e a norma do vetor resultante final, no caso de GJ e GS, é escrito também a quantidade de loops até encerrar a execução.
- `make clean` remove todas as pastas e arquivos gerados.
- `make val` executa com o valgrind para checagem de vazamentos de memória.

## Ferramentas utilizadas

<table>
    <tr align="center">
         <td>
            <img alt="Icone C" title="C" height="60" src="https://user-images.githubusercontent.com/84464307/224509054-5fd43a1f-7330-4d0f-b066-25ff6df69f53.png">
         </td>
         <td>    
            <img alt="Icone GNU Makefile" title="GNU Makefile" height="60" src="https://user-images.githubusercontent.com/84464307/224509679-b957b786-f83a-403a-b088-7132a54bd024.svg">
         </td>
         <td>
            <img alt="Icone Git" title="Git" height="60" src="https://user-images.githubusercontent.com/84464307/224510001-3e60f54c-2a0a-4ae9-bee6-f5b10df9ecf1.svg">
         </td>
    </tr>
    <tr align="center">
        <td>
            C
        </td>
        <td>    
            GNU Makefile
        </td>
        <td>
            Git
        </td>
    </tr>
</table>

<h6 align="center">by David Propato <a href="https://github.com/Propato">@Propato</a></h6>
