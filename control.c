/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:16:07 by yhachami          #+#    #+#             */
/*   Updated: 2023/03/05 00:17:37 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf_bonus.h"

void	hook_projection(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_2)
		|| mlx_is_key_down(vars->mlx, MLX_KEY_KP_2))
	{
		vars->army.x = 50;
		vars->army.y = 0;
		vars->project = 1;
		vars->grid_rot.x = 0.78;
		vars->grid_rot.y = 0.05;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_3)
		|| mlx_is_key_down(vars->mlx, MLX_KEY_KP_3))
	{
		vars->army.x = 10;
		vars->army.y = 1;
		vars->project = 0;
		vars->grid_rot.x = 0.59;
		vars->grid_rot.y = 0.5;
	}
}

void	hook_move(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		vars->index = 0;
		vars->grid_start.x -= up_ui(vars, vars->grid_start.x, 100, 7);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		vars->index = 0;
		vars->grid_start.x += up_ui(vars, vars->grid_start.x, 100, 7);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
	{
		vars->index = 1;
		vars->grid_start.y -= up_ui(vars, vars->grid_start.y, 125, 7);
	}
}

void	hook_move2(void *param)
{
	t_vars			*vars;
	t_vector2int	mouse_pos;

	mouse_pos.x = 0;
	mouse_pos.y = 0;
	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
	{
		vars->index = 1;
		vars->grid_start.y += up_ui(vars, vars->grid_start.y, 125, 7);
	}
	if (mlx_is_mouse_down(vars->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(vars->mlx, &mouse_pos.x, &mouse_pos.y);
		vars->index = 0;
		vars->grid_start.x -= up_ui(vars, vars->grid_start.x, 100,
				(vars->mouse_pos.x - mouse_pos.x) / 25);
		vars->index = 1;
		vars->grid_start.y -= up_ui(vars, vars->grid_start.y, 125,
				(vars->mouse_pos.y - mouse_pos.y) / 25);
	}
}

void	hook_rot(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		vars->index = 2;
		vars->grid_rot.x += up_ui(vars, vars->grid_rot.x * 10, 200, 0.02);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		vars->index = 2;
		vars->grid_rot.x -= up_ui(vars, vars->grid_rot.x * 10, 200, 0.02);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W) && vars->army.y != 0)
	{
		vars->index = 3;
		vars->grid_rot.y += up_ui(vars, vars->grid_rot.y * 10, 225, 0.02);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S) && vars->army.y != 0)
	{
		vars->index = 3;
		vars->grid_rot.y -= up_ui(vars, vars->grid_rot.y * 10, 225, 0.02);
	}
}

void	hook_rot3(void *param)
{
	t_vars			*vars;
	t_vector2int	mouse_pos;

	mouse_pos.x = 0;
	mouse_pos.y = 0;
	vars = (t_vars *)param;
	if (mlx_is_mouse_down(vars->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		mlx_get_mouse_pos(vars->mlx, &mouse_pos.x, &mouse_pos.y);
		vars->index = 2;
		vars->grid_rot.x += up_ui(vars, vars->grid_rot.x * 10, 200,
				(float)(vars->mouse_rot.x - mouse_pos.x) / 7500);
	}
	if (mlx_is_mouse_down(vars->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		mlx_get_mouse_pos(vars->mlx, &mouse_pos.x, &mouse_pos.y);
		vars->index = 3;
		vars->grid_rot.y += up_ui(vars, vars->grid_rot.y * 10, 225,
				(float)(vars->mouse_rot.y - mouse_pos.y) / 25000);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_X))
		vars->grid_rot.x = 1;
}
