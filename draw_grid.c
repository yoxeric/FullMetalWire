/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:58:33 by yhachami          #+#    #+#             */
/*   Updated: 2023/03/01 12:39:49 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

void	make_grid(t_vars *vars, t_vector3 step)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (j < vars->grid_size.y)
	{
		step.z = vars->p[i][j].z * vars->grid_shift.z
			* sin(vars->grid_rot.y);
		vars->p[i][j].x = step.x;
		vars->p[i][j].y = step.y - step.z;
		step.x += vars->grid_shift.x * cos(vars->grid_rot.x);
		step.y += vars->grid_shift.y
			* sin(vars->grid_rot.x) * cos(vars->grid_rot.y);
		i++;
		if (i == vars->grid_size.x)
		{
			j++;
			i = 0;
			step.x = vars->grid_start.x - (vars->grid_shift.x * j)
				* sin(vars->grid_rot.x);
			step.y = vars->grid_start.y + (vars->grid_shift.y * j)
				* cos(vars->grid_rot.x) * cos(vars->grid_rot.y);
		}
	}
}

void	draw_grid(t_vars *vars)
{
	t_vector3	step;
	int			i;
	int			j;

	step.x = vars->grid_start.x;
	step.y = vars->grid_start.y;
	make_grid(vars, step);
	i = 0;
	j = 0;
	while (j < vars->grid_size.y)
	{
		if (i < vars->grid_size.x -1)
			draw_line(vars->img, vars->p[i][j], vars->p[i +1][j]);
		if (j < vars->grid_size.y -1)
			draw_line(vars->img, vars->p[i][j], vars->p[i][j +1]);
		i++;
		if (i == vars->grid_size.x)
		{
			j++;
			i = 0;
		}
	}
}
