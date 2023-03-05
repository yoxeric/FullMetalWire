/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:48:02 by yhachami          #+#    #+#             */
/*   Updated: 2023/03/03 07:56:08 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf_bonus.h"

void	ft_error(void)
{
	perror(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	render(t_vars *vars)
{
	mlx_delete_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, WIDTH - (WIDTH / 5), HEIGHT);
	draw_grid(vars);
	if (!vars->img || (mlx_image_to_window(vars->mlx, vars->img, 0, 0) < 0))
		ft_error();
}

void	hook(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	render(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_0)
		|| mlx_is_key_down(vars->mlx, MLX_KEY_KP_0))
	{
		vars->zoom = 1;
		vars->grid_start.x = 700;
		vars->grid_start.y = 300;
		vars->grid_shift.x = 1337 / (vars->grid_size.x + vars->grid_size.y);
		vars->grid_shift.y = 1337 / (vars->grid_size.x + vars->grid_size.y);
		vars->grid_shift.z = (vars->grid_size.x / vars->grid_size.y);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(vars->mlx);
		free(vars->p);
	}
}

int	fdf(char *map)
{
	t_vars	vars;

	vars.mlx = mlx_init(WIDTH, HEIGHT, "Metal Wire", true);
	if (!vars.mlx)
		ft_error();
	vars.img = mlx_new_image(vars.mlx, WIDTH - (WIDTH / 5), HEIGHT);
	if (!vars.img || (mlx_image_to_window(vars.mlx, vars.img, 0, 0) < 0))
		ft_error();
	init_grid(&vars, map);
	render_ui(&vars);
	mlx_loop_hook(vars.mlx, hook, &vars);
	mlx_mouse_hook(vars.mlx, hook_mouse, &vars);
	mlx_loop_hook(vars.mlx, hook_projection, &vars);
	mlx_loop_hook(vars.mlx, hook_move, &vars);
	mlx_loop_hook(vars.mlx, hook_zoom, &vars);
	mlx_loop_hook(vars.mlx, hook_zoom2, &vars);
	mlx_loop_hook(vars.mlx, hook_move2, &vars);
	mlx_loop_hook(vars.mlx, hook_rot, &vars);
	mlx_loop_hook(vars.mlx, hook_rot3, &vars);
	mlx_scroll_hook(vars.mlx, hook_zoom3, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	int	f;

	f = open(argv[1], O_RDONLY);
	if (argc == 2 && f >= 0)
	{
		close(f);
		fdf(argv[1]);
	}
	else
		write(1, "INPUT ERROR:", 11);
	return (0);
}
