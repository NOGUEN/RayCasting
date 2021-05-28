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
	if (s->wallray.side == 0 && s->wallray.rayDirX > 0)
	{
		s->wallray.floorXWall = s->map.x;
		s->wallray.floorXWall = s->map.y + s->draw.wallX;
	}
	else if (s->wallray.side == 0 && s->wallray.rayDirX < 0)
	{
		s->wallray.floorXWall = s->map.x + 1.0;
		s->wallray.floorYWall = s->map.y + s->draw.wallX;
	}
	else if (s->wallray.side == 1 && s->wallray.rayDirX > 0)
	{
		s->wallray.floorXWall = s->map.x + s->draw.wallX;
		s->wallray.floorYWall = s->map.y;
	}
	else
	{
		s->wallray.floorXWall = s->map.x + s->draw.wallX;
		s->wallray.floorYWall = s->map.y + 1.0;
	}
}

void	last_casting2(t_all *s, int x)
{
	int y;

	y = s->draw.drawEnd + 1;
	s->dist.wall = s->wallray.perpWallDist;
	s->dist.player = 0.0;
	if (s->draw.drawEnd < 0)
		s->draw.drawEnd = s->win.y;
	while (y < s->win.y)
	{
		s->dist.current = s->win.y / (2.0 * y - s->win.y);
		s->win.buf[y][x] = s->tex.f;
		y++;
	}
}
