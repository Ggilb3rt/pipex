O = obj/
I = inc/
S = src/

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

$O%.o: $S%.c $(HEADERS) | $O
	@printf "Création des objets en cours : $@ ...\n"
	@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@printf "Compilation ...\n"
	@$(CC) $^ -o $@
	@printf "Have fun :-)\n"

# CLEANERS
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all
