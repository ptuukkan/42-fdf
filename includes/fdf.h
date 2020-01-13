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
# include "keys_linux.h"
# include <stdint.h>
# include <fcntl.h>
# include "libft.h"
# include <math.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720


typedef struct	s_color
{
	int	red;
	int	green;
	int	blue;
}				t_color;

typedef struct	s_map
{
	int		width;
	int		height;
	int		**altitude;
	int		peak;
	int		bottom;
	float	zoom;
	float	alt_mul;
	short	projection;
	int		x_offset;
	int		y_offset;
}				t_map;

typedef struct	s_quat
{
	float	w;
	float	x;
	float	y;
	float	z;
}				t_quat;

typedef struct	s_line
{
	int		x0;
	int		y0;
	int		z0;
	int		x1;
	int		y1;
	int		z1;
	int		p;
	float	x_angle;
	float	y_angle;
	float	z_angle;
	t_color	color_start;
	t_color	color_end;
}				t_line;

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

typedef struct	s_fdf
{
	t_map	map;
	t_mlx	mlx;
	t_img	img;
	t_line	line;
	int		test;
}				t_fdf;

void			read_map(char *file, t_fdf *fdf);
void			draw_map(t_fdf *fdf);
void			draw_line(t_fdf *fdf);
void			calculate_xy(t_fdf *fdf, int x, int y, int direction);
int				key_events(int key, t_fdf *fdf);
int				rotate_events(int key, t_fdf *fdf);
void			rotate(t_fdf *fdf, float ax, float ay, float az);
void			reset_map(t_fdf *fdf);
void			draw_sq(t_fdf *fdf);
void			quat_rotate(t_fdf *fdf);
void			set_angles(t_fdf *fdf, float ax, float ay, float az);
t_color			get_color(t_color color_start, t_color color_end, double perc);
float			percent(int start, int current, int end);
void			init_color(t_fdf *fdf);

#endif
