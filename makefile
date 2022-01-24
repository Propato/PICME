executaveis = Cexe GJexe GSexe LUexe

flags = -lm -g -Wall

obj = LU.o Cholesky.o Gauss-Jacobi.o Gauss-Seidel.o 

pastas = obj Executaveis Saidas/LU Saidas/Cholesky Saidas/Gauss-Jacobi Saidas/Gauss-Seidel

##ALTERE VALOR DE <matriz> PARA ESPECIFICAR QUAL ARQUIVO DESEJA LER E EXECUTAR.
matriz = 3

arqLU = Entradas/matriz$(matriz).txt Saidas/LU/vet$(matriz).txt
arqC  = Entradas/matriz$(matriz).txt Saidas/Cholesky/vet$(matriz).txt
arqGJ = Entradas/matriz$(matriz).txt Saidas/Gauss-Jacobi/vet$(matriz).txt
arqGS = Entradas/matriz$(matriz).txt Saidas/Gauss-Seidel/vet$(matriz).txt

all: carrega | diretorios

carrega: $(obj)
	@echo Compilando...
	
	gcc -o LUexe LU.o $(flags)
	gcc -o Cexe Cholesky.o $(flags)
	gcc -o GJexe Gauss-Jacobi.o $(flags)
	gcc -o GSexe Gauss-Seidel.o $(flags)
	
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

LU:
	./Executaveis/LUexe $(arqLU)

C:
	./Executaveis/Cexe $(arqC)

GJ:
	./Executaveis/GJexe $(arqGJ)

GS:
	./Executaveis/GSexe $(arqGS)