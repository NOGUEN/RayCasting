MLX_NAME = mlx
MLX_DIR = ./mlx

all:
	gcc -L$(MLX_DIR) -l$(MLX_NAME) -framework OpenGL -framework AppKit main.c -o test_load.out
	./test_load.out

clean:
	rm -rf *.out
