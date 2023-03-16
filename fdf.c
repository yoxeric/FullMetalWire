/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 07:55:31 by yhachami          #+#    #+#             */
/*   Updated: 2023/03/05 01:39:13 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

void	ft_error(void)
{
	perror(mlx_strerror(mlx_errno));
	exit(1);
}

void	resize_hook(int width, int height, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	mlx_delete_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, width, height);
	init_grid(vars);
	draw_grid(vars);
	if (!vars->img || (mlx_image_to_window(vars->mlx, vars->img, 0, 0) < 0))
		ft_error();
}

void	hook(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(vars->mlx);
		free(vars->p);
	}
}

int	fdf(char *map)
{
	t_vars	vars;

	read_grid(&vars, map);
	vars.mlx = mlx_init(WIDTH, HEIGHT, "metal wire", true);
	if (!vars.mlx)
		ft_error();
	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	if (!vars.img || (mlx_image_to_window(vars.mlx, vars.img, 0, 0) < 0))
		ft_error();
	init_grid(&vars);
	draw_grid(&vars);
	mlx_loop_hook(vars.mlx, hook, &vars);
	mlx_resize_hook(vars.mlx, resize_hook, &vars);
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
			f = 0;
			while (argv[1][f] != '.')
				f++;
			if (argv[1][f] == '.' && argv[1][f + 1] == 'f'
				&& argv[1][f + 2] == 'd' && argv[1][f + 3] == 'f')
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
