O = obj/
I = inc/
S = src/
L = lib/

include sources.mk
OBJ = $(SRC:$S%.c=$O%.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
INCFLAGS = -I$I

RM = rm -rf

.PHONY: all clean fclean re


# MAKERS
all: $(NAME)

$O:
	@mkdir -p $@

$(OBJ): | $O

$O%.o: $S%.c | $O
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	make bonus -C lib/libft/
	$(CC) $^ -L./lib/libft -lft -o $@
	./$(NAME) Makefile "ls -l" "grep l" src/main.c

# CLEANERS
clean:
	$(RM) $(O)
fclean: clean
	$(RM) $(NAME)
re: fclean all

fcleanlibft:
	make fclean -C lib/libft/
fcleanall: fclean fcleanlibft
reall: fcleanall all


