/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:08:02 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/24 17:19:05 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main_loop(t_all *s){
	fc_casting(s);
	calculate(s);
	wall_casting(s);
	draw(s);
	return (0);
}

int main(int argc, char** argv) {
	t_all	s;
	int i;
	int j;
	
	i = 0;
	j = 0;
	s.err.p = 0;
	s.err.n = 0;
	s.win.x = 0;
	s.win.y = 0;
	s.map.x = 0;
	s.map.y = 0;
	s.map.map = NULL;
	s.pos.x = 5.0;
	s.pos.y = 2.0;
	s.dir.x = 0.0;
	s.dir.y = 0.0;
	s.plane.x = 0.0;
	s.plane.y = 0.0;
	s.tex.n = NULL;
	s.tex.e = NULL;
	s.tex.w = NULL;
	s.tex.s = NULL;
	s.tex.i = NULL;
	s.speed.rotate = 0.1;
	s.speed.move = 0.1;
	parse(&s, argv[1]);
	
	s.win.buf = malloc(sizeof(int *) * s.win.y + 1);
	while (i < s.win.y + 1){
		s.win.buf[i] = malloc(sizeof(int) * s.win.x + 1);
		i++;
	}
	i = 0;
	while (i < s.win.y + 1){
		while (j < s.win.x + 1){
			s.win.buf[i][j] = 0;
			j++;
		}
		i++;
	}
	i = 0;
    s.mlx.ptr = mlx_init();
    s.win.ptr = mlx_new_window(s.mlx.ptr, s.win.x, s.win.y, "cub3D");

    s.img.ptr = mlx_new_image(s.mlx.ptr, s.win.x, s.win.y);
    s.img.data = (int *)mlx_get_data_addr(s.img.ptr, &s.img.bpp,
            &s.img.size_l, &s.img.endian);

    if (argc == 3 && name_check(argv[1], "cub") && save_check(argv[2], "--save")){
        main_loop(&s);
        save_bmp(&s);
    }
    
    mlx_hook(s.win.ptr, X_EVENT_KEY_PRESS, 0, &key_press, &s);
    mlx_loop_hook(s.mlx.ptr, &main_loop, &s);
    mlx_loop(s.mlx.ptr);
	i = argc;
}
