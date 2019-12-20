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

static void	img_pixel_put(t_fdf *fdf, int x, int y)
{
	int	pos;

	pos = fdf->img.line_size * y + x * 4;
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		fdf->img.img_data[pos++] = fdf->img.color.blue;
		fdf->img.img_data[pos++] = fdf->img.color.green;
		fdf->img.img_data[pos++] = fdf->img.color.red;
	}
}

static void	draw_run_over_rise(t_fdf *fdf, int dx, int dy)
{
	int	d;
	int	sy;
	int	sx;

	sy = 0;
	if (fdf->map.y1 > fdf->map.y0)
		sy = 1;
	else if (fdf->map.y0 > fdf->map.y1)
		sy = -1;
	d = 2 * dy - dx;
	sx = 1;
	if (fdf->map.x1 < fdf->map.x0)
		sx = -1;
	while (fdf->map.x0 != fdf->map.x1)
	{
		img_pixel_put(fdf, fdf->map.x0, fdf->map.y0);
		if (d > 0)
		{
			fdf->map.y0 += sy;
			d = d - 2 * dx;
		}
		d = d + 2 * dy;
		fdf->map.x0 += sx;
	}
}

static void	draw_rise_over_run(t_fdf *fdf, int dx, int dy)
{
	int	d;
	int	sy;
	int	sx;

	sx = 0;
	if (fdf->map.x1 > fdf->map.x0)
		sx = 1;
	else if (fdf->map.x0 > fdf->map.x1)
		sx = -1;
	d = 2 * dx - dy;
	sy = 1;
	if (fdf->map.y1 < fdf->map.y0)
		sy = -1;
	while (fdf->map.y0 != fdf->map.y1)
	{
		img_pixel_put(fdf, fdf->map.x0, fdf->map.y0);
		if (d > 0)
		{
			fdf->map.x0 += sx;
			d = d - 2 * dy;
		}
		d = d + 2 * dx;
		fdf->map.y0 += sy;
	}
}

void		draw_line(t_fdf *fdf)
{
	int	dx;
	int	dy;

	dx = ft_abs(fdf->map.x1 - fdf->map.x0);
	dy = ft_abs(fdf->map.y1 - fdf->map.y0);
	if (ft_abs(dx) > ft_abs(dy))
		draw_run_over_rise(fdf, dx ,dy);
	else
		draw_rise_over_run(fdf, dx, dy);
}
