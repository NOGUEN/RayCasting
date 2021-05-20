/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:37:03 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/20 20:42:09 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fc_casting(t_all *s){
	int		cellX;
	int		cellY;
	int		tx;
	int		ty;

	for (int y = 0; y < s->win.y; y++){
		fc_setting(s, y);
		for (int x = 0; x < s->win.x; x++){
			cellX = (int)s->fcray.floorX;
			cellY = (int)s->fcray.floorY;
			tx = (int)(TEXWIDTH * (s->fcray.floorX - cellX)) & (TEXWIDTH - 1);
			ty = (int)(TEXHEIGHT * (s->fcray.floorY - cellY)) & (TEXHEIGHT - 1);
			s->fcray.floorX += s->fcray.floorStepX;
			s->fcray.floorY += s->fcray.floorStepY;
			s->win.buf[y][x] = (s->tex.c >> 1) & 8355711;
			s->win.buf[s->win.y - y - 1][x] = (s->tex.f >> 1) & 83555711;
		}
	}
}

void	perform_dda(t_all *s){
	while (s->wallray.hit == 0){
		if (s->wallray.sideDistX < s->wallray.sideDistY){
			s->wallray.sideDistX += s->wallray.deltaDistX;
			s->map.mapX += s->wallray.stepX;
			s->wallray.side = 0;
		} else {
			s->wallray.sideDistY += s->wallray.deltaDistY;
			s->map.mapY += s->wallray.stepY;
			s->wallray.side = 1;
		}
		if (s->map.map[s->map.mapY][s->map.mapX] > 48)
			s->wallray.hit = 1;
	}
}

void	calculate(t_all *s){
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
	if (s->wallray.side == 0){
		s->draw.wallX = s->pos.y + s->wallray.perpWallDist *
			s->wallray.rayDirY;
	} else {
		s->draw.wallX = s->pos.x + s->wallray.perpWallDist *
			s->wallray.rayDirX;
	}
	s->draw.wallX -= floor(s->draw.wallX);
}

void	wall_casting(t_all *s){
	for (int x = 0; x < s->win.x; x++){
		wall_setting(s, x);
		step_setting(s);
		perform_dda(s);
		calculate(s);
		tex_setting(s, x);
		last_casting1(s);
		last_casting2(s, x);
	}
}

void	draw(t_all *s){
	for (int y = 0; y < s->win.y; y++){
		for (int x = 0; x < s->win.x; x++){
			s->img.data[y * s->win.x + x] = s->win.buf[y][x];
		}
	}
	mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);
}
