NAME = lib42.a
FT_PRINTF = $(addprefix src/ft_, white_space.c)
OBJS_FT = ${FT_PRINTF:.c=.o}
OBJ = $(OBJS_FT)
CC = gcc
FLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
