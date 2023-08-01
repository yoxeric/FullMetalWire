/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:16:07 by yhachami          #+#    #+#             */
/*   Updated: 2023/08/01 16:33:05 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

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
		vars->grid_start.x -= 7;
		render_text(vars, 0, vars->grid_start.x, 100);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		vars->grid_start.x += 7;
		render_text(vars, 0, vars->grid_start.x, 100);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
	{
		vars->grid_start.y -= 7;
		render_text(vars, 1, vars->grid_start.y, 125);
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
		vars->grid_start.y += 7;
		render_text(vars, 1, vars->grid_start.y, 125);
	}
	if (mlx_is_mouse_down(vars->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(vars->mlx, &mouse_pos.x, &mouse_pos.y);
		vars->grid_start.x -= (vars->mouse_pos.x - mouse_pos.x) / 25;
		render_text(vars, 0, vars->grid_start.x, 100);
		vars->grid_start.y -= (vars->mouse_pos.y - mouse_pos.y) / 25;
		render_text(vars, 1, vars->grid_start.y, 125);
	}
}

void	hook_rot(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		vars->grid_rot.x += 0.02;
		render_text(vars, 2, vars->grid_rot.x * 10, 200);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		vars->grid_rot.x -= 0.02;
		render_text(vars, 2, vars->grid_rot.x * 10, 200);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W) && vars->army.y != 0)
	{
		vars->grid_rot.y += 0.02;
		render_text(vars, 3, vars->grid_rot.y * 10, 225);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S) && vars->army.y != 0)
	{
		vars->grid_rot.y -= 0.02;
		render_text(vars, 3, vars->grid_rot.y * 10, 225);
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
		vars->grid_rot.x += (float)(vars->mouse_rot.x - mouse_pos.x) / 7500;
		render_text(vars, 2, vars->grid_rot.x * 10, 200);
	}
	if (mlx_is_mouse_down(vars->mlx, MLX_MOUSE_BUTTON_RIGHT)
		&& vars->army.y != 0)
	{
		mlx_get_mouse_pos(vars->mlx, &mouse_pos.x, &mouse_pos.y);
		vars->grid_rot.y += (float)(vars->mouse_rot.y - mouse_pos.y) / 25000;
		render_text(vars, 3, vars->grid_rot.y * 10, 225);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_X))
		vars->grid_rot.x = 1;
}
