# Nome do programa principal
MAIN = mergesort

# Compilador utilizado
CC = gcc

# Define as flags de compilação (warnings)
CCFLAGS = -Wall

LIBS = -lpthread

# Define as variáveis para os arquivos fonte, headers e objetos
SOURCES = $(wildcard ./src/*.c)
HEADERS = $(wildcard ./src/*.h)
OBJECTS = $(SOURCES:.c=.o)

# Define o diretório do programa
PROGRAMDIR = .

# Regra principal: compila o programa e limpa os objetos
all: $(MAIN) clean_objects

# Regra para compilar o programa principal
$(MAIN): $(OBJECTS)
	$(CC) $(LIBS) $(OBJECTS) -o $(PROGRAMDIR)/$(MAIN)
	@echo "Programa compilado com sucesso!"
	@echo "Execute: $(PROGRAMDIR)/$(MAIN)"

# Regra genérica para compilar arquivos .c em .o
%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(LIBS) -c $< -o $@

# Regra para limpar os arquivos objeto 
clean_objects:
	@rm -f $(OBJECTS)

# Regra para limpar o executável e os arquivos objeto
clean:
	rm -f $(PROGRAMDIR)/$(MAIN) $(OBJECTS)
	@echo "Executável e arquivos objeto removidos."