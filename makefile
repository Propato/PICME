# executaveis = Cexe GJexe GSexe LUexe

# CPP = gcc
# flags = -lm -g -Wall

# obj = src/LU.o src/Cholesky.o src/Gauss-Jacobi.o src/Gauss-Seidel.o src/Funcoes/Dados.o

# pastas = obj Executaveis Saidas/LU Saidas/Cholesky Saidas/Gauss-Jacobi Saidas/Gauss-Seidel

# ##ALTERE VALOR DE <matriz> PARA ESPECIFICAR QUAL ARQUIVO DESEJA LER E EXECUTAR##
# ##Possiveis valores -> 1, 2 e 3##
# matriz = 3

# arqLU = Entradas/matriz$(matriz).txt Saidas/LU/vet$(matriz).txt
# arqC  = Entradas/matriz$(matriz).txt Saidas/Cholesky/vet$(matriz).txt
# arqGJ = Entradas/matriz$(matriz).txt Saidas/Gauss-Jacobi/vet$(matriz).txt Saidas/Gauss-Jacobi/NormasVet$(matriz).txt
# arqGS = Entradas/matriz$(matriz).txt Saidas/Gauss-Seidel/vet$(matriz).txt Saidas/Gauss-Seidel/NormasVet$(matriz).txt

# all: carrega | diretorios

# carrega: $(obj)
# 	@echo Compilando...
	
# 	gcc -o LUexe LU.o Dados.o $(flags)
# 	gcc -o Cexe Cholesky.o Dados.o $(flags)
# 	gcc -o GJexe Gauss-Jacobi.o Dados.o $(flags)
# 	gcc -o GSexe Gauss-Seidel.o Dados.o $(flags)
	
# 	@echo Compilado!!!

# %.o: %.c
# 	gcc -c $^ $(flags)
	
# diretorios:
# 	@mkdir -p $(pastas)
# 	@mv *.o ./obj
# 	@mv LUexe ./Executaveis
# 	@mv Cexe ./Executaveis
# 	@mv GJexe ./Executaveis
# 	@mv GSexe ./Executaveis
# 	@echo Pastas geradas e arquivos armazenados!!
	
# clean:
# 	rm -rf *.o obj Saidas $(executaveis) Executaveis

# run:
# 	./Executaveis/LUexe $(arqLU) & ./Executaveis/Cexe $(arqC) & ./Executaveis/GJexe $(arqGJ) & ./Executaveis/GSexe $(arqGS)

# val:
# 	valgrind ./Executaveis/LUexe $(arqLU) & valgrind ./Executaveis/Cexe $(arqC) & valgrind ./Executaveis/GJexe $(arqGJ) & valgrind ./Executaveis/GSexe $(arqGS)

#################################################################################################################################################

VAL = 1

INPUT = ./Entradas/matriz$(VAL).txt
OUTPUTS_FOLDER = ./Saidas ./Saidas/LU/ ./Saidas/C/ ./Saidas/GJ/ ./Saidas/GS/

MAIN = main.c
SRC_FOLDER = src
OBJ_FOLDER = obj

EXECUTAVEL = picme
CPP = gcc
CFLAGS = -lm -g -Wall

SRC = $(wildcard $(SRC_FOLDER)/*.c)
OBJ = $(subst $(SRC_FOLDER),$(OBJ_FOLDER),$(SRC:.c=.o))

############ ALVOS

# gera o executável, a pasta obj e armazena os .o nela
all: $(OBJ_FOLDER) $(OUTPUTS_FOLDER) $(EXECUTAVEL)

# gera pasta dos arquivos-objetos
$(OBJ_FOLDER) $(OUTPUTS_FOLDER):
	mkdir -p $@

# linka o executável aos arquivos-objeto
$(EXECUTAVEL): $(OBJ_FOLDER)/$(MAIN:.c=.o) $(OBJ)
	$(CPP) $^ -o $@ $(CFLAGS)
	@echo executavel

# gera arquivos-objeto
$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	$(CPP) -c $< -o $@ $(CFLAGS)
	@echo objs

$(OBJ_FOLDER)/$(MAIN:.c=.o): $(MAIN)
	$(CPP) -c $< -o $@ $(CFLAGS)
	@echo main

clean:
	rm -rf $(OBJ_FOLDER) $(OUTPUTS_FOLDER) $(EXECUTAVEL)

run:
	./$(EXECUTAVEL) $(INPUT)

val:
	valgrind --leak-check=full ./$(EXECUTAVEL) $(INPUT)