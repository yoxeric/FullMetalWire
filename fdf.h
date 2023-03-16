/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:32:15 by yhachami          #+#    #+#             */
/*   Updated: 2023/03/01 12:42:59 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "MLX42/include/MLX42/MLX42.h"

# define WIDTH 1440
# define HEIGHT 1080
# define DEFAULT_COLOR "0xFFFFFFFF"

typedef struct s_rgb {
	int	r;
	int	g;
	int	b;
	int	a;
}	t_rgb;

typedef struct s_v3c {
	int		x;
	int		y;
	int		z;
	t_rgb	c;
}	t_vector3color;

typedef struct s_v3 {
	float	x;
	float	y;
	float	z;
}	t_vector3;

typedef struct s_v2 {
	int	x;
	int	y;
}	t_vector2;

typedef struct s_vars {
	t_vector3color	**p;
	t_vector3		grid_shift;
	t_vector3		grid_rot;
	t_vector2		grid_start;
	t_vector2		grid_size;
	float			zoom;
	mlx_t			*mlx;
	mlx_image_t		*img;
}		t_vars;

char		*get_next_line(int fd);
int			ft_atoi(char *str);
void		ft_error(void);
void		read_grid(t_vars *vars, char *map);
void		init_grid(t_vars *vars);
void		draw_grid(t_vars *vars);
void		draw_line(t_vars *vars, t_vector3color p0, t_vector3color p1);
t_rgb		get_color(char *s);
int			rgb2int(t_rgb c);
#endif
