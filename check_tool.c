/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:48:43 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/27 15:59:37 by nogeun           ###   ########.fr       */
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

int		save_check(char *arg, char *save){
	int		i;

	i = 0;
	while (arg[i] == save[i]){
		if (arg[i] == '\0' && save[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}


