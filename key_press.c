/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:00:15 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/22 14:43:49 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int keycode, t_all *s){
	if (keycode == KEY_ESC)
		tool_close(s, 1);
	if (keycode == KEY_W || keycode == 126)
		act_move(s, 1);
	else if (keycode == KEY_A || keycode == 123)
		act_rotate(s, 1);
	else if (keycode == KEY_S || keycode == 125)
		act_move(s, -1);
	else if (keycode == KEY_D || keycode == 124)
		act_rotate(s, -1);
	return (0);
}

void	act_move(t_all *s, double c){
	s->pos.x += c * (s->dir.x * s->speed.move);
	if (s->map.map[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
		s->pos.x -= c * (s->dir.x * s->speed.move);
	s->pos.y += c * (s->dir.y * s->speed.move);
	if (s->map.map[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '1')
		s->pos.y -= c * (s->dir.y * s->speed.move);
	if (s->map.map[(int)floor(s->pos.y)][(int)floor(s->pos.x)] == '2')
		s->map.map[(int)floor(s->pos.y)][(int)floor(s->pos.x)] = '0';
}

void	act_rotate(t_all *s, double c){
	double		oldDirX;
	double		oldPlaneX;

	oldDirX = s->dir.x;
	s->dir.x = s->dir.x * cos(c * s->speed.rotate)
		- s->dir.y * sin(c * s->speed.rotate);
	s->dir.y = oldDirX * sin(c * s->speed.rotate)
		+ s->dir.y * cos(c * s->speed.rotate);
	oldPlaneX = s->plane.x;
	s->plane.x = s->plane.x * cos(c * s->speed.rotate)
		- s->plane.y * sin(c *s->speed.rotate);
	s->plane.y = oldPlaneX * sin(c * s->speed.rotate)
		+ s->plane.y * cos(c * s->speed.rotate);
}
