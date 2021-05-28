/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:48:25 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/21 18:19:38 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	last_casting1(t_all *s)
{
	if (s->wallray.side == 0 && s->wallray.raydirx > 0)
	{
		s->wallray.floorxwall = s->map.x;
		s->wallray.floorxwall = s->map.y + s->draw.wallx;
	}
	else if (s->wallray.side == 0 && s->wallray.raydirx < 0)
	{
		s->wallray.floorxwall = s->map.x + 1.0;
		s->wallray.floorywall = s->map.y + s->draw.wallx;
	}
	else if (s->wallray.side == 1 && s->wallray.raydirx > 0)
	{
		s->wallray.floorxwall = s->map.x + s->draw.wallx;
		s->wallray.floorywall = s->map.y;
	}
	else
	{
		s->wallray.floorxwall = s->map.x + s->draw.wallx;
		s->wallray.floorywall = s->map.y + 1.0;
	}
}

void	last_casting2(t_all *s, int x)
{
	int y;

	y = s->draw.drawend + 1;
	s->dist.wall = s->wallray.perpwalldist;
	s->dist.player = 0.0;
	if (s->draw.drawend < 0)
		s->draw.drawend = s->win.y;
	while (y < s->win.y)
	{
		s->dist.current = s->win.y / (2.0 * y - s->win.y);
		s->win.buf[y][x] = s->tex.f;
		y++;
	}
}
