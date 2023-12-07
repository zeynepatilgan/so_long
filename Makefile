NAME	=	so_long
CC		=	gcc -g
CFLAGS	=	-Wall -Werror -Wextra
LFLAGS	=	-Lminilibx -lmlx -framework OpenGL -framework AppKit libft.a

SOURCES =	src/close_game.c \
            src/events.c \
            src/main.c \
            src/map_checkers.c \
            src/mlx_create.c \
            src/path_checkers.c \
			src/hook.c \
			src/map_checkers_2.c 

OBJ = $(SOURCES:.c=.o)

all		:	$(NAME)

$(NAME)	:	mdir $(OBJ)
		$(CC) $(CFLAGS) $(LFLAGS) $(SOURCES) -o $(NAME)

mdir	:
		@make -C libft
		@make -C minilibx

clean	:
		@make -C libft	clean
		@make -C minilibx		clean
		@rm -f $(OBJ)

fclean :
		@make -C libft fclean
		@make -C minilibx	clean
		@rm	-f $(NAME) $(OBJ)
		rm -rf libft.a

re		:	fclean all

.PHONY	:	all $(NAME) mdir clean fclean re
