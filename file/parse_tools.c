/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:57:31 by nogeun            #+#    #+#             */
/*   Updated: 2021/06/01 13:06:35 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		input_xpm(t_all *s, int **adr, char *file)
{
	int			fd;
	int			y;
	int			x;

	*adr = malloc(sizeof(int) * (TEXWIDTH * TEXHEIGHT));
	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	close(fd);
	s->img.ptr =
		mlx_xpm_file_to_image(s->mlx.ptr, file, &s->img.width, &s->img.height);
	if (s->img.ptr == NULL || s->img.width != 64 || s->img.height != 64)
		return (-1);
	s->img.data = (int *)mlx_get_data_addr(s->img.ptr,
			&s->img.bpp, &s->img.size_l, &s->img.endian);
	y = -1;
	while (++y < 64)
	{
		x = -1;
		while (++x < 64)
		{
			(*adr)[64 * y + x] = s->img.data[64 * y + x];
		}
	}
	mlx_destroy_image(s->mlx.ptr, s->img.ptr);
	return (0);
}

int		input_texture(t_all *s, int **adr, char *line, int *i)
{
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

int		input_color(unsigned int *color, char *line, int *i)
{
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
		return (-6);
	*color = r * 256 * 256 + g * 256 + b;
	return (0);
}
