# Nom de l'exécutable
NAME = minishell

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include

# Répertoires
SRC_DIR = srcs
OBJ_DIR = objs
INC_DIR = include

# Recherche des fichiers sources dans les sous-dossiers
SRCS = $(shell find $(SRC_DIR) -name "*.c")
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Commandes
RM = rm -rf

# Règles
all: $(NAME)

# Création de l'exécutable
$(NAME): $(OBJS)
	@echo "Compiling $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

# Compilation des fichiers .c en .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D) # Crée les sous-dossiers dans objs si nécessaire
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(LIBFT_INC) -c $< -o $@

# Création du répertoire objs
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Nettoyage des fichiers objets
clean:
	@echo "Cleaning object files..."
	$(RM) $(OBJ_DIR)

# Nettoyage complet
fclean: clean
	@echo "Removing executable..."
	$(RM) $(NAME)

# Recompilation complète
re: fclean all

# Inclure libft si nécessaire
bonus: $(LIBFT)

# Éviter des erreurs si le Makefile trouve des fichiers nommés "clean", "fclean", etc.
.PHONY: all clean fclean re bonus
