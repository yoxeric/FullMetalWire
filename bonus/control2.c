/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 23:23:58 by yhachami          #+#    #+#             */
/*   Updated: 2023/03/05 00:17:42 by yhachami         ###   ########.fr       */
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
	vars->zoom += 0.3 * sign;
	if (vars->zoom < 0.1)
		vars->zoom = 0.1;
}

void	hook_zoom(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_1)
		|| mlx_is_key_down(vars->mlx, MLX_KEY_KP_1))
	{
		vars->army.x = 1;
		vars->army.y = 1;
		vars->project = 1;
		vars->grid_rot.x = 0.78;
		vars->grid_rot.y = 1;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_KP_ADD))
	{
		vars->grid_shift.z += 0.01;
		render_text(vars, 6, vars->grid_shift.z * 10, 375);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_KP_SUBTRACT))
	{
		vars->grid_shift.z -= 0.01;
		render_text(vars, 6, vars->grid_shift.z * 10, 375);
	}
}

void	hook_zoom2(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_PAGE_UP))
	{
		zoom(vars, 1);
		render_text(vars, 5, vars->zoom * 10, 300);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_PAGE_DOWN))
	{
		zoom(vars, -1);
		render_text(vars, 5, vars->zoom * 10, 300);
	}
}

void	hook_zoom3(double x, double y, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if ((x != 0 || y > 0) && vars->zoom > 0.05)
	{
		zoom(vars, x - y);
		render_text(vars, 5, vars->zoom * 10, 300);
	}
	if ((x != 0 || y < 0))
	{
		zoom(vars, x - y);
		render_text(vars, 5, vars->zoom * 10, 300);
	}
}
