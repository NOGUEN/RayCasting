/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:48:43 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/24 15:06:56 by nogeun           ###   ########.fr       */
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

void	print_all(t_all *s){
	for (int j = 0; j < s->map.y; j++){
		for (int i = 0; i < s->map.x / 2 + 1; i++){
			char c = s->map.map[j][i];
			write(2, &c, 1);
		}
		write(2, "\n", 1);
	}
}

