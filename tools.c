/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:57:42 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/11 12:12:42 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		tool_space_skip(char *line, int *i){
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n') || 
			(line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
	return (1);
}

int		tool_atoi(char *line, int *i){
	int		n;

	n = 0;
	tool_space_skip(line, i);
	while (line[*i] >= '0' && line[*i] <= '9'){
		n = n * 10 + (line[*i] - 48);
		(*i)++;
	}
	return (n);
}

int		tool_strlen(char *line){
	int		n;

	n = 0;
	while(*line){
		n++;
		line++;
	}
	return (n);
}

