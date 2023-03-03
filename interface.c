/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:25:19 by yhachami          #+#    #+#             */
/*   Updated: 2023/03/01 12:40:41 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

float	up_ui(t_vars *vars, float val, int pos, float step)
{
	char	*text;

	mlx_delete_image(vars->mlx, vars->ui[vars->index]);
	text = ft_itoa(val);
	vars->ui[vars->index] = mlx_put_string(vars->mlx, text,
			WIDTH - (WIDTH / 11), pos);
	free(text);
	return (step);
}

void	render_ui_text(t_vars *vars, int index, float content, int postion)
{
	char	*text;

	text = ft_itoa(content);
	vars->ui[index] = mlx_put_string(vars->mlx, text,
			WIDTH - (WIDTH / 11), postion);
	free(text);
}

void	render_numbs(t_vars *vars)
{
	render_ui_text(vars, 0, vars->grid_start.x, 100);
	render_ui_text(vars, 1, vars->grid_start.y, 125);
	render_ui_text(vars, 2, vars->grid_rot.x * 10, 200);
	render_ui_text(vars, 3, vars->grid_rot.y * 10, 225);
	render_ui_text(vars, 5, vars->zoom, 300);
	render_ui_text(vars, 6, vars->grid_shift.z * 10, 375);
	render_ui_text(vars, 7, vars->grid_size.x, 450);
	render_ui_text(vars, 8, vars->grid_size.y, 475);
}

void	render_bg(t_vars *vars)
{
	int	bg_size;
	int	i;
	int	j;

	bg_size = WIDTH / 5;
	vars->ui[10] = mlx_new_image(vars->mlx, bg_size, HEIGHT);
	if (!vars->ui[10] || (mlx_image_to_window(vars->mlx, vars->ui[10],
				WIDTH - bg_size, 0) < 0))
		ft_error();
	i = 0;
	j = 0;
	while (j < HEIGHT - 4)
	{
		mlx_put_pixel(vars->ui[10], i, j, BG_COLOR);
		i++;
		if (i == bg_size)
		{
			i = 0;
			j++;
		}
	}
}

void	render_ui(t_vars *vars)
{
	int	title_pos;
	int	num_pos;

	title_pos = WIDTH - (WIDTH / 5.5);
	num_pos = WIDTH - (WIDTH / 8);
	mlx_put_string(vars->mlx, "* Full Metal Wire *", WIDTH - (WIDTH / 5.9), 25);
	mlx_put_string(vars->mlx, "Grid postion: <,/\\,\\/,>", title_pos, 75);
	mlx_put_string(vars->mlx, "x - ", num_pos, 100);
	mlx_put_string(vars->mlx, "y - ", num_pos, 125);
	mlx_put_string(vars->mlx, "Grid Rotation: w,a,s,d", title_pos, 175);
	mlx_put_string(vars->mlx, "x - ", num_pos, 200);
	mlx_put_string(vars->mlx, "y - ", num_pos, 225);
	mlx_put_string(vars->mlx, "Grid Zoom: page up,down", title_pos, 275);
	mlx_put_string(vars->mlx, "@ - ", num_pos, 300);
	mlx_put_string(vars->mlx, "Grid altitude: +,-", title_pos, 350);
	mlx_put_string(vars->mlx, "^ - ", num_pos, 375);
	mlx_put_string(vars->mlx, "Grid Size:", title_pos, 425);
	mlx_put_string(vars->mlx, "x - ", num_pos, 450);
	mlx_put_string(vars->mlx, "y - ", num_pos, 475);
	render_bg(vars);
	render_numbs(vars);
}
