# Minishell Makefile with separate directory for object files

NAME = minishell
SRC_DIR = srcs
OBJ_DIR = objs

# Définition des sources par répertoire
SRC_LEXER = 		$(addprefix lexer/, lexer.c launch_handler.c operator_handler.c quote_handler2.c quote_handler.c redir_handler.c str_handler.c token_handler.c convert.c)
SRC_PARSER = 		$(addprefix parser/, pipe_parser.c quote_parser.c redirect_parser.c synthaxe_parser.c parser.c init.c)
#SRC_INIT_ENV = 		$(addprefix )
#SRC_SIGNALS = 		$(addprefix )
#SRC_BUILT_IN = 		$(addprefix )
SRC_EXEC = $(addprefix executor/, errors.c executor.c utils.c utils2.c ft_split.c)
#SRC_EXPANDER = $(addprefix )
#SRC_FREE_ALL = 		$(addprefix )
#SRC_INIT_EXEC = 	$(addprefix )*/

# Combinaison de tous les fichiers sources
SRCS = main.c \
      $(SRC_LEXER) \
       $(SRC_PARSER) \
	   	$(SRC_EXEC)

SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD
LIBFT = ./lib/lib42.a
YELLOW		= \033[1;33m
MAGENTA		= \033[1;35m
END			= \033[0m

# Directory creation commandz
DIR_DUP = mkdir -p $(@D)

# Nombre total de fichiers
TOTAL_FILES := $(words $(SRCS))

# Compteur de fichiers actuellement compilés
CURRENT_FILE := 0

# Main targets
all: 			$(NAME)
				@clear
				@echo "${MAGENTA}                                               ${END}"
				@echo "${MAGENTA}▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖▗▖ ▗▖▗▄▄▄▖▗▖   ▗▖   ${END}"
				@echo "${MAGENTA}▐▛▚▞▜▌  █  ▐▛▚▖▐▌  █  ▐▌   ▐▌ ▐▌▐▌   ▐▌   ▐▌   ${END}"
				@echo "${MAGENTA}▐▌  ▐▌  █  ▐▌ ▝▜▌  █   ▝▀▚▖▐▛▀▜▌▐▛▀▀▘▐▌   ▐▌   ${END}"
				@echo "${MAGENTA}▐▌  ▐▌▗▄█▄▖▐▌  ▐▌▗▄█▄▖▗▄▄▞▘▐▌ ▐▌▐▙▄▄▖▐▙▄▄▖▐▙▄▄▖${END}"
				@echo "${MAGENTA}                                               ${END}"

$(NAME): $(OBJS)
	@cd lib && make > /dev/null
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline
	@echo ""

# Fonction pour mettre à jour et afficher la barre de progression sur une seule ligne
define update_progress
    $(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
    $(eval PERCENT=$(shell echo $$((($(CURRENT_FILE)*100)/$(TOTAL_FILES)))))
	@printf "\r	   \033[0;32m["
    @printf "%-50s" "$$(printf '/%.0s' $$(seq 1 $$(($(PERCENT)/2))))"
	@printf "] %d%%\033[0m" $(PERCENT)
endef

# Rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(call update_progress)

# Include dependencies
-include $(DEPS)

# Function to update and display the progress bar on a single line
define clean_progress
	$(eval TOTAL_COUNT=$(words $(OBJS) $(DEPS) 1)) # +1 for the objs directory
	$(eval CURRENT_COUNT=$(shell echo $$(($(CURRENT_COUNT)+1))))
	$(eval PERCENT=$(shell echo $$((($(CURRENT_COUNT)*100)/$(TOTAL_COUNT)))))
	@printf "\r	   \033[0;33m["
	@printf "%-50s" "$$(printf '/%.0s' $$(seq 1 $$(($(PERCENT)/2))))"
	@printf "] %d%%\033[0m" $(PERCENT)
endef

# Other rules (clean, fclean, re)
clean:
	make clean -C lib/
	@clear
	$(eval CURRENT_COUNT=0)
	@$(foreach obj,$(OBJS) $(DEPS),rm -f $(obj); $(call clean_progress);)
	@rm -rf $(OBJ_DIR)
	@$(call clean_progress)
	@echo "${YELLOW}                                     ${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⡆⠀⠀clean⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡈⠻⠇⢸⣷⣶⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣶⣶⣿⣿⣿⣿⣿⣿⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⡿⠿⠟⠛⠋⣉⣤⣴⣶⡀⠀⠀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⣁⣠⣤⣤⣴⣶⣿⣿⠿⠿⠛⠋⣁⡀⠀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠛⠛⠋⣉⣉⣠⣤⣴⣶⣾⣿⣿⣷⡀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢦⣄⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠂⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡏⣿⣿⣿⣿⡿⣿⣿⢿⣿⡿⢿⣿⠻⡿⠛⠁⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⡿⠀⡟⢹⣿⡿⠃⠸⠿⠀⠙⠃⠀⠁⠀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}                                     ${END}";

# Fonction pour mettre à jour et afficher la barre de progression sur une seule ligne pour fclean
define fclean_progress
	$(eval TOTAL_COUNT=1) # Only for the minishell executable
	$(eval CURRENT_COUNT=$(shell echo $$(($(CURRENT_COUNT)+1))))
	$(eval PERCENT=$(shell echo $$((($(CURRENT_COUNT)*100)/$(TOTAL_COUNT)))))
	@printf "\r	   \033[0;33m["
	@printf "%-50s" "$$(printf '/%.0s' $$(seq 1 $$(($(PERCENT)/2))))"
	@printf "] %d%%\033[0m" $(PERCENT)
endef

# Other rules (clean, fclean, re)
fclean:
	$(eval CURRENT_COUNT=0)
	@$(MAKE) clean > /dev/null
	@rm -f $(NAME) lib/lib42.a
	@$(call clean_progress)
	@echo "${YELLOW}                                     ${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⡆⠀⠀Fclean⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡈⠻⠇⢸⣷⣶⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣶⣶⣿⣿⣿⣿⣿⣿⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⡿⠿⠟⠛⠋⣉⣤⣴⣶⡀⠀⠀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⣁⣠⣤⣤⣴⣶⣿⣿⠿⠿⠛⠋⣁⡀⠀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠛⠛⠋⣉⣉⣠⣤⣴⣶⣾⣿⣿⣷⡀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⠀⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢦⣄⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠂⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡏⣿⣿⣿⣿⡿⣿⣿⢿⣿⡿⢿⣿⠻⡿⠛⠁⠀⠀${END}";
	@echo "${YELLOW}⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⡿⠀⡟⢹⣿⡿⠃⠸⠿⠀⠙⠃⠀⠁⠀⠀⠀⠀⠀⠀${END}";
	@echo "${YELLOW}                                     ${END}";

re: fclean all

.PHONY: all clean fclean re
