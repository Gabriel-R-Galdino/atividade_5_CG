# Detectando o Sistema Operacional
ifeq ($(OS),Windows_NT)
    EXE_EXT := .exe
    RM := rm -f
    CC := gcc
    RUN := build\Main.exe
else
    EXE_EXT :=
    RM := rm -f
    CC := gcc
    RUN := ./build/Main
endif

OUT_DIR := build
SRC_DIR := src
INC_DIR := include

# Alvo padrão
all: $(OUT_DIR)/Main$(EXE_EXT)

# Compilar Main
$(OUT_DIR)/Main$(EXE_EXT): $(SRC_DIR)/Main.c $(SRC_DIR)/Biblioteca.c | $(OUT_DIR)
	$(CC) -o $@ $(SRC_DIR)/Main.c $(SRC_DIR)/Biblioteca.c -I$(INC_DIR)

# Criar diretório de saída
$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

# Rodar o programa
run: $(OUT_DIR)/Main$(EXE_EXT)
	$(RUN)

# Limpar arquivos gerados
clean:
	$(RM) $(OUT_DIR)/*.o $(OUT_DIR)/*.exe
