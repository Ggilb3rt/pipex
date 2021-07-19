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
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	#make bonus -C lib/libft/
	$(CC) $^ -o $@
	./$(NAME) ./tests/Nina "grep la" "grep ," ./tests/out
	cat ./tests/out
	rm ./tests/out
	./$(NAME) ./tests/Nina "" "" ./tests/out

# CLEANERS
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all
