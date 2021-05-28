/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:37:03 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/28 18:03:57 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fc_casting(t_all *s)
{
	int		tx;
	int		ty;
	int		y;
	int		x;

	y = -1;
	x = -1;
	while (++y < s->win.y)
	{
		fc_setting(s, y);
		x = -1;
		while (++x < s->win.x)
		{
			s->fcray.cellx = (int)s->fcray.floorx;
			s->fcray.celly = (int)s->fcray.floory;
			tx = (int)(TEXWIDTH * (s->fcray.floorx -
						s->fcray.cellx)) & (TEXWIDTH - 1);
			ty = (int)(TEXHEIGHT * (s->fcray.floory -
						s->fcray.celly)) & (TEXHEIGHT - 1);
			s->fcray.floorx += s->fcray.floorstepx;
			s->fcray.floory += s->fcray.floorstepy;
			s->win.buf[y][x] = s->tex.c;
			s->win.buf[s->win.y - y - 1][x] = s->tex.c;
		}
	}
}

void	perform_dda(t_all *s)
{
	while (s->wallray.hit == 0)
	{
		if (s->wallray.sidedistx < s->wallray.sidedisty)
		{
			s->wallray.sidedistx += s->wallray.deltadistx;
			s->map.mapx += s->wallray.stepx;
			s->wallray.side = 0;
		}
		else
		{
			s->wallray.sidedisty += s->wallray.deltadisty;
			s->map.mapy += s->wallray.stepy;
			s->wallray.side = 1;
		}
		if (s->map.map[s->map.mapy][s->map.mapx] != '0')
			s->wallray.hit = 1;
	}
}

void	calculate(t_all *s)
{
	if (s->wallray.side == 0)
		s->wallray.perpwalldist = (s->map.mapx - s->pos.x +
				(1 - s->wallray.stepx) / 2) / s->wallray.raydirx;
	else
		s->wallray.perpwalldist = (s->map.mapy - s->pos.y +
				(1 - s->wallray.stepy) / 2) / s->wallray.raydiry;
	s->draw.lineheight = (int)(s->win.y / s->wallray.perpwalldist);
	s->draw.drawstart = -s->draw.lineheight / 2 + s->win.y / 2;
	if (s->draw.drawstart < 0)
		s->draw.drawstart = 0;
	s->draw.drawend = s->draw.lineheight / 2 + s->win.y / 2;
	if (s->draw.drawend >= s->win.y)
		s->draw.drawend = s->win.y - 1;
	if (s->wallray.side == 0)
	{
		s->draw.wallx = s->pos.y + s->wallray.perpwalldist *
			s->wallray.raydiry;
	}
	else
	{
		s->draw.wallx = s->pos.x + s->wallray.perpwalldist *
			s->wallray.raydirx;
	}
	s->draw.wallx -= floor(s->draw.wallx);
}

void	wall_casting(t_all *s)
{
	int		x;

	x = -1;
	while (++x < s->win.x)
	{
		wall_setting(s, x);
		step_setting(s);
		perform_dda(s);
		calculate(s);
		tex_setting(s, x);
		last_casting1(s);
		last_casting2(s, x);
	}
}

void	draw(t_all *s)
{
	int		y;
	int		x;

	y = -1;
	while (++y < s->win.y)
	{
		x = -1;
		while (++x < s->win.x)
		{
			s->img.data[y * s->win.x + x] = s->win.buf[y][x];
		}
	}
	mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);
}
