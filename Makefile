CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = pipex

NAME_BONUS = pipex_bonus

SRCS = pipex.c utils.c

SRCS_BONUS = pipex_bonus.c utils.c

all: $(NAME)

all_bonus: $(NAME_BONUS)

$(NAME):
	@make all -C $(LIBFT_DIR)
	@$(CC) -fPIE $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)
	@clear
	@echo "\033[1;36mprogram ready\033[0m"
	@echo "\n"

$(NAME_BONUS):
	@make all -C $(LIBFT_DIR)
	@$(CC) -fPIE $(CFLAGS) $(SRCS_BONUS) $(LIBFT) -o $(NAME_BONUS)
	@clear
	@echo "\033[1;36mprogram ready\033[0m"
	@echo "\n"

bonus : all_bonus
clean:
	make clean -C $(LIBFT_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all

fast: fclean all bonus clean
	make fclean -C $(LIBFT_DIR)
	clear
	@echo "\033[1;36mprogram ready\033[0m"
	@echo "\n"

.PHONY: all all_bonus clean fclean re fast
