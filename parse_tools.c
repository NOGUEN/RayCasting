/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:57:31 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/03 12:47:37 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		input_resolution(t_all *s, char *line, int *i){
	if (s->win.x != 0 || s->win.y != 0)
		return (-3);
	(*i)++;
	s->win.x = tool_atoi(line, i);
	s->win.y = tool_atoi(line, i);
	if (s->win.x > 2560)
		s->win.x = 2560;
	if (s->win.y > 1400)
		s->win.y = 1400;
	tool_space_skip(line, i);
	if (s->win.x <= 0 || s->win.y <= 0 || line[*i] != '\0')
		return (-4);
	return (0);
}

int		input_xpm(t_all *s, unsigned int **adr, char *file){
	int			fd;
	void		*img;
	int			tab[5];

	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	close(fd);
	img = mlx_xpm_file_to_image(s->mlx.ptr, file, &tab[0], &tab[1]);
	if (img == NULL || tab[0] != 64 || tab[1] != 64)
		return (-1);
	*adr = (unsigned int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
	free(img);
	return (0);
}

int		input_texture(t_all *s, unsigned int **adr, char *line, int *i){
	int		j;
	char	*file;

	if (*adr != NULL)
		return (-7);
	(*i) += 2;
	tool_space_skip(line, i);
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	if (!(file = malloc(sizeof(char) * (*i - j + 1))))
		return (-8);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		file[j++] = line[(*i)++];
	file[j] = '\0';
	j = input_xpm(s, adr, file);
	free(file);
	if (j == -1)
		return (-9);
	return (0);
}

int		input_color(unsigned int *color, char *line, int *i){
	int		r;
	int		g;
	int		b;

	if (*color == NONE)
		return (-5);
	(*i)++;
	r = tool_atoi(line, i);
	(*i)++;
	g = tool_atoi(line, i);
	(*i)++;
	b = tool_atoi(line, i);
	tool_space_skip(line, i);
	if (line[*i] != '\0' || r > 255 || g > 255 || b > 255)
		return (-5);
	*color = r * 256 * 256 + g * 256 + b;
	return (0);
}
