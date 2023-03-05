// 3D

void	make_grid(t_vars *vars)
{
	t_vector3	step;
	int			i;
	int			j;

	step.x = vars->grid_start.x;
	step.y = vars->grid_start.y;
	step.z = 0;
	i = 0;
	j = 0;
	while (j < vars->grid_size.y)
	{
		step.z = vars->p[i][j].z * vars->grid_shift.z
			* sin(vars->grid_rot.y) * cos(vars->grid_rot.z);
		vars->p[i][j].x = step.x;
		vars->p[i][j].y = step.y - step.z;
		step.x += vars->grid_shift.x * cos(vars->grid_rot.x)
			* sin(vars->grid_rot.y);
		step.y += vars->grid_shift.y * sin(vars->grid_rot.x)
			* cos(vars->grid_rot.y);
		i++;
		if (i == vars->grid_size.x)
		{
			j++;
			i = 0;
			step.x = vars->grid_start.x - (vars->grid_shift.x * j)
				* sin(vars->grid_rot.x) * cos(vars->grid_rot.z);
			step.y = vars->grid_start.y + vars->grid_shift.y * j
				* cos(vars->grid_rot.x) * sin(vars->grid_rot.z);
		}
	}
}

// render_ui_text(vars, 4, vars->grid_rot.z * 10, 250);

void	hook_rot2(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_E))
	{
		vars->index = 4;
		vars->grid_rot.z += up_ui(vars, vars->grid_rot.z * 10, 250, 0.02);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_Q))
	{
		vars->index = 4;
		vars->grid_rot.z -= up_ui(vars, vars->grid_rot.z * 10, 250, 0.02);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_R))
	{
		vars->index = 7;
		up_ui(vars, vars->grid_shift.x, 425, 0);
		vars->index = 8;
		up_ui(vars, vars->grid_shift.y, 450, 0);
		vars->index = 9;
		up_ui(vars, vars->grid_shift.z, 475, 0);
	}
}

	

