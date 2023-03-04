/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 23:23:58 by yhachami          #+#    #+#             */
/*   Updated: 2023/02/19 23:24:16 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf_bonus.h"

void	hook_mouse(mouse_key_t mouse_key, action_t action,
	modifier_key_t m, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mouse_key == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		mlx_get_mouse_pos(vars->mlx, &vars->mouse_pos.x, &vars->mouse_pos.y);
	if (mouse_key == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS && m == 0)
		mlx_get_mouse_pos(vars->mlx, &vars->mouse_rot.x, &vars->mouse_rot.y);
}

void	zoom(t_vars *vars, int sign)
{
	vars->zoom += 0.01 * sign;
	if (vars->zoom < 0.01)
		vars->zoom = 0.01;
}

void	hook_zoom(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_KP_ADD))
	{
		vars->index = 6;
		vars->grid_shift.z += up_ui(vars, vars->grid_shift.z * 10, 375, 0.1);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_KP_SUBTRACT))
	{
		vars->index = 6;
		vars->grid_shift.z -= up_ui(vars, vars->grid_shift.z * 10, 375, 0.1);
	}
}

void	hook_zoom2(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_PAGE_UP))
	{
		zoom(vars, 1);
		vars->index = 5;
		up_ui(vars, vars->zoom * 100, 300, 1);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_PAGE_DOWN))
	{
		if (vars->grid_shift.x + vars->grid_shift.y > 2.5)
		{
			zoom(vars, -1);
			vars->index = 5;
			up_ui(vars, vars->zoom * 100, 300, 1);
		}
	}
}

void	hook_zoom3(double x, double y, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if ((x != 0 || y > 0) && vars->zoom > 0.05)
	{
		zoom(vars, x - y);
		vars->index = 5;
		up_ui(vars, vars->zoom * 100, 300, 1);
	}
	if ((x != 0 || y < 0))
	{
		zoom(vars, x - y);
		vars->index = 5;
		up_ui(vars, vars->zoom * 100, 300, 1);
	}
}
