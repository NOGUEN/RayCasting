/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:08:02 by nogeun            #+#    #+#             */
/*   Updated: 2021/06/01 14:32:14 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d_init3(t_all *s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < s->win.y + 1)
	{
		while (j < s->win.x + 1)
		{
			s->win.buf[i][j] = 0;
			j++;
		}
		i++;
	}
	s->win.ptr = mlx_new_window(s->mlx.ptr, s->win.x, s->win.y, "cub3D");
	s->img.ptr = mlx_new_image(s->mlx.ptr, s->win.x, s->win.y);
	s->img.data = (int *)mlx_get_data_addr(s->img.ptr, &s->img.bpp,
			&s->img.size_l, &s->img.endian);
	mlx_hook(s->win.ptr, X_EVENT_KEY_PRESS, 0, &key_press, s);
	mlx_hook(s->win.ptr, 17, 0, &tool_close, s);
	mlx_loop_hook(s->mlx.ptr, &main_loop, s);
	mlx_loop(s->mlx.ptr);
}

void	cub3d_init2(t_all *s, char **argv)
{
	int i;
	int j;

	i = 0;
	j = 0;
	s->tex.n = NULL;
	s->tex.e = NULL;
	s->tex.w = NULL;
	s->tex.s = NULL;
	s->speed.rotate = 0.1;
	s->speed.move = 0.1;
	s->win.x = 1080;
	s->win.y = 720;
	s->mlx.ptr = mlx_init();
	if (parse(s, argv[1]) == -1)
		exit(0);
	s->win.buf = malloc(sizeof(int *) * s->win.y + 1);
	while (i < s->win.y + 1)
	{
		s->win.buf[i] = malloc(sizeof(int) * s->win.x + 1);
		i++;
	}
	cub3d_init3(s);
}

void	cub3d_init(t_all *s, char **argv)
{
	s->err.p = 0;
	s->err.n = 0;
	s->win.x = 0;
	s->win.y = 0;
	s->map.x = 0;
	s->map.y = 0;
	s->map.map = NULL;
	s->pos.x = 5.0;
	s->pos.y = 2.0;
	s->dir.x = 0.0;
	s->dir.y = 0.0;
	s->plane.x = 0.0;
	s->plane.y = 0.0;
	cub3d_init2(s, argv);
}

int		main_loop(t_all *s)
{
	fc_casting(s);
	calculate(s);
	wall_casting(s);
	draw(s);
	return (0);
}

int		main(int argc, char **argv)
{
	t_all	s;

	if (argc == 2 && name_check(argv[1], "cub"))
		cub3d_init(&s, argv);
	else
		write(2, "Error : Invalid arguments\n", 26);
	return (0);
}
