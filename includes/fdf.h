/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 10:54:27 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/18 10:54:29 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include "keys_mac.h"
# include <stdint.h>
# include <fcntl.h>
# include "libft.h"
# include <math.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define OC_IN 0
# define OC_LEFT 1
# define OC_RIGHT 2
# define OC_BOTTOM 4
# define OC_TOP 8
# define OC_NEAR 16
# define OC_FAR 32

typedef struct	s_color
{
	int	red;
	int	green;
	int	blue;
}				t_color;

typedef struct	s_vec4
{
	double	x;
	double	y;
	double	z;
	double	w;
	t_color	color;
}				t_vec4;

typedef struct	s_mat4
{
	double	m[16];
}				t_mat4;

typedef struct	s_map
{
	int		width;
	int		height;
	int		**altitude;
	t_vec4	**vertices;
	int		peak;
	int		bottom;
	float	zoom;
	float	alt_mul;
	short	view;
	int		x_offset;
	int		y_offset;
	double	x_angle;
	double	y_angle;
	double	z_angle;
	t_mat4	rotation;
	t_mat4	scaling;
	t_mat4	moving;
	t_mat4	projection;
	t_mat4	mvp;
	t_mat4	viewport;
}				t_map;

typedef struct	s_quat
{
	float	w;
	float	x;
	float	y;
	float	z;
}				t_quat;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
}				t_mlx;

typedef struct	s_img
{
	t_color	color_start;
	t_color	color_end;
	char	*img_data;
	int		line_size;
	int		total_size;
	int		bpp;
	int		endian;
}				t_img;

typedef struct	s_line
{
	int		x0;
	int		y0;
	int		x;
	int		y;
	int		x1;
	int		y1;
	int		dy;
	int		dx;
	t_color	color_start;
	t_color	color_end;
}				t_line;

typedef struct	s_viewport
{
	int		width;
	int		height;
	t_line	line;
	t_mat4	matrix;
}				t_viewport;

typedef struct	s_fdf
{
	t_map		map;
	t_mlx		mlx;
	t_img		img;
	t_line		line;
	t_viewport	viewport;
	int		test;
}				t_fdf;

void			read_file(char *file, t_fdf *fdf);
void			draw_map(t_fdf *fdf);
void			draw_line(t_fdf *fdf, t_line *line);
void			calculate_xy(t_fdf *fdf, int x, int y, int direction);
int				key_events(int key, t_fdf *fdf);
int				rotate_events(int key, t_fdf *fdf);
void			rotate(t_fdf *fdf, double ax, double ay, double az);
void			reset_map(t_fdf *fdf);
void			draw_sq(t_fdf *fdf);
void			quat_rotate(t_fdf *fdf);
void			set_angles(t_fdf *fdf, double ax, double ay, double az);
t_color			get_color(t_color color_start, t_color color_end, double perc);
double			percent(int start, int current, int end);
void			init_color(t_fdf *fdf);
void			translate(t_fdf *fdf, double trans_x, double trans_y,
				double trans_z);
t_mat4			new_rotation_matrix(double ax, double ay, double az);
t_mat4			new_translation_matrix(double trans_x, double trans_y, double trans_z);
t_vec4			transform_vertex(t_fdf *fdf, t_vec4 *v);
void			construct_matrices(t_fdf *fdf);
void			build_mvp_matrix(t_fdf *fdf);
void			multiply_vertices(t_fdf *fdf, t_mat4 *m);
void			multiply_vertex(t_mat4 *m, t_vec4 *v);
t_mat4			new_scaling_matrix(double scale_x, double scale_y, double scale_z);
void			print_vertices(t_fdf *fdf);
int				clip(t_fdf *fdf, t_vec4 *a, t_vec4 *b);

#endif
