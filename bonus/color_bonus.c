/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 23:25:38 by yhachami          #+#    #+#             */
/*   Updated: 2023/02/19 23:25:41 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../fdf_bonus.h"

int	get_chanel(char *s)
{
	int	i;
	int	v;
	int	base;

	i = 2;
	v = 0;
	base = 1;
	while (--i >= 0)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			v += (s[i] - 55) * base;
		if (s[i] >= 'a' && s[i] <= 'z')
			v += (s[i] - 87) * base;
		else if (s[i] >= '0' && s[i] <= '9')
			v += (s[i] - '0') * base;
		base *= 16;
	}
	return (v);
}

t_rgb	get_color(char *s)
{
	t_rgb	color;

	color.r = get_chanel(s + 2);
	if (s[4] != ' ')
		color.g = get_chanel(s + 4);
	else
		color.g = 0;
	if (s[6] != ' ')
		color.b = get_chanel(s + 6);
	else
		color.b = 0;
	if (s[8] != ' ')
		color.a = get_chanel(s + 8);
	else
		color.a = 255;
	return (color);
}

int	rgb2int(t_rgb c)
{
	return (c.r * 16777216 + c.g * 65536 + c.b * 256 + c.a);
}

int	interpolate_color(t_rgb c1, t_rgb c2, float t)
{
	t_rgb	result;

	result.r = c1.r + (int)((c2.r - c1.r) * t);
	result.g = c1.g + (int)((c2.g - c1.g) * t);
	result.b = c1.b + (int)((c2.b - c1.b) * t);
	result.a = c1.a + (int)((c2.a - c1.a) * t);
	return (rgb2int(result));
}
