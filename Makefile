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

# Couleurs pour les messages
GREEN = \033[0;32m
CYAN = \033[0;36m
YELLOW = \033[0;33m
RED = \033[0;31m
BOLD = \033[1m
RESET = \033[0m

# Règle par défaut
all: banner $(TARGET)
	@echo ""
	@echo "$(GREEN)$(BOLD)Compilation terminée avec succès !$(RESET)"
	@echo "$(CYAN)Exécutez avec : ./$(TARGET)$(RESET)"
	@echo ""

# Banner de compilation
banner:
	@echo "$(CYAN)╔═════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║      Compilation de KlientHTTP      ║$(RESET)"
	@echo "$(CYAN)╚═════════════════════════════════════╝$(RESET)"
	@echo ""

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
	rm -rf $(BIN_DIR)

# Recompilation complète
re: fclean all

# Compilation et exécution
run: all
	@echo "$(CYAN)╔═════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║       Lancement de KlientHTTP       ║$(RESET)"
	@echo "$(CYAN)╚═════════════════════════════════════╝$(RESET)"
	@echo ""
	@./$(TARGET)

.PHONY: all clean fclean re