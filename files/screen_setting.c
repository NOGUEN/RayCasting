/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 19:32:36 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/20 17:15:59 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fc_setting(t_all *s, int y)
{
	s->fcray.rayDirX0 = s->dir.x - s->plane.x;
	s->fcray.rayDirY0 = s->dir.y - s->plane.y;
	s->fcray.rayDirX1 = s->dir.x + s->plane.x;
	s->fcray.rayDirY1 = s->dir.y + s->plane.y;
	s->fcray.p = y - s->win.y / 2;
	s->pos.z = 0.5 * s->win.y;
	s->fcray.rowDistance = s->pos.z / s->fcray.p;
	s->fcray.floorStepX = s->fcray.rowDistance *
		(s->fcray.rayDirX1 - s->fcray.rayDirX0) / s->win.x;
	s->fcray.floorStepY = s->fcray.rowDistance *
		(s->fcray.rayDirY1 - s->fcray.rayDirY0) / s->win.x;
	s->fcray.floorX = s->pos.x + s->fcray.rowDistance * s->fcray.rayDirX0;
	s->fcray.floorY = s->pos.y + s->fcray.rowDistance * s->fcray.rayDirY0;
}

void	wall_setting(t_all *s, int x)
{
	s->wallray.cameraX = 2 * x / (double)s->win.x - 1;
	s->wallray.rayDirX = s->dir.x + s->plane.x * s->wallray.cameraX;
	s->wallray.rayDirY = s->dir.y + s->plane.y * s->wallray.cameraX;
	s->map.mapX = (int)s->pos.x;
	s->map.mapY = (int)s->pos.y;
	s->wallray.deltaDistX = fabs(1 / s->wallray.rayDirX);
	s->wallray.deltaDistY = fabs(1 / s->wallray.rayDirY);
	s->wallray.hit = 0;
}

void	step_setting(t_all *s)
{
	if (s->wallray.rayDirX < 0)
	{
		s->wallray.stepX = -1;
		s->wallray.sideDistX = (s->pos.x - s->map.mapX) *
			s->wallray.deltaDistX;
	}
	else
	{
		s->wallray.stepX = 1;
		s->wallray.sideDistX = (s->map.mapX + 1.0 - s->pos.x) *
			s->wallray.deltaDistX;
	}
	if (s->wallray.rayDirY < 0)
	{
		s->wallray.stepY = -1;
		s->wallray.sideDistY = (s->pos.y - s->map.mapY) *
			s->wallray.deltaDistY;
	}
	else
	{
		s->wallray.stepY = 1;
		s->wallray.sideDistY = (s->map.mapY + 1.0 - s->pos.y) *
			s->wallray.deltaDistY;
	}
}

void	tex_setting(t_all *s, int x)
{
	int		y;

	y = s->draw.drawStart;
	s->draw.texX = (int)(s->draw.wallX * (double)TEXWIDTH);
	if (s->wallray.side == 0 && s->wallray.rayDirX > 0)
		s->draw.texX = TEXWIDTH - s->draw.texX - 1;
	if (s->wallray.side == 1 && s->wallray.rayDirY < 0)
		s->draw.texX = TEXWIDTH - s->draw.texX - 1;
	s->wallray.step = 1.0 * TEXHEIGHT / s->draw.lineHeight;
	s->wallray.texPos = (s->draw.drawStart - s->win.y / 2 +
			s->draw.lineHeight / 2) * s->wallray.step;
	while (++y < s->draw.drawEnd)
	{
		s->draw.texY = (int)s->wallray.texPos & (TEXHEIGHT - 1);
		s->wallray.texPos += s->wallray.step;
		dirtex_setting(s);
		s->win.buf[y][x] = s->draw.color;
	}
}

void	dirtex_setting(t_all *s)
{
	if (s->wallray.rayDirY < 0 && s->wallray.side == 1)
		s->draw.color = s->tex.e[TEXWIDTH * s->draw.texY + s->draw.texX];
	else if (s->wallray.rayDirY > 0 && s->wallray.side == 1)
		s->draw.color = s->tex.w[TEXWIDTH * s->draw.texY + s->draw.texX];
	else if (s->wallray.rayDirX < 0 && s->wallray.side == 0)
		s->draw.color = s->tex.s[TEXWIDTH * s->draw.texY + s->draw.texX];
	else if (s->wallray.rayDirX > 0 && s->wallray.side == 0)
		s->draw.color = s->tex.n[TEXWIDTH * s->draw.texY + s->draw.texX];
	if (s->wallray.side == 1)
		s->draw.color = (s->draw.color >> 1) & 8355711;
}
