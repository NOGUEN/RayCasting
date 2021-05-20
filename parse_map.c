/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:32:25 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/12 19:22:31 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_map(t_all *s){
	int		j;
<<<<<<< HEAD

	j = -1;
	if (!(s->map.map = malloc(sizeof(char *) * (s->map.y + 2))))
		return (-11);
	while (++j < s->map.y + 2){
		if (!(s->map.map[j] = malloc(sizeof(char) * (s->map.x + 1))))
			return (-11);
	}
	j = -1;
	while (++j < s->map.y + 2){
		s->map.map[j][0] = '\0';
	}
	return (0);
}

int		input_map(t_all *s, char *line, int *j){
	int		k;
	
	if (s->map.map == NULL){
		s->err.n = set_map(s);
	}
	k = 0;
	while (k < s->map.x){
		s->map.map[*j][k] = line[k * 2];
		k++;
	}
	*j = *j + 1;;
	return (0);
=======
	
	dfdfdfdf
>>>>>>> 016b8fbfeaf533cdb66017114c0a82df36fd6789
}
