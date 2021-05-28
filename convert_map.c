/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:55:54 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/24 14:09:18 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	convert_wall_right(t_all *s, int *i, int *j)
{
	if (*i + 1 < s->map.x / 2 + 1 && s->map.map[*j][*i + 1] == '1')
	{
		*i = *i + 1;
		convert_wall(s, i, j);
	}
}

void	convert_wall_down(t_all *s, int *i, int *j)
{
	if (*j + 1 < s->map.y && s->map.map[*j + 1][*i] == '1')
	{
		*j = *j + 1;
		convert_wall(s, i, j);
	}
}

void	convert_wall_left(t_all *s, int *i, int *j)
{
	if (*i - 1 > -1 && s->map.map[*j][*i - 1] == '1')
	{
		*i = *i - 1;
		convert_wall(s, i, j);
	}
}

void	convert_wall_up(t_all *s, int *i, int *j)
{
	if (*j - 1 > -1 && s->map.map[*j - 1][*i] == '1')
	{
		*j = *j - 1;
		convert_wall(s, i, j);
	}
}

void	convert_wall(t_all *s, int *i, int *j)
{
	s->map.map[*j][*i] = 'w';
	convert_wall_left(s, i, j);
	convert_wall_down(s, i, j);
	convert_wall_right(s, i, j);
	convert_wall_up(s, i, j);
}
