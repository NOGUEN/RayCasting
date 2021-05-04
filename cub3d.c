#include "cub3d.h"

int		init_cube(t_all s, char *cub, int bmp){
	t_pos	pos;
	t_dir	dir;

	pos.x = 0;
	pos.y = 0;
	dir.x = 0;
	dir.y = 0;
	s.pos = pos;
	s.dir = dir;
	s.mlx.ptr = mlx_init();
}

int		init_graphic(t_all s, char *cub, int bmp){
	t_map	*map;
	t_tex	tex;

	map = malloc(sizeof(t_map));
	tex.n = NULL;
	tex.s = NULL;
	tex.e = NULL;
	tex.w = NULL;
	tex.i = NULL;
}

void	init(char *cub, int bmp){
	t_all	s;
	t_mlx	mlx;
	t_win	win;
	t_img	img;
	t_err	err;

	mlx.ptr = NULL;
	win.ptr = NULL;
	img.ptr = NULL;
	img.adr = NULL;
}


int main(int argc, char** argv) {
	t_all	s;
	int i;
	
	s.mlx.ptr = mlx_init();
	s.win.x = 0;
	s.win.y = 0;
	parse(&s, argv[1]);
	printf("%d\n", s.win.x);
	printf("%d\n", s.win.y);
	printf("%p\n", s.tex.n);
	printf("%p\n", s.tex.s);
	printf("%p\n", s.tex.e);
	printf("%p\n", s.tex.w);
	printf("%p\n", s.tex.i);
	printf("%d\n", s.tex.f);
	printf("%s\n", argv[1]);
	
	i = argc;
	return (0);
}
