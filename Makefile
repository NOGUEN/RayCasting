NAME = cub3D

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I.

MLX = mlx

LXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

SRCS = cub3d.c parse.c parse_tools.c tools.c parse_map.c parse_check.c map_check.c\
		convert_map.c\
		gnl/get_next_line.c gnl/get_next_line_utils.c \
		screen_setting.c casting.c \
		key_press.c last_casting.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(MLX) $(OBJS)
		$(CC) $(CFLAGS) -g -o $(NAME) $(OBJS) $(LXFLAGS)

$(MLX) : 
		@$(MAKE) -C mlx

clean:
	rm -rf *.o
	rm -rf gnl/*.o

fclean:		 clean
				rm -rf $(NAME)

re: fclean all

test: re
		./$(NAME) map/map.cub
