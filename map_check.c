/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:48:43 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/22 16:56:02 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		find_start_point(t_all *s, int *i, int *j){
	while (s->map.map[*j][*i]){
		if (s->map.map[*j][*i] == '1')
			return (*i);
		else
			*i = *i + 1;
	}
	return (-1);
}

void	convert_wall(t_all *s, int *i, int *j){
	s->map.map[*j][*i] = 'w';
	if (*i + 1 < s->map.x / 2 + 1){
		*i = *i + 1;
		if (s->map.map[*j][*i] == '1'){
			convert_wall(s, i, j);
		}
	}
	if (*j + 1 < s->map.y){
		*j = *j + 1;
		if (s->map.map[*j][*i] == '1'){
			convert_wall(s, i, j);
		}
	}
	if (*i - 1 >= 0){
		*i = *i - 1;
		if (s->map.map[*j][*i] == '1'){
			convert_wall(s, i, j);
		}
	}
	if (*j - 1 >= 0){
		*j = *j - 1;
		if (s->map.map[*j][*i] == '1'){
			convert_wall(s, i, j);
		}
	}
}

void	print_all(t_all *s){
	for (int j = 0; j < s->map.y; j++){
		for (int i = 0; i < s->map.x / 2 + 1; i++){
			char c = s->map.map[j][i];
			write(2, &c, 1);
		}
		write(2, "\n", 1);
	}
}

