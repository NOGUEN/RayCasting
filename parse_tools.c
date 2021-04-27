#include <cub3d.h>

int		input_resolution(t_all *s, char *line, *i){
	if (s->win.x != 0 || s->win.y != 0)
		return (-3);
	(*i)++;
	s->win.x = tool_atoi(line, i);
	s->win.y = tool_atoi(line, i);
	if (s->win.x > 2560)
		s->win.x = 2560;
	if (s->win.y > 1400)
		s->win.y = 1400;
	ft_spaceskip(line, i);
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

	img = mlx_xpm_file_to_image(s->mlx.ptr, file, &tab[0])
}

int		input_texture(t_all *s, unsigned int ,char *line, int *i){
	(*i) += 2;

	tool_space_skip(line, i);

}
