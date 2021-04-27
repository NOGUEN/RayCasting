/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 09:03:07 by nogeun            #+#    #+#             */
/*   Updated: 2021/04/28 08:18:02 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		input_line(t_all *s, char *line){
	
}

void	parse(t_all *s, char *cub){
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	fd = open(cub, O_RDONLY);
	if (fd == -1)
		write(2, "Open File Error", 15);
	while (ret == 1){
		ret = get_next_line(fd, &line);
		if (input_line(s, line) == -1)
			ret = -1;
		free(line);
	}
	close(fd);
	if (ret == -1)
		write(2, "Error", 5);
	ft
}

