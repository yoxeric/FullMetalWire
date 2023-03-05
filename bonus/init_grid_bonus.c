/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:47:55 by yhachami          #+#    #+#             */
/*   Updated: 2023/03/05 00:16:55 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../fdf_bonus.h"

void	get_grid_len(t_vars *vars, int fd)
{
	t_vector2	s;
	char		*line;
	int			i;

	s.x = 0;
	s.y = 0;
	line = get_next_line(fd);
	while (line)
	{
		i = -1;
		s.x = 0;
		while (line[++i])
			if (((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
				&& (i == 0 || line[i - 1] == ' '))
				s.x++;
		if (s.x > vars->grid_size.x)
			vars->grid_size.x = s.x;
		free(line);
		line = get_next_line(fd);
		s.y++;
	}
	free(line);
	vars->grid_size.y = s.y;
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
				vars->p[x][y].c = get_color(DEF_COLOR);
			}
			if (line[i - 1] == ',')
				vars->p[x][y].c = get_color(line + i);
		}
	}
}

void	forge_grid(t_vars *vars, int fd)
{
	int		y;
	char	*line;

	vars->p = (t_vector3color **) malloc(vars->grid_size.x
			* sizeof(t_vector3color *));
	y = -1;
	while (++y < vars->grid_size.x)
		vars->p[y] = (t_vector3color *) malloc(vars->grid_size.y
				* sizeof(t_vector3color));
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

void	init_grid(t_vars *vars, char *map)
{
	int	f;

	f = open(map, O_RDONLY);
	get_grid_len(vars, f);
	close(f);
	vars->zoom = 1;
	vars->army.x = 1;
	vars->army.y = 1;
	vars->project = 1;
	vars->grid_start.x = 700;
	vars->grid_start.y = 250;
	vars->grid_rot.x = 0.78;
	vars->grid_rot.y = 1;
	vars->grid_shift.x = 1337 / (vars->grid_size.x + vars->grid_size.y);
	vars->grid_shift.y = 1337 / (vars->grid_size.x + vars->grid_size.y);
	vars->grid_shift.z = (vars->grid_size.x / vars->grid_size.y) * 2;
	f = open(map, O_RDONLY);
	forge_grid(vars, f);
	close(f);
}
