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
	exit(EXIT_FAILURE);
}

void	render(t_vars *vars)
{
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

	vars.mlx = mlx_init(WIDTH, HEIGHT, "metal wire", true);
	if (!vars.mlx)
		ft_error();
	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	if (!vars.img || (mlx_image_to_window(vars.mlx, vars.img, 0, 0) < 0))
		ft_error();
	init_grid(&vars, map);
	render(&vars);
	mlx_loop_hook(vars.mlx, hook, &vars);
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
		write(1, "INPUT ERROR", 11);
	return (0);
}
