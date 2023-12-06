# Created by: mdoulahi
SRC = source/main.c

OBJ = $(SRC:.c=.o)

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a -lreadline 

%.o: %.c header/minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C libft
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all

run: re
	@./$(NAME)

push: fclean
	@git add .
	@git commit -m "push"
	@git push

.PHONY: all clean fclean re run