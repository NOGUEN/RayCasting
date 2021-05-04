/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 16:18:24 by nogeun            #+#    #+#             */
/*   Updated: 2021/05/03 21:03:43 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "mlx/mlx.h"
# include "gnl/get_next_line.h"

# define NONE					0xFF000000
# define WHITE					0x00FFFFFF
# define BLACK					0x00000000
# define RED					0x00FF0000
# define GREEN					0x0000FF00
# define BLUE					0x000000FF
# define MAGENTA				0x00FF00FF
# define YELLOW					0x00FFFF00
# define CYAN					0x0000FFFF

# define texWidth				64
# define texHeight				64

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

# define KEY_ESC				53
# define KEY_Q					12
# define KEY_W					13
# define KEY_E					14
# define KEY_R					15
# define KEY_A					0
# define KEY_S					1

typedef struct		s_mlx{
	void			*ptr;
}					t_mlx;

typedef struct		s_win{
	void			*ptr;
	int				x;
	int				y;
}					t_win;

typedef struct		s_err{
	int				n;
}					t_err;

typedef struct		s_img{
	void			*ptr;
	int				*adr;

	int				img_width;
	int				img_height;
	int				size_l;
	int				bpp;
	int				endian;
}					t_img;

typedef struct		s_map{
	t_map			*next;
	char			*line;
}					t_map;

typedef struct		s_tex{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;
	unsigned int	*w;
	unsigned int	*i;
	unsigned int	f;
	unsigned int	c;
}					t_tex;

typedef struct		s_pos{
	double			x;
	double			y;
}					t_pos;

typedef struct		s_dir{
	double			x;
	double			y;
}					t_dir;

typedef struct		s_all{
	t_mlx			mlx;
	t_win			win;
	t_err			err;
	t_img			img;
	t_map			map_head;
	t_tex			tex;
	t_pos			pos;
	t_dir			dir;
}					t_all;

int		input_line(t_all *s, char *line);
void	parse(t_all *s, char *cub);

int		input_resolution(t_all *s, char *line, int *i);
int		input_xpm(t_all *s, unsigned int **adr, char *file);
int		input_texture(t_all *s, unsigned int **adr, char *line, int *i);
int		input_color(unsigned int *color, char *line, int *i);

int		tool_space_skip(char *line, int *i);
int		tool_atoi(char *line, int *i);
#endif

