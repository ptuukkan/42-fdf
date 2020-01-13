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
		fdf->img.img_data[pos++] = color.blue;
		fdf->img.img_data[pos++] = color.green;
		fdf->img.img_data[pos++] = color.red;
		fdf->img.img_data[pos] = 0;
	}
}

static void	draw_run_over_rise(t_fdf *fdf, int dx, int dy)
{
	int	d;
	int	sy;
	int	sx;

	sy = 0;
	if (fdf->line.y1 > fdf->line.y0)
		sy = 1;
	else if (fdf->line.y0 > fdf->line.y1)
		sy = -1;
	d = 2 * dy - dx;
	sx = 1;
	if (fdf->line.x1 < fdf->line.x0)
		sx = -1;
	fdf->line.p = fdf->line.x0;
	while (fdf->line.p != fdf->line.x1)
	{
		img_pixel_put(fdf, fdf->line.p, fdf->line.y0, 1);
		if (d > 0)
		{
			fdf->line.y0 += sy;
			d = d - 2 * dx;
		}
		d = d + 2 * dy;
		fdf->line.p += sx;
	}
	img_pixel_put(fdf, fdf->line.p, fdf->line.y0, 1);
}

static void	draw_rise_over_run(t_fdf *fdf, int dx, int dy)
{
	int	d;
	int	sy;
	int	sx;

	sx = 0;
	if (fdf->line.x1 > fdf->line.x0)
		sx = 1;
	else if (fdf->line.x0 > fdf->line.x1)
		sx = -1;
	d = 2 * dx - dy;
	sy = 1;
	if (fdf->line.y1 < fdf->line.y0)
		sy = -1;
	fdf->line.p = fdf->line.y0;
	while (fdf->line.p != fdf->line.y1)
	{
		img_pixel_put(fdf, fdf->line.x0, fdf->line.p, 0);
		if (d > 0)
		{
			fdf->line.x0 += sx;
			d = d - 2 * dy;
		}
		d = d + 2 * dx;
		fdf->line.p += sy;
	}
	img_pixel_put(fdf, fdf->line.x0, fdf->line.p, 0);
}

void		draw_line(t_fdf *fdf)
{
	int	dx;
	int	dy;

	dx = ft_abs(fdf->line.x1 - fdf->line.x0);
	dy = ft_abs(fdf->line.y1 - fdf->line.y0);
	//printf("\n");
	if (dx > dy)
		draw_run_over_rise(fdf, dx ,dy);
	else
		draw_rise_over_run(fdf, dx, dy);
}
