/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:47:55 by yhachami          #+#    #+#             */
/*   Updated: 2023/08/01 16:54:37 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

void	fill_line(t_vars *vars, int x, int y)
{
	while (x < vars->grid_size.x - 1)
	{
		x++;
		vars->p[x][y].x = x;
		vars->p[x][y].y = y;
		vars->p[x][y].z = 0;
		vars->p[x][y].c = get_color(DEFAULT_COLOR);
	}
}

void	forge_line(t_vars *vars, char *line, int y)
{
	int	i;
	int	x;

	i = -1;
	x = -1;
	while (line[++i])
	{
		if ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				x++;
				vars->p[x][y].x = x;
				vars->p[x][y].y = y;
				vars->p[x][y].z = ft_atoi(line + i);
				vars->p[x][y].c = get_color(DEFAULT_COLOR);
			}
			if (line[i - 1] == ',')
				vars->p[x][y].c = get_color(line + i);
		}
	}
	if (x < vars->grid_size.x - 1)
		fill_line(vars, x, y);
}

void	forge_grid(t_vars *vars, int fd)
{
	int		y;
	char	*line;

	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		forge_line(vars, line, y);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	free(line);
}

void	get_grid_len(t_vars *vars, int fd)
{
	t_vector2	s;
	char		*line;
	int			i;

	s.x = 0;
	s.y = 0;
	line = get_next_line(fd);
	if (!line)
		exit(1);
	while (line)
	{
		i = -1;
		s.x = 0;
		while (line[++i])
		{
			if (((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
				&& (i == 0 || line[i - 1] == ' '))
				s.x++;
		}
		if (vars->grid_size.x < s.x)
			vars->grid_size.x = s.x;
		free(line);
		line = get_next_line(fd);
		s.y++;
	}
	free(line);
	vars->grid_size.y = s.y;
}

void	read_grid(t_vars *vars, char *map)
{
	int	f;

	f = open(map, O_RDONLY);
	get_grid_len(vars, f);
	close(f);
	vars->p = (t_vector3color **) malloc(vars->grid_size.x
			* sizeof(t_vector3color *));
	if (!vars->p)
		exit(1);
	f = -1;
	while (++f < vars->grid_size.x)
	{
		vars->p[f] = (t_vector3color *) malloc(vars->grid_size.y
				* sizeof(t_vector3color));
		if (!vars->p[f])
			exit(1);
	}
	f = open(map, O_RDONLY);
	forge_grid(vars, f);
	close(f);
	init_grid(vars);
}
