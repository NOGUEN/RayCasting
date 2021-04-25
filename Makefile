MLX_NAME = mlx
MLX_DIR = ./mlx

all:	
	gcc -L$(MLX_DIR) -l$(MLX_NAME) -framework OpenGL -framework AppKit main.c -o cub3D.out
	./cub3D.out

clean:
	rm -rf *.out
