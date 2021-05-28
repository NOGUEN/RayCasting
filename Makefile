NAME = cub3D

CC = gcc

CFLAGS = -O3 -Wall -Wextra -Werror -I.

MLX = mlx

LXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

SRCS =	file/cub3d.c\
		file/parse.c\
		file/parse_tools.c\
		file/tools.c\
		file/parse_map.c\
		file/parse_check.c\
		file/check_tool.c\
		file/convert_map.c\
		gnl/get_next_line.c\
		gnl/get_next_line_utils.c\
		file/screen_setting.c\
		file/casting.c\
		file/key_press.c\
		file/last_casting.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(MLX) $(OBJS)
		$(CC) $(CFLAGS) -g -o $(NAME) $(OBJS) $(LXFLAGS)

$(MLX) : 
		@$(MAKE) -C mlx

clean:
	rm -rf $(OBJS)

fclean:		 clean
				rm -rf $(NAME)

re: fclean all

test: re
		./$(NAME) map/map.cub
