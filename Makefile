# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Répertoires
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Nom de l'exécutable
TARGET = $(BIN_DIR)/KlientHTTP

# Récupération automatique des sources
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Règle principale
all: $(TARGET)

# Construction du programme
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Compilation des .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re