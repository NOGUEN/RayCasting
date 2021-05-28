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
			s->fcray.cellX = (int)s->fcray.floorX;
			s->fcray.cellY = (int)s->fcray.floorY;
			tx = (int)(TEXWIDTH * (s->fcray.floorX -
						s->fcray.cellX)) & (TEXWIDTH - 1);
			ty = (int)(TEXHEIGHT * (s->fcray.floorY -
						s->fcray.cellY)) & (TEXHEIGHT - 1);
			s->fcray.floorX += s->fcray.floorStepX;
			s->fcray.floorY += s->fcray.floorStepY;
			s->win.buf[y][x] = s->tex.c;
			s->win.buf[s->win.y - y - 1][x] = s->tex.c;
		}
	}
}

void	perform_dda(t_all *s)
{
	while (s->wallray.hit == 0)
	{
		if (s->wallray.sideDistX < s->wallray.sideDistY)
		{
			s->wallray.sideDistX += s->wallray.deltaDistX;
			s->map.mapX += s->wallray.stepX;
			s->wallray.side = 0;
		}
		else
		{
			s->wallray.sideDistY += s->wallray.deltaDistY;
			s->map.mapY += s->wallray.stepY;
			s->wallray.side = 1;
		}
		if (s->map.map[s->map.mapY][s->map.mapX] != '0')
			s->wallray.hit = 1;
	}
}

void	calculate(t_all *s)
{
	if (s->wallray.side == 0)
		s->wallray.perpWallDist = (s->map.mapX - s->pos.x +
				(1 - s->wallray.stepX) / 2) / s->wallray.rayDirX;
	else
		s->wallray.perpWallDist = (s->map.mapY - s->pos.y +
				(1 - s->wallray.stepY) / 2) / s->wallray.rayDirY;
	s->draw.lineHeight = (int)(s->win.y / s->wallray.perpWallDist);
	s->draw.drawStart = -s->draw.lineHeight / 2 + s->win.y / 2;
	if (s->draw.drawStart < 0)
		s->draw.drawStart = 0;
	s->draw.drawEnd = s->draw.lineHeight / 2 + s->win.y / 2;
	if (s->draw.drawEnd >= s->win.y)
		s->draw.drawEnd = s->win.y - 1;
	if (s->wallray.side == 0)
	{
		s->draw.wallX = s->pos.y + s->wallray.perpWallDist *
			s->wallray.rayDirY;
	}
	else
	{
		s->draw.wallX = s->pos.x + s->wallray.perpWallDist *
			s->wallray.rayDirX;
	}
	s->draw.wallX -= floor(s->draw.wallX);
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
