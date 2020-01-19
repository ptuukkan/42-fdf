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

int			get_outcode(t_vec4 v)
{
	int	code;

	code = OC_IN;
	if (v.x > 1.0)
		code |= OC_RIGHT;
	else if (v.x < -1.0)
		code |= OC_LEFT;
	if (v.y > 1.0)
		code |= OC_TOP;
	else if (v.y < -1.0)
		code |= OC_BOTTOM;
	if (v.z > 1.0)
		code |= OC_FAR;
	else if (v.z < -1.0)
		code |= OC_NEAR;
	return (code);
}

int			clip(t_fdf *fdf, t_vec4 a, t_vec4 b)
{
	int	oc_a;
	int	oc_b;

	oc_a = get_outcode(a);
	oc_b = get_outcode(b);
	if (!(oc_a | oc_b))
		return (1);
	if (oc_a & oc_b)
		return (0);

}

void		viewport_transform(t_fdf *fdf, t_vec4 a, t_vec4 b)
{
	if (!clip(fdf, a, b))
		return ;
	multiply_vertex(&fdf->map.viewport, &a);
	multiply_vertex(&fdf->map.viewport, &b);
	a.x = (int)((a.x / a.w) + 0.5);
	a.y = (int)((a.y / a.w) + 0.5);
	b.x = (int)((b.x / b.w) + 0.5);
	b.y = (int)((b.y / b.w) + 0.5);
	draw_line(fdf, a, b);
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

	if (fdf->test)
		return (draw_sq(fdf));
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
	mlx_string_put(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, 10, 10, 0xFFFFFF, "x degrees:");
	mlx_string_put(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, 120, 10, 0xFFFFFF, ft_itoa(fdf->line.x_angle));
	mlx_string_put(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, 10, 25, 0xFFFFFF, "y degrees:");
	mlx_string_put(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, 120, 25, 0xFFFFFF, ft_itoa(fdf->line.y_angle));
	mlx_string_put(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, 10, 40, 0xFFFFFF, "z degrees:");
	mlx_string_put(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, 120, 40, 0xFFFFFF, ft_itoa(fdf->line.z_angle));
	mlx_destroy_image(fdf->mlx.mlx_ptr, fdf->mlx.img_ptr);
}
