# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Répertoires
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
HDR_DIR = include

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

# Afficher les fichiers détectés
info:
	@echo "$(CYAN)=== Informations du projet ===$(RESET)"
	@echo "$(YEllOW)Sources détectées :$(RESET)"
	@for src in $(SRC_DIR); do echo "  - $$src"; done
	@echo ""
	@echo "$(YELLOW)Headers détectés :$(RESET)"
	@for hdr in $(HDR_DIR); do echo "  - $$hdr"; done
	@echo ""
	@echo "$(YELLOW)Objets à générer :$(RESET)"
	@for obj in $(OBJ_DIR); do echo "  - $$obj"; done
	@echo ""
	@echo "$(YELLOW)Exécutable :$(RESET) $(TARGET)"

# Debug: compilation avec symboles de debug
debug: CFLAGS += -DDEBUG -O0
debug: clean all
	@echo "$(GREEN)Compilation en mode DEBUG$(RESET)"

# Compilation et exécution
run: all
	@echo "$(CYAN)╔═════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║       Lancement de KlientHTTP       ║$(RESET)"
	@echo "$(CYAN)╚═════════════════════════════════════╝$(RESET)"
	@echo ""
	@./$(TARGET)

# Aide
help:
	@echo "$(CYAN)╔═════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║        Commandes disponibles        ║$(RESET)"
	@echo "$(CYAN)╚═════════════════════════════════════╝$(RESET)"
	@echo ""
	@echo "  $(YELLOW)make$(RESET)			- Compile le projet"
	@echo "  $(YELLOW)make run$(RESET)		- Compile et exéute"
	@echo "  $(YELLOW)make clean$(RESET)		- Nettoie les fichiers compilés"
	@echo "  $(YELLOW)make fclean$(RESET)		- Nettoyage complet"
	@echo "  $(YELLOW)make re$(RESET)		- Recompile tout"
	@echo "  $(YELLOW)make debug$(RESET)		- Compile en mode debug"
	@echo "  $(YELLOW)make info$(RESET)		- Affiche les infos du projet"
	@echo "  $(YELLOW)make help$(RESET)		- Affiche cette aide"

.PHONY: all clean fclean re
.DEFAULT_GOAL := all