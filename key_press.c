/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:00:15 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/20 19:06:43 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int keycode, t_all *s){
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_W || keycode == 126)
		key_press_W(keycode, s);
	else if (keycode == KEY_A || keycode == 123)
		key_press_A(keycode, s);
	else if (keycode == KEY_S || keycode == 125)
		key_press_S(keycode, s);
	else if (keycode == KEY_D || keycode == 124)
		key_press_D(keycode, s);
	return (0);
}

int		key_press_W(int keycode, t_all *s){
	if (keycode == KEY_W || keycode == 126){
		if (s->map.map[(int)(s->pos.x + s->dir.x * s->speed.move)]
				[(int)(s->pos.y + s->dir.y * s->speed.move)] >= 48){
			s->pos.x += s->dir.x * s->speed.move;
			s->pos.y += s->dir.y * s->speed.move;
		}
	}
	return (0);
}

int        key_press_A(int keycode, t_all *s){
    if (keycode == KEY_A || keycode == 123){
        double    oldDirX;
        double    oldPlaneX;

        oldDirX = s->dir.x;
        oldPlaneX = s->plane.x;
        s->dir.x = s->dir.x * cos(s->speed.rotate)
            - s->dir.y * sin(s->speed.rotate);
        s->dir.y = oldDirX * sin(s->speed.rotate)
            + s->dir.y * cos(s->speed.rotate);
        s->plane.x = s->plane.x * cos(s->speed.rotate)
            - s->plane.y * sin(s->speed.rotate);
        s->plane.y = oldPlaneX * sin(s->speed.rotate)
            + s->plane.y * cos(s->speed.rotate);
    }
	return (0);
}

int        key_press_S(int keycode, t_all *s){
    if (keycode == KEY_S || keycode == 125){
        if (s->map.map[(int)(s->pos.x - s->dir.x * s->speed.move)]
                [(int)(s->pos.y - s->dir.y * s->speed.move)] >= 48 ){
            s->pos.x -= s->dir.x * s->speed.move;
            s->pos.y -= s->dir.y * s->speed.move;
        }
    }
	return (0);
}

int        key_press_D(int keycode, t_all *s){
    if (keycode == KEY_D || keycode == 124){
		double	oldDirX;
		double	oldPlaneX;

		oldDirX = s->dir.x;
		oldPlaneX = s->plane.x;
		s->dir.x = s->dir.x * cos(-s->speed.rotate)
			- s->dir.y * sin(-s->speed.rotate);
		s->dir.y = oldDirX * sin(-s->speed.rotate)
			+ s->dir.y * cos(-s->speed.rotate);
		s->plane.x = s->plane.x * cos(-s->speed.rotate)
			- s->plane.y * sin(-s->speed.rotate);
		s->plane.y = oldPlaneX * sin(-s->speed.rotate)
			+ s->plane.y * cos(-s->speed.rotate);
	}
	return (0);
}
