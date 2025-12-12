CC = cc
# Flags de Compilação (Warnings, Includes)
CFLAGS = -Wall -Wextra -Isrc 
# Flags de Linker (Bibliotecas como math.h)
LIBS = -lm

SRC_DIR = src
OUT_DIR = build

# Lista apenas os nomes dos ficheiros
_OBJS = main.o lialg.o functions.o
# Adiciona o prefixo 'build/' a cada item da lista
OBJS = $(addprefix $(OUT_DIR)/, $(_OBJS))

.PHONY : all clean execute

all : $(OUT_DIR) main clean execute

# Cria a pasta build se ela não existir
$(OUT_DIR) :
	mkdir -p $(OUT_DIR)

# O target 'main' depende da lista completa com caminhos (build/main.o, etc.)
main : $(OBJS)
	$(CC) $(OBJS) -o $(OUT_DIR)/main $(LIBS)

# Regra Genérica: Compila .c em src/ para .o em build/
$(OUT_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

execute :
	clear
	./$(OUT_DIR)/main

clean :
	rm -f $(OUT_DIR)/*.o