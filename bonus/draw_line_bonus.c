/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:46:15 by yhachami          #+#    #+#             */
/*   Updated: 2023/03/05 00:17:01 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../fdf_bonus.h"

void	draw_pixel(mlx_image_t *img, t_vector3color p0, t_vector3color p1,
			t_vector2int v)
{
	int		color;
	double	num;
	double	denom;

	num = (v.x - p0.x) * (p1.x - p0.x) + (v.y - p0.y) * (p1.y - p0.y);
	denom = pow(p1.x - p0.x, 2) + pow(p1.y - p0.y, 2);
	color = interpolate_color(p0.c, p1.c, num / denom);
	mlx_put_pixel(img, v.x, v.y, color);
}

void	plot_line(mlx_image_t *img, t_vector3color p0, t_vector3color p1,
		t_plot l)
{
	while (true)
	{
		if (l.v.x > 5 && l.v.y > 5
			&& l.v.x < (int) img->width - 5 && l.v.y < (int) img->height - 5)
			draw_pixel(img, p0, p1, l.v);
		if (l.v.x == p1.x && l.v.y == p1.y)
			break ;
		l.e2 = 2 * l.err;
		if (l.e2 >= l.d.y)
		{
			if (l.v.x == p1.x)
				break ;
			l.err = l.err + l.d.y;
			l.v.x = l.v.x + l.s.x;
		}
		if (l.e2 <= l.d.x)
		{
			if (l.v.y == p1.y)
				break ;
			l.err = l.err + l.d.x;
			l.v.y = l.v.y + l.s.y;
		}
	}
}

void	draw_line(mlx_image_t *img, t_vector3color p0, t_vector3color p1)
{
	t_plot	l;

	l.v.x = p0.x;
	l.v.y = p0.y;
	l.d.x = abs(p1.x - p0.x);
	if (p0.x < p1.x)
		l.s.x = 1;
	else
		l.s.x = -1;
	l.d.y = -abs(p1.y - p0.y);
	if (p0.y < p1.y)
		l.s.y = 1;
	else
		l.s.y = -1;
	l.err = l.d.x + l.d.y;
	plot_line(img, p0, p1, l);
}
