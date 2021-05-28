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
	s->fcray.raydirx0 = s->dir.x - s->plane.x;
	s->fcray.raydiry0 = s->dir.y - s->plane.y;
	s->fcray.raydirx1 = s->dir.x + s->plane.x;
	s->fcray.raydiry1 = s->dir.y + s->plane.y;
	s->fcray.p = y - s->win.y / 2;
	s->pos.z = 0.5 * s->win.y;
	s->fcray.rowdistance = s->pos.z / s->fcray.p;
	s->fcray.floorstepx = s->fcray.rowdistance *
		(s->fcray.raydirx1 - s->fcray.raydirx0) / s->win.x;
	s->fcray.floorstepy = s->fcray.rowdistance *
		(s->fcray.raydiry1 - s->fcray.raydiry0) / s->win.x;
	s->fcray.floorx = s->pos.x + s->fcray.rowdistance * s->fcray.raydirx0;
	s->fcray.floory = s->pos.y + s->fcray.rowdistance * s->fcray.raydiry0;
}

void	wall_setting(t_all *s, int x)
{
	s->wallray.camerax = 2 * x / (double)s->win.x - 1;
	s->wallray.raydirx = s->dir.x + s->plane.x * s->wallray.camerax;
	s->wallray.raydiry = s->dir.y + s->plane.y * s->wallray.camerax;
	s->map.mapx = (int)s->pos.x;
	s->map.mapy = (int)s->pos.y;
	s->wallray.deltadistx = fabs(1 / s->wallray.raydirx);
	s->wallray.deltadisty = fabs(1 / s->wallray.raydiry);
	s->wallray.hit = 0;
}

void	step_setting(t_all *s)
{
	if (s->wallray.raydirx < 0)
	{
		s->wallray.stepx = -1;
		s->wallray.sidedistx = (s->pos.x - s->map.mapx) *
			s->wallray.deltadistx;
	}
	else
	{
		s->wallray.stepx = 1;
		s->wallray.sidedistx = (s->map.mapx + 1.0 - s->pos.x) *
			s->wallray.deltadistx;
	}
	if (s->wallray.raydiry < 0)
	{
		s->wallray.stepy = -1;
		s->wallray.sidedisty = (s->pos.y - s->map.mapy) *
			s->wallray.deltadisty;
	}
	else
	{
		s->wallray.stepy = 1;
		s->wallray.sidedisty = (s->map.mapy + 1.0 - s->pos.y) *
			s->wallray.deltadisty;
	}
}

void	tex_setting(t_all *s, int x)
{
	int		y;

	y = s->draw.drawstart;
	s->draw.texx = (int)(s->draw.wallx * (double)TEXWIDTH);
	if (s->wallray.side == 0 && s->wallray.raydirx > 0)
		s->draw.texx = TEXWIDTH - s->draw.texx - 1;
	if (s->wallray.side == 1 && s->wallray.raydiry < 0)
		s->draw.texx = TEXWIDTH - s->draw.texx - 1;
	s->wallray.step = 1.0 * TEXHEIGHT / s->draw.lineheight;
	s->wallray.texpos = (s->draw.drawstart - s->win.y / 2 +
			s->draw.lineheight / 2) * s->wallray.step;
	while (++y < s->draw.drawend)
	{
		s->draw.texy = (int)s->wallray.texpos & (TEXHEIGHT - 1);
		s->wallray.texpos += s->wallray.step;
		dirtex_setting(s);
		s->win.buf[y][x] = s->draw.color;
	}
}

void	dirtex_setting(t_all *s)
{
	if (s->wallray.raydiry < 0 && s->wallray.side == 1)
		s->draw.color = s->tex.e[TEXWIDTH * s->draw.texy + s->draw.texx];
	else if (s->wallray.raydiry > 0 && s->wallray.side == 1)
		s->draw.color = s->tex.w[TEXWIDTH * s->draw.texy + s->draw.texx];
	else if (s->wallray.raydirx < 0 && s->wallray.side == 0)
		s->draw.color = s->tex.s[TEXWIDTH * s->draw.texy + s->draw.texx];
	else if (s->wallray.raydirx > 0 && s->wallray.side == 0)
		s->draw.color = s->tex.n[TEXWIDTH * s->draw.texy + s->draw.texx];
	if (s->wallray.side == 1)
		s->draw.color = (s->draw.color >> 1) & 8355711;
}
