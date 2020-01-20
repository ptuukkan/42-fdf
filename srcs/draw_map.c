/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:00:53 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/19 12:00:54 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec4			mvp_transform(t_fdf *fdf, t_vec4 *v)
{
	t_vec4	new;
	double	perc;

	new.x = v->x;
	new.y = v->y;
	new.z = v->z;
	new.w = v->w;
	perc = percent(fdf->map.bottom, new.z, fdf->map.peak);
	new.color = get_color(fdf->img.color_start, fdf->img.color_end, perc);
	multiply_vertex(&fdf->map.mvp, &new);
	return (new);
}

void		viewport_transform(t_fdf *fdf, t_vec4 a, t_vec4 b)
{
	t_line	line;

	a.x /= a.w;
	a.y /= a.w;
	a.z /= a.w;
	b.x /= b.w;
	b.y /= b.w;
	b.z /= b.w;
	multiply_vertex(&fdf->map.viewport, &a);
	multiply_vertex(&fdf->map.viewport, &b);
	line.x0 = (int)(a.x + 0.5);
	line.y0 = (int)(a.y + 0.5);
	line.x = line.x0;
	line.y = line.y0;
	line.x1 = (int)(b.x + 0.5);
	line.y1 = (int)(b.y + 0.5);
	line.color_start = a.color;
	line.color_end = b.color;
	if (!clip(fdf, a, b))
		return ;
	draw_line(fdf, &line);
}

static void	plot(t_fdf *fdf, int x, int y)
{
	t_vec4	a;
	t_vec4	b;
	t_vec4	c;

	a = mvp_transform(fdf, &fdf->map.vertices[y][x]);
	if (x < fdf->map.width - 1)
	{
		b = mvp_transform(fdf, &fdf->map.vertices[y][x + 1]);
		viewport_transform(fdf, a, b);
	}
	if (y < fdf->map.height - 1)
	{
		c = mvp_transform(fdf, &fdf->map.vertices[y + 1][x]);
		viewport_transform(fdf, a, c);
	}
}

static void	create_new_image(t_fdf *fdf)
{
	if (!(fdf->mlx.img_ptr = mlx_new_image(fdf->mlx.mlx_ptr, WIN_WIDTH,
											WIN_HEIGHT)))
		ft_exiterror("Image creation failed", 8, 2);
	fdf->img.img_data = mlx_get_data_addr(fdf->mlx.img_ptr, &fdf->img.bpp,
									&fdf->img.line_size, &fdf->img.endian);
}

void		draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

//	if (fdf->test)
//		return (draw_sq(fdf));
	build_mvp_matrix(fdf);
	create_new_image(fdf);
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			plot(fdf, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr,
							fdf->mlx.img_ptr, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx_ptr, fdf->mlx.img_ptr);
}
