/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 16:18:24 by nogeun            #+#    #+#             */
/*   Updated: 2021/04/27 12:05:22 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "mlx/mlx.h"
# include "gnl/get_next_line.h"

# define texWidth				64
# define texHeight				64

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_PRESS		3
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
}					t_win;

typedef struct		s_img{
	void			*ptr;
	int				*data;

	int				img_width;
	int				img_height;
	int				size_l;
	int				bpp;
	int				endian;
}					t_img;

typedef struct		s_map{
	char			**tab;
	int				x;
	int				y;
	int				spr;
}					t_map;

typedef struct		s_tex{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;
	unsigned int	*w;
	unsigned int	*i;
	unsigned int	c;
	unsigned int	f;
}					t_tex;

typedef struct		s_pos{
	double			x;
	double			y;
}					t_pos;

typedef struct		s_dir{
	double			x;
	double			y;
}

typedef struct		s_all{
	t_mlx			mlx;
	t_win			win;
	t_img			img;
	t_map			map;
	t_tex			tex;
	t_pos			pos;
	t_dir			dir;
}
#endif

