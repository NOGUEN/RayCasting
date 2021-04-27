#include <cub3d.h>

int		tool_space_skip(char *line, int *i){
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
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
