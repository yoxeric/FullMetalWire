/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_pointsDDA.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:42:27 by yhachami          #+#    #+#             */
/*   Updated: 2023/02/18 01:08:17 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	connect_pointsDDA(mlx_image_t *img, vector3 p1, vector3 p2)
{
	double x;
	double y;
	double dx;
	double dy;
	double s;
	int	i;

	x = p1.x;
	y = p1.y;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	s = dy/dx;
	if (fabs(dx) >= fabs(dy))
		s = fabs(dx);
	else
		s = fabs(dy);
	dx = dx / s;
	dy = dy / s;
	i = 1;
	while (i <= s)
	{
		mlx_put_pixel(img, x, y, 0x00FA0AFF);
		x = x + dx;
		y = y + dy;
		i++;
		//x++;
		//y = s * (x - p1.x)  + p1.y;
	}
}