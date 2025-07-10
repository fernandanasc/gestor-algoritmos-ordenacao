# Nome do executável
EXEC = main.exe

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Ofast -Iinclude

# Diretórios
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Arquivos-fonte
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Alvo padrão
all: $(EXEC)

# Compilação do executável
$(EXEC): main.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilação dos arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	@echo Iniciando limpeza completa...
	@if exist $(OBJ_DIR) del /q $(OBJ_DIR)\*.o && echo - Arquivos objeto removidos
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR) && echo - Diretorio obj removido
	@if exist $(EXEC) del /q $(EXEC) && echo - Executavel main.exe removido
	@powershell -Command "if (Test-Path 'data\*.csv') { Remove-Item 'data\*.csv' -Force; Write-Host '- Arquivos CSV removidos' } else { Write-Host '- Nenhum arquivo CSV encontrado' }"
	@echo Limpeza completa concluida!

# Limpeza apenas dos arquivos CSV
clean-data:
	@echo Removendo arquivos CSV...
	@powershell -Command "if (Test-Path 'data\*.csv') { Remove-Item 'data\*.csv' -Force; Write-Host 'Arquivos CSV removidos da pasta data/' } else { Write-Host 'Nenhum arquivo CSV encontrado na pasta data/' }"

.PHONY: all clean clean-data
