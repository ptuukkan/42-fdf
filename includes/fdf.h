/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 10:54:27 by ptuukkan          #+#    #+#             */
/*   Updated: 2021/07/29 16:10:31 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdlib.h>
// # include "keys.h" // MAC
# include "keys_linux.h" // Linux
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
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	unsigned char	set;
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
	int			width;
	int			height;
	intmax_t	peak;
	intmax_t	bottom;
	t_vec4		**vertices;
	double		*z_buf;
	float		zoom;
	float		alt_mul;
	short		view;
}				t_map;

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
	int		bpp;
	int		endian;
}				t_img;

typedef struct	s_line
{
	int		x0;
	int		y0;
	double	z0;
	int		x;
	int		y;
	double	z;
	int		x1;
	int		y1;
	double	z1;
	int		dy;
	int		dx;
	double	mz;
	t_color	color_start;
	t_color	color_end;
}				t_line;

typedef struct	s_viewport
{
	double	width;
	double	height;
	double	near;
	double	far;
	t_mat4	matrix;
}				t_viewport;

typedef struct	s_camera
{
	int		x;
	int		y;
	int		z;
	t_mat4	matrix;
}				t_camera;

typedef struct	s_rot
{
	double	x;
	double	y;
	double	z;
	t_mat4	matrix;
}				t_rot;

typedef struct	s_mvp
{
	int		x_offset;
	int		y_offset;
	int		z_offset;
	t_mat4	scale;
	t_mat4	move;
	t_mat4	projection;
	t_rot	rot;
	t_mat4	matrix;
}				t_mvp;

typedef struct	s_fdf
{
	t_map		map;
	t_mlx		mlx;
	t_img		img;
	t_viewport	viewport;
	t_camera	camera;
	t_mvp		mvp;
}				t_fdf;

void			read_file(char *file, t_fdf *fdf);
void			draw_map(t_fdf *fdf);
void			draw_line(t_fdf *fdf, t_line *line);
int				key_events(int key, t_fdf *fdf);
int				rotate_events(int key, t_fdf *fdf);
void			reset_map(t_fdf *fdf);
void			set_angles(t_fdf *fdf, double ax, double ay, double az);
void			create_new_image(t_fdf *fdf);
double			percent(double start, double current, double end);
void			init_color(t_fdf *fdf);
void			translate(t_fdf *fdf, double x, double y, double z);
void			build_mvp_matrix(t_fdf *fdf);
void			multiply_vertices(t_fdf *fdf, t_mat4 *m);
void			multiply_vertex(t_mat4 *m, t_vec4 *v);
int				clip2d(t_vec4 *a, t_vec4 *b);
int				clip3d(t_vec4 *a, t_vec4 *b);
t_color			read_color(char **line);
t_color			get_color(t_color color_start, t_color color_end, double perc);
t_mat4			multiply_matrix(t_mat4 *m1, t_mat4 *m2);
t_mat4			new_rotation_matrix(double ax, double ay, double az);
t_mat4			new_translation_matrix(double trans_x, double trans_y,
				double trans_z);
t_mat4			new_ortho_matrix(t_fdf *fdf);
t_mat4			new_perspective_matrix(t_fdf *fdf, double ar);
t_mat4			new_viewport_matrix(t_fdf *fdf);
t_mat4			new_scaling_matrix(double scale_x, double scale_y,
				double scale_z);

#endif
