/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:48:02 by yhachami          #+#    #+#             */
/*   Updated: 2023/08/01 16:54:57 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

void	ft_error(void)
{
	perror(mlx_strerror(mlx_errno));
	exit(1);
}

void	rerender(int width, int height, void *param)
{
	t_vars	*vars;
	int		i;

	vars = (t_vars *)param;
	mlx_delete_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, width - (width / 5), height);
	reset_grid(vars);
	draw_grid(vars);
	if (!vars->img || (mlx_image_to_window(vars->mlx, vars->img, 0, 0) < 0))
		ft_error();
	i = -1;
	while (++i < 30)
		mlx_delete_image(vars->mlx, vars->ui[i]);
	render_ui(vars, width, height);
}

void	hook(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	render(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_0)
		|| mlx_is_key_down(vars->mlx, MLX_KEY_KP_0)
		|| mlx_is_key_down(vars->mlx, MLX_KEY_SPACE))
	{
		rerender(vars->mlx->width, vars->mlx->height, vars);
		init_grid(vars);
		render_ui_text(vars);
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
	read_grid(&vars, map);
	render_ui(&vars, vars.mlx->width, vars.mlx->height);
	draw_grid(&vars);
	mlx_loop_hook(vars.mlx, hook, &vars);
	mlx_loop_hook(vars.mlx, hook_projection, &vars);
	mlx_loop_hook(vars.mlx, hook_move, &vars);
	mlx_loop_hook(vars.mlx, hook_zoom, &vars);
	mlx_loop_hook(vars.mlx, hook_zoom2, &vars);
	mlx_loop_hook(vars.mlx, hook_move2, &vars);
	mlx_loop_hook(vars.mlx, hook_rot, &vars);
	mlx_loop_hook(vars.mlx, hook_rot3, &vars);
	mlx_resize_hook(vars.mlx, rerender, &vars);
	mlx_mouse_hook(vars.mlx, hook_mouse, &vars);
	mlx_scroll_hook(vars.mlx, hook_zoom3, &vars);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	int	f;

	if (argc == 2)
	{
		f = open(argv[1], O_RDONLY);
		if (f >= 0)
		{
			close(f);
			f = ft_strlen(argv[1]);
			if (argv[1][f - 4] == '.' && argv[1][f - 3] == 'f'
				&& argv[1][f - 2] == 'd' && argv[1][f - 1] == 'f')
				fdf(argv[1]);
			else
				write(1, "FILE EXTENTION ERROR: expected \'.fdf\'", 39);
		}
		else
			write(1, "INVALID INPUT", 13);
	}
	else
		write(1, "INPUT ERROR: enter a .fdf map", 29);
	return (0);
}
