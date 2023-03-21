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
OBJ = $(patsubst $(SRC_FOLDER)/%.c, $(OBJ_FOLDER)/%.o, $(SRC))

############ ALVOS

# gera o executável, a pasta obj e as pastas de saida
all: $(OBJ_FOLDER) $(OUTPUTS_FOLDER) $(EXECUTAVEL)

# gera pasta dos arquivos-objetos as pastas de saida
$(OBJ_FOLDER) $(OUTPUTS_FOLDER):
	@mkdir -p $@

# linka o executável aos arquivos-objeto
$(EXECUTAVEL): $(OBJ_FOLDER)/$(MAIN:.c=.o) $(OBJ)
	@$(CPP) $^ -o $@ $(CFLAGS)

# gera arquivos-objeto
$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	@$(CPP) -c $< -o $@ $(CFLAGS)

$(OBJ_FOLDER)/$(MAIN:.c=.o): $(MAIN)
	@$(CPP) -c $< -o $@ $(CFLAGS)

clean:
	@rm -rf $(OBJ_FOLDER) $(OUTPUTS_FOLDER) $(EXECUTAVEL)

run:
	@./$(EXECUTAVEL) $(INPUT)

val:
	valgrind --leak-check=full ./$(EXECUTAVEL) $(INPUT)
