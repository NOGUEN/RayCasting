MLX_NAME = mlx
MLX_DIR = ./mlx

all:

all:	
	gcc -L ./mlx -lmlx -framework OpenGL -framework AppKit main.c -o test_load.out 
	./test_load.out	

clean:
	rm -rf *.out
