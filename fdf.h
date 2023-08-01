/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:59:09 by yhachami          #+#    #+#             */
/*   Updated: 2023/08/01 16:48:49 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "MLX42/include/MLX42/MLX42.h"

# define WIDTH 1920
# define HEIGHT 1080
# define DEFAULT_COLOR "0xFFFFFFFF"
# define BG_COLOR 0xBB0A1EAA

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
	float	x;
	float	y;
}	t_vector2;

typedef struct s_v2int {
	int	x;
	int	y;
}	t_vector2int;

typedef struct s_vars {
	t_vector3color	**p;
	t_vector3		grid_shift;
	t_vector3		grid_rot;
	t_vector2		grid_start;
	t_vector2		grid_size;
	t_vector2int	mouse_pos;
	t_vector2int	mouse_rot;
	t_vector2		army;
	float			project;
	float			zoom;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*ui[30];
}		t_vars;

char		*get_next_line(int fd);
char		*ft_itoa(int n);
int			ft_atoi(char *str);
int			ft_strlen(const char *s);

void		ft_error(void);
void		read_grid(t_vars *vars, char *map);
void		init_grid(t_vars *vars);
void		reset_grid(t_vars *vars);
void		make_grid(t_vars *vars, t_vector3 step);
void		draw_grid(t_vars *vars);
void		draw_line(t_vars *vars, t_vector3color p0, t_vector3color p1);
t_rgb		get_color(char *s);
int			rgb2int(t_rgb c);

void		hook_projection(void *params);
void		hook_move(void *param);
void		hook_move2(void *param);
void		hook_mouse(mouse_key_t mk, action_t a, modifier_key_t m, void *p);
void		hook_rot(void *param);
void		hook_rot3(void *param);
void		hook_zoom(void *param);
void		hook_zoom2(void *param);
void		hook_zoom3(double x, double y, void *param);
void		render(t_vars *vars);
void		render_ui(t_vars *vars, int width, int height);
void		render_ui_text(t_vars *vars);
void		render_text(t_vars *vars, int index, float val, int pos);
#endif
