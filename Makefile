NAME = count_page_fault

SRC = main.c

OBJ = $(SRC:%.c=%.o)

LIBFT = libft/libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -Iinclude

all : $(NAME)

$(NAME) : $(OBJ)
	make -C ./libft
	$(CC) $(CFLAGS) $^ $(LIBFT) -o $@

clean :
	make clean -C libft
	rm -rf $(OBJ)

fclean : clean
	make fclean -C libft
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
