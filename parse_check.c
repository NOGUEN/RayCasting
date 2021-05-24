/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:53:03 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/24 15:06:48 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		name_check(char *arg, char *ext){
	int	i;

	i = 0;
	while (arg[i] != '\0')
		i++;
	if ((i > 4 && arg[i - 1] == ext[2] && arg[i - 2] == ext[1])
		&& (arg[i - 3] == ext[0] && arg[i - 4] == '.'))
		return (1);
	return (0);
}

int		map_check(t_all *s){
	int		i;
	int		j;
	int		start_i;
	int		start_j;

	i = 0;
	j = 0;
	if ((i = find_start_point(s, &i, &j)) == -1)
		return (-1);
	start_i = i;
	start_j = j;
	convert_wall(s, &i, &j);
	if (start_i + 1 == i && start_j == j)
		return (0);
	print_all(s);
	return (-1);
}

void	set_direction(t_all *s, char c){
	s->dir.x = (c == 'N' || c == 'S') ? 1.0 : 0.0;
	s->dir.x *= (c == 'N') ? -1 : 1;
	s->dir.y = (c == 'W' || c == 'E') ? 1.0 : 0.0;
	s->dir.y *= (c== 'W') ? -1 : 1;
	s->plane.y = (c == 'N' || c == 'S') ? 0.66 : 0.0;
	s->plane.y *= (c == 'S') ? -1 : 1 ;
	s->plane.x = (c == 'W' || c == 'E') ? 0.66 : 0.0;
	s->plane.x *= (c == 'W') ? -1 : 1;
}

void	pos_check(t_all *s){
	char	c;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++i < s->map.y){
		while (++j < s->map.x){
			c = s->map.map[i][j];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W'){
				s->map.map[i][j] = '0';
				s->pos.y = (double)i + 0.5;
				s->pos.x = (double)j + 0.5;
				set_direction(s, c);
				s->err.p++;
			}
		}
		j = -1;
	}
}

int		parse_check(t_all *s){
	if (s->win.x <= 0 || s->win.y <= 0)
		return (tool_error(-14));
	else if ((s->tex.n == NULL || s->tex.s == NULL || s->tex.e == NULL)
			|| (s->tex.w == NULL || s->tex.i == NULL))
		return (tool_error(-15));
	else if (s->tex.c == NONE || s->tex.f == NONE)
		return (tool_error(-16));
	else if (s->err.p == 0)
		return (tool_error(-17));
	else if (s->err.p > 1)
		return (tool_error(-18));
	else if (map_check(s) == -1)
		return (tool_error(-19));
	return (1);
}
