/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:58:33 by yhachami          #+#    #+#             */
/*   Updated: 2023/08/01 16:53:29 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

void	render(t_vars *vars)
{
	mlx_delete_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, vars->mlx->width
			- (vars->mlx->width / 5), vars->mlx->height);
	draw_grid(vars);
	if (!vars->img || (mlx_image_to_window(vars->mlx, vars->img, 0, 0) < 0))
		ft_error();
}

void	make_grid(t_vars *vars, t_vector3 step)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < vars->grid_size.y)
	{
		step.z = vars->p[i][j].z * vars->grid_shift.z * vars->zoom
			* sin(vars->grid_rot.y) * vars->army.x ;
		vars->p[i][j].x = step.x;
		vars->p[i][j].y = step.y - step.z;
		step.x += vars->grid_shift.x * vars->zoom * cos(vars->grid_rot.x);
		step.y += vars->grid_shift.y * vars->zoom * sin(vars->grid_rot.x)
			* cos(vars->grid_rot.y) * vars->project ;
		i++;
		if (i == vars->grid_size.x)
		{
			j++;
			i = 0;
			step.x = vars->grid_start.x - (vars->grid_shift.x * vars->zoom * j)
				* sin(vars->grid_rot.x);
			step.y = vars->grid_start.y + (vars->grid_shift.y * vars->zoom * j)
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
			draw_line(vars, vars->p[i][j], vars->p[i +1][j]);
		if (j < vars->grid_size.y -1)
			draw_line(vars, vars->p[i][j], vars->p[i][j +1]);
		i++;
		if (i == vars->grid_size.x)
		{
			j++;
			i = 0;
		}
	}
}

void	init_grid(t_vars *vars)
{
	vars->army.x = 1;
	vars->army.y = 1;
	vars->project = 1;
	vars->grid_shift.x = 1;
	vars->grid_shift.y = 1;
	vars->grid_rot.x = M_PI / 4;
	vars->grid_rot.y = M_PI / 4;
	reset_grid(vars);
}

void	reset_grid(t_vars *vars)
{
	t_vector3	s;

	vars->grid_start.x = (vars->img->width / 2);
	vars->grid_start.y = (vars->img->height / 4);
	vars->grid_shift.z = 0.5;
	if (vars->grid_size.x < 20 && vars->grid_size.y < 20)
		vars->grid_shift.z = 0.1;
	s.x = (vars->img->width / vars->grid_size.x);
	s.y = (vars->img->height / vars->grid_size.y);
	if (s.x < s.y && s.x > 0)
		vars->zoom = s.x / 2;
	else if (s.x > 0 && s.y > 0)
		vars->zoom = s.y / 2;
	else
		vars->zoom = 0.1;
}
