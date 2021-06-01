/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nogeun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 16:18:24 by nogeun            #+#    #+#             */
/*   Updated: 2021/06/01 14:32:44 by nogeun           ###   ########.fr       */
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

# define TEXWIDTH				64
# define TEXHEIGHT				64

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
# define KEY_D					2

typedef struct		s_mlx{
	void			*ptr;
}					t_mlx;

typedef struct		s_win{
	void			*ptr;
	int				x;
	int				y;
	int				**buf;
}					t_win;

typedef struct		s_err{
	int				n;
	int				p;
}					t_err;

typedef struct		s_img{
	void			*ptr;
	int				*data;

	int				width;
	int				height;
	int				size_l;
	int				bpp;
	int				endian;
}					t_img;

typedef struct		s_map{
	char			**map;
	int				x;
	int				y;
	int				mapx;
	int				mapy;
	int				spr;
}					t_map;

typedef struct		s_tex{
	int				*n;
	int				*s;
	int				*e;
	int				*w;
	unsigned int	f;
	unsigned int	c;
}					t_tex;

typedef struct		s_pos{
	double			x;
	double			y;
	double			z;
}					t_pos;

typedef struct		s_dir{
	double			x;
	double			y;
}					t_dir;

typedef struct		s_plane{
	double			x;
	double			y;
}					t_plane;

typedef struct		s_speed{
	double			move;
	double			rotate;
}					t_speed;

typedef struct		s_fcray{
	float			raydirx0;
	float			raydiry0;
	float			raydirx1;
	float			raydiry1;
	int				p;
	float			rowdistance;
	float			floorstepx;
	float			floorstepy;
	float			floorx;
	float			floory;
	int				cellx;
	int				celly;
}					t_fcray;

typedef struct		s_wallray{
	double			camerax;
	double			raydirx;
	double			raydiry;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	double			step;
	double			texpos;
	double			floorxwall;
	double			floorywall;
}					t_wallray;

typedef struct		s_draw{
	int				lineheight;
	int				texnum;
	int				drawstart;
	int				drawend;
	int				texx;
	int				texy;
	int				color;
	double			wallx;
}					t_draw;

typedef struct		s_dist{
	double			wall;
	double			player;
	double			current;
}					t_dist;

typedef struct		s_all{
	t_mlx			mlx;
	t_win			win;
	t_err			err;
	t_img			img;
	t_map			map;
	t_tex			tex;
	t_pos			pos;
	t_dir			dir;
	t_plane			plane;
	t_speed			speed;
	t_fcray			fcray;
	t_wallray		wallray;
	t_draw			draw;
	t_dist			dist;
}					t_all;

void				longest_line(t_all *s, char *cub);
int					input_line(t_all *s, char *line, int *j);
int					parse(t_all *s, char *cub);

int					input_xpm(t_all *s, int **adr, char *file);
int					input_texture(t_all *s, int **adr, char *line, int *i);
int					input_color(unsigned int *color, char *line, int *i);

int					set_map(t_all *s);
int					input_map(t_all *s, char *line, int *j);

int					name_check(char *arg, char *ext);
int					map_check(t_all *s);
void				set_direction(t_all *s, char c);
int					parse_check(t_all *s);
void				pos_check(t_all *s);

int					find_start_point(t_all *s, int *i, int *j);
int					save_check(char *arg, char *save);

void				convert_wall(t_all *s, int *i, int *j);
void				convert_wall_left(t_all *s, int *i, int *j);
void				convert_wall_right(t_all *s, int *i, int *j);
void				convert_wall_up(t_all *s, int *i, int *j);
void				convert_wall_down(t_all *s, int *i, int *j);

void				fc_setting(t_all *s, int y);
void				wall_setting(t_all *s, int x);
void				step_setting(t_all *s);
void				tex_setting(t_all *s, int x);
void				dirtex_setting(t_all *s);

void				fc_casting(t_all *s);
void				perform_dda(t_all*s);
void				calculate(t_all *s);
void				wall_casting(t_all *s);
void				draw(t_all *s);

void				last_casting1(t_all *s);
void				last_casting2(t_all *s, int x);
int					main_loop(t_all *s);

int					key_press(int keycode, t_all *s);
void				act_move(t_all *s, double c);
void				act_rotate(t_all *s, double c);

void				set_int_in_char(unsigned char *start, int value);
int					write_bmp_header(int fd, int filesize, t_all *s);
int					get_color(t_all *s, int x, int y);
int					write_bmp_data(int file, t_all *s, int pad);
int					save_bmp(t_all *s);

int					tool_space_skip(char *line, int *i);
int					tool_atoi(char *line, int *i);
int					tool_strlen(char *line);
int					tool_error(int err);
int					tool_close();

#endif
