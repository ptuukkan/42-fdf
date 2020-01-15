/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:00:53 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/19 12:00:54 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	img_pixel_put(t_fdf *fdf, int x, int y, int dir)
{
	int		pos;
	t_color	color;

	pos = fdf->img.line_size * y + x * 4;
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		if (dir == 1)
			color = get_color(fdf->line.color_start, fdf->line.color_end,
					percent(fdf->line.x0, x, fdf->line.x1));
		else
			color = get_color(fdf->line.color_start, fdf->line.color_end,
					percent(fdf->line.y0, y, fdf->line.y1));
		//printf("color: r: %d g: %d b: %d\n", color.red, color.green, color.blue);
		fdf->img.img_data[pos++] = fdf->img.color_start.blue;
		fdf->img.img_data[pos++] = fdf->img.color_start.green;
		fdf->img.img_data[pos++] = fdf->img.color_start.red;
		fdf->img.img_data[pos] = 0;
	}
}

static void	draw_run_over_rise(t_fdf *fdf, int dx, int dy, t_vec4 a, t_vec4 b)
{
	int	d;
	int	sy;
	int	sx;

	sy = 0;
	if (b.y > a.y)
		sy = 1;
	else if (a.y > b.y)
		sy = -1;
	d = 2 * dy - dx;
	sx = 1;
	if (b.x < a.x)
		sx = -1;
	while (a.x != b.x)
	{
		img_pixel_put(fdf, a.x, a.y, 1);
		if (d > 0)
		{
			a.y += sy;
			d = d - 2 * dx;
		}
		d = d + 2 * dy;
		a.x += sx;
	}
	img_pixel_put(fdf, a.x, a.y, 1);
}

static void	draw_rise_over_run(t_fdf *fdf, int dx, int dy, t_vec4 a, t_vec4 b)
{
	int	d;
	int	sy;
	int	sx;

	sx = 0;
	if (b.x > a.x)
		sx = 1;
	else if (a.x > b.x)
		sx = -1;
	d = 2 * dx - dy;
	sy = 1;
	if (b.y < a.y)
		sy = -1;
	while (a.y != b.y)
	{
		img_pixel_put(fdf, a.x, a.y, 0);
		if (d > 0)
		{
			a.x += sx;
			d = d - 2 * dy;
		}
		d = d + 2 * dx;
		a.y += sy;
	}
	img_pixel_put(fdf, a.x, a.y, 0);
}

void		draw_line(t_fdf *fdf, t_vec4 a, t_vec4 b)
{
	int	dx;
	int	dy;

	//printf("x: %f y: %f z: %f\n", a.x, a.y, a.z);
	//printf("x: %f y: %f z: %f\n", b.x, b.y, b.z);
	dx = ft_abs(b.x - a.x);
	dy = ft_abs(b.y - a.y);
	//printf("\n");
	if (dx > dy)
		draw_run_over_rise(fdf, dx ,dy, a, b);
	else
		draw_rise_over_run(fdf, dx, dy, a, b);
}
