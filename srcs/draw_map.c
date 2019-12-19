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

static void	img_pixel_put(t_fdf *fdf, int x, int y)
{
	int	pos;

	pos = fdf->img.line_size * y + x * 4;
	if (x >= 0 && y >= 0 && x < WIN_HEIGHT && y < WIN_WIDTH)
	{
		fdf->img.img_data[pos++] = fdf->img.color.blue;
		fdf->img.img_data[pos++] = fdf->img.color.green;
		fdf->img.img_data[pos++] = fdf->img.color.red;
	}
}

static void	draw_run_over_rise(t_fdf *fdf, int dx, int dy)
{
	int	d;
	int	s;

	s = 0;
	if (fdf->map.y1 > fdf->map.y0)
		s = 1;
	else if (fdf->map.y0 > fdf->map.y1)
		s = -1;
	d = 2 * dy - dx;
	while (fdf->map.x0 != fdf->map.x1)
	{
		img_pixel_put(fdf, fdf->map.x0, fdf->map.y0);
		if (d > 0)
		{
			fdf->map.y0 += s;
			d = d - 2 * dx;
		}
		d = d + 2 * dy;
		fdf->map.x0 += 1;
	}
}

static void	draw_rise_over_run(t_fdf *fdf, int dx, int dy)
{
	int	d;
	int	s;

	s = 0:
	if (fdf->map.x1 > fdf->map.x0)
		s = 1;
	else if (fdf->map.x0 > fdf->map.x1)
		s = -1;
	d = 2 * dx - dy;
	while (fdf->map.y0 != fdf->map.y1)
	{
		img_pixel_put(fdf, fdf->map.x0, fdf->map.y0);
		if (d > 0)
		{
			fdf->map.x0 += s;
			d = d - 2 * dy;
		}
		d = d + 2 * dx;
		fdf->map.y0 += 1;
	}
}

static void	draw_line(t_fdf *fdf)
{
	int	dx;
	int	dy;

	dx = x1 - x0;
	dy = y1 - y0;
	if (ft_abs(dx) > ft_abs(dy))
		draw_run_over_rise(fdf, dx ,dy);
	else
		draw_rise_over_run(fdf, dx, dy);
}

void		draw_map(t_fdf *fdf)
{
	int	w;
	int	h = 0;

	while (h < fdf->map.height)
	{
		w = 0;
		while (w < fdf->map.width)
		{
			if (w < (fdf->map.width - 1))
			{
				draw_line(fdf, (w - h) * cos(0.523599), (w + h) * sin(0.523599)\
				- fdf->map.altitude[h][w], (w + 1 - h) * cos(0.523599), (w + h) *\
				sin(0.523599) - fdf->map.altitude[h][w + 1]);
			}
			if (h < (fdf->map.height - 1))
			{
				draw_line(fdf, (w - h) * cos(0.523599), (w + h) * sin(0.523599)\
				- fdf->map.altitude[h][w], (w - h) * cos(0.523599), (w + 1 + h) *\
				sin(0.523599) - fdf->map.altitude[h + 1][w]);
			}
			w++;
		}
		h++;
	}
}
