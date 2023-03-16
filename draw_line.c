/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:46:15 by yhachami          #+#    #+#             */
/*   Updated: 2023/03/03 07:56:51 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

void	draw_pixel(t_vars *vars, t_vector3 v,
		t_vector3color p0, t_vector3color p1)
{
	int		color;
	float	num;
	float	denom;
	t_rgb	lerp;

	if (v.x > 5 && v.x < (int) vars->img->width - 5
		&& v.y > 5 && v.y < (int) vars->img->height - 5)
	{
		num = (v.x - p0.x) * (p1.x - p0.x) + (v.y - p0.y) * (p1.y - p0.y);
		denom = pow(p1.x - p0.x, 2) + pow(p1.y - p0.y, 2);
		lerp.r = p0.c.r + (int)((p1.c.r - p0.c.r) * (num / denom));
		lerp.g = p0.c.g + (int)((p1.c.g - p0.c.g) * (num / denom));
		lerp.b = p0.c.b + (int)((p1.c.b - p0.c.b) * (num / denom));
		lerp.a = p0.c.a + (int)((p1.c.a - p0.c.a) * (num / denom));
		color = rgb2int(lerp);
		mlx_put_pixel(vars->img, v.x, v.y, color);
	}
}

void	draw_line(t_vars *vars, t_vector3color p0, t_vector3color p1)
{
	t_vector3	v;
	t_vector3	d;
	int			i;

	v.x = p0.x;
	v.y = p0.y;
	d.x = p1.x - p0.x;
	d.y = p1.y - p0.y;
	d.z = d.y / d.x;
	if (fabs(d.x) >= fabs(d.y))
		d.z = fabs(d.x);
	else
		d.z = fabs(d.y);
	d.x = d.x / d.z;
	d.y = d.y / d.z;
	i = 1;
	while (i <= d.z)
	{
		draw_pixel(vars, v, p0, p1);
		v.x = v.x + d.x;
		v.y = v.y + d.y;
		i++;
	}
}
