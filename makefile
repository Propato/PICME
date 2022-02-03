executaveis = Cexe GJexe GSexe LUexe

flags = -lm -g -Wall

obj = pontoC/LU.o pontoC/Cholesky.o pontoC/Gauss-Jacobi.o pontoC/Gauss-Seidel.o pontoC/Funcoes/Dados.o

pastas = obj Executaveis Saidas/LU Saidas/Cholesky Saidas/Gauss-Jacobi Saidas/Gauss-Seidel

##ALTERE VALOR DE <matriz> PARA ESPECIFICAR QUAL ARQUIVO DESEJA LER E EXECUTAR##
matriz = 2

arqLU = Entradas/matriz$(matriz).txt Saidas/LU/vet$(matriz).txt
arqC  = Entradas/matriz$(matriz).txt Saidas/Cholesky/vet$(matriz).txt
arqGJ = Entradas/matriz$(matriz).txt Saidas/Gauss-Jacobi/vet$(matriz).txt Saidas/Gauss-Jacobi/NormasVet$(matriz).txt
arqGS = Entradas/matriz$(matriz).txt Saidas/Gauss-Seidel/vet$(matriz).txt Saidas/Gauss-Seidel/NormasVet$(matriz).txt

all: carrega | diretorios

carrega: $(obj)
	@echo Compilando...
	
	gcc -o LUexe LU.o Dados.o $(flags)
	gcc -o Cexe Cholesky.o Dados.o $(flags)
	gcc -o GJexe Gauss-Jacobi.o Dados.o $(flags)
	gcc -o GSexe Gauss-Seidel.o Dados.o $(flags)
	
	@echo Compilado!!!

%.o: %.c
	gcc -c $^ $(flags)
	
diretorios:
	@mkdir -p $(pastas)
	@mv *.o ./obj
	@mv LUexe ./Executaveis
	@mv Cexe ./Executaveis
	@mv GJexe ./Executaveis
	@mv GSexe ./Executaveis
	@echo Pastas geradas e arquivos armazenados!!
	
clean:
	rm -rf obj Saidas Executaveis

run:
	./Executaveis/LUexe $(arqLU) & ./Executaveis/Cexe $(arqC) & ./Executaveis/GJexe $(arqGJ) & ./Executaveis/GSexe $(arqGS)