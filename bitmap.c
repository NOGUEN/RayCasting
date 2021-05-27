/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:24:10 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/25 16:53:39 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_int_in_char(unsigned char *start, int value){
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

int		write_bmp_header(int fd, int filesize, t_all *s){
	int				i;
	int				tmp;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	tmp = s->win.x;
	set_int_in_char(bmpfileheader + 18, tmp);
	tmp = s->win.y;
	set_int_in_char(bmpfileheader + 22, tmp);
	bmpfileheader[26] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpfileheader, 54) < 0));
}

int		get_color(t_all *s, int x, int y){
	int		rgb;
	int		color;

	color = s->win.buf[y][x];
	rgb = (color & 0xFFFFFF);
	return (rgb);
}

int		write_bmp_data(int file, t_all *s, int pad){
	unsigned char		zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					color;

	i = (int)s->win.y;
	while (--i >= 0){
		j = 0;
		while (j < (int)s->win.x){
			color = get_color(s, j, i);
			if (write(file, &color, 3) < 0)
				return (0);
			if (pad > 0 && write(file, &zero, pad) < 0)
				return (0);
			j++;
		}
	}
	return (1);
}

int		save_bmp(t_all *s){
	int		filesize;
	int		file;
	int		pad;

	pad = (4 - ((int)s->win.x * 3) % 4) % 4;
	filesize = 54 + (3 * ((int)s->win.x + pad) * (int)s->win.y);
	if ((file = 
		open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) < 0)
		return (0);
	if (!write_bmp_header(file, filesize, s))
		return (0);
	if (!write_bmp_data(file, s, pad))
		return (0);
	close(file);
	return (1);
}
