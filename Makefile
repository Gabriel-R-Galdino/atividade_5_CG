# Configurar caminhos e flags utilizadas
OUT_DIR := build
SRC_DIR := src
INC_DIR := include
CFLAGS := -Wall -Wextra -Wpedantic -O0

# Pegar todos os sources
SOURCES := $(wildcard $(SRC_DIR)/*.c)

# Detectando o Sistema Operacional
ifeq ($(OS),Windows_NT)
	EXE_EXT := .exe
	RM := rm -f
	CC := gcc
	RUN := $(OUT_DIR)\Main.exe
else
	EXE_EXT :=
	RM := rm -f
	CC := gcc
	RUN := ./$(OUT_DIR)/Main
endif

# Definir caminho alvo
EXE_PATH := $(OUT_DIR)/Main$(EXE_EXT)

# Alvo padrão
all: $(EXE_PATH)

# Compilar executável final
$(EXE_PATH): $(SOURCES) | $(OUT_DIR)
	$(CC) -o $@ $(SOURCES) -I$(INC_DIR) $(CFLAGS)

# Criar diretório de saída
$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

# Rodar o programa
run: $(EXE_PATH)
	$(RUN)

# Limpar arquivos gerados
clean:
	$(RM) $(OUT_DIR)/*.o $(OUT_DIR)/*.exe $(EXE_PATH)
