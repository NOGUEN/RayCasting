/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 09:03:07 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/03 13:02:35 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		input_line(t_all *s, char *line){
	int		i;

	i = 0;
	tool_space_skip(line, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		s->err.n = input_resolution(s, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		s->err.n = input_texture(s, &s->tex.n, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		s->err.n = input_texture(s, &s->tex.s, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		s->err.n = input_texture(s, &s->tex.e, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		s->err.n = input_texture(s, &s->tex.w, line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		s->err.n = input_texture(s, &s->tex.i, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		s->err.n = input_color(&s->tex.f, line, &i);
	else if (line[i] == '1')
		s->err.n = input_map();
	return (s->err.n);
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
}

