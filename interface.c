/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:25:19 by yhachami          #+#    #+#             */
/*   Updated: 2023/08/01 16:32:51 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

void	render_bg(t_vars *vars, int width, int height)
{
	int	bg_size;
	int	i;
	int	j;

	bg_size = width / 5;
	vars->ui[9] = mlx_new_image(vars->mlx, bg_size, height);
	if (!vars->ui[9] || (mlx_image_to_window(vars->mlx, vars->ui[9],
				width - bg_size, 0) < 0))
		ft_error();
	i = 0;
	j = 0;
	while (j < height - 4)
	{
		mlx_put_pixel(vars->ui[9], i, j, BG_COLOR);
		i++;
		if (i == bg_size)
		{
			i = 0;
			j++;
		}
	}
}

void	render_text(t_vars *vars, int index, float val, int pos)
{
	char	*text;

	if (vars->ui[index])
		mlx_delete_image(vars->mlx, vars->ui[index]);
	text = ft_itoa(val);
	vars->ui[index] = mlx_put_string(vars->mlx, text,
			vars->mlx->width - (vars->mlx->width / 11), pos);
	free(text);
}

void	render_ui_text(t_vars *vars)
{
	render_text(vars, 0, vars->grid_start.x, 100);
	render_text(vars, 1, vars->grid_start.y, 125);
	render_text(vars, 2, vars->grid_rot.x * 10, 200);
	render_text(vars, 3, vars->grid_rot.y * 10, 225);
	render_text(vars, 5, vars->zoom, 300);
	render_text(vars, 6, vars->grid_shift.z * 10, 375);
	render_text(vars, 7, vars->grid_size.x, 450);
	render_text(vars, 8, vars->grid_size.y, 475);
}

void	render_numbs(t_vars *v, int width, int height)
{
	int	tag_pos;
	int	num_pos;

	tag_pos = width - (width / 5.5);
	num_pos = width - (width / 7);
	v->ui[25] = mlx_put_string(v->mlx, "Projections", tag_pos, 525);
	v->ui[26] = mlx_put_string(v->mlx, "Isometric : 1", tag_pos, 550);
	v->ui[27] = mlx_put_string(v->mlx, "Military : 2", tag_pos, 575);
	v->ui[28] = mlx_put_string(v->mlx, "Cabinet : 3", tag_pos, 599);
	v->ui[29] = mlx_put_string(v->mlx, "RESET: PRESS 0 or SPACE", tag_pos,
			height - 50);
}

void	render_ui(t_vars *v, int width, int height)
{
	int	tag_pos;
	int	num_pos;

	tag_pos = width - (width / 5.5);
	num_pos = width - (width / 8);
	v->ui[10] = mlx_put_string(v->mlx, "* Full Metal Wire *",
			width - (width / 5.9), 25);
	v->ui[11] = mlx_put_string(v->mlx, "Grid postion: <,/\\,\\/,>", tag_pos, 75);
	v->ui[12] = mlx_put_string(v->mlx, "x - ", num_pos, 100);
	v->ui[13] = mlx_put_string(v->mlx, "y - ", num_pos, 125);
	v->ui[14] = mlx_put_string(v->mlx, "Grid Rotation: w,a,s,d", tag_pos, 175);
	v->ui[15] = mlx_put_string(v->mlx, "x - ", num_pos, 200);
	v->ui[16] = mlx_put_string(v->mlx, "y - ", num_pos, 225);
	v->ui[17] = mlx_put_string(v->mlx, "Grid Zoom: page up,down", tag_pos, 275);
	v->ui[18] = mlx_put_string(v->mlx, "@ - ", num_pos, 300);
	v->ui[19] = mlx_put_string(v->mlx, "Grid altitude: +,-", tag_pos, 350);
	v->ui[21] = mlx_put_string(v->mlx, "^ - ", num_pos, 375);
	v->ui[22] = mlx_put_string(v->mlx, "Grid Size:", tag_pos, 425);
	v->ui[23] = mlx_put_string(v->mlx, "x - ", num_pos, 450);
	v->ui[24] = mlx_put_string(v->mlx, "y - ", num_pos, 475);
	render_numbs(v, width, height);
	render_bg(v, width, height);
}
