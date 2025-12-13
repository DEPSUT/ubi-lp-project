CC = cc
# Flags de Compilação (Warnings, Includes)
CFLAGS = -Wall -Wextra -Isrc 
# Flags de Linker (Bibliotecas como math.h)
LIBS = -lm

SRC_DIR = src
OUT_DIR = build
EXEC = $(OUT_DIR)/main

# Lista apenas os nomes dos ficheiros
_OBJS = main.o lialg.o functions.o menu_functions.o
# Adiciona o prefixo 'build/' a cada item da lista
OBJS = $(addprefix $(OUT_DIR)/, $(_OBJS))

.PHONY : all clean execute

all : $(EXEC)

# Cria a pasta build se ela não existir
$(OUT_DIR) :
	mkdir -p $(OUT_DIR)

$(EXEC) : $(OUT_DIR) $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LIBS)

# Compila .c em src/ para .o em build/
$(OUT_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

execute : $(EXEC)
	clear
	./$(OUT_DIR)/main

clean :
	rm -f $(OUT_DIR)/*.o $(EXEC)