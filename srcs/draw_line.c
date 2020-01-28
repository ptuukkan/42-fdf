/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line->c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:00:53 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/19 12:00:54 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_depth(t_fdf *fdf, t_line *line, int dir)
{
	int	pos;

	if (line->x < 0 || line->x >= WIN_WIDTH || line->y < 0 ||
		line->y >= WIN_HEIGHT)
		return (0);
	pos = WIN_WIDTH * line->y + line->x;
	if (line->z < fdf->map.z_buf[pos])
	{
		fdf->map.z_buf[pos] = line->z;
		line->z += line->mz;
		return (1);
	}
	line->z += line->mz;
	return (0);
}

static void	img_pixel_put(t_fdf *fdf, t_line *line, int dir)
{
	int		pos;
	t_color	color;
	double	perc;

	if (!check_depth(fdf, line, dir))
		return ;
	pos = fdf->img.line_size * line->y + line->x * 4;
	if (dir == 1)
	{
		perc = percent(line->x0, line->x, line->x1);
		color = get_color(line->color_start, line->color_end, perc);
	}
	else
	{
		perc = percent(line->y0, line->y, line->y1);
		color = get_color(line->color_start, line->color_end, perc);
	}
	fdf->img.img_data[pos++] = color.blue;
	fdf->img.img_data[pos++] = color.green;
	fdf->img.img_data[pos++] = color.red;
	fdf->img.img_data[pos] = 0;
}

static void	draw_run_over_rise(t_fdf *fdf, t_line *line)
{
	int	d;
	int	sy;
	int	sx;

	sy = (line->y1 > line->y0);
	if (line->y0 > line->y1)
		sy = -1;
	d = 2 * line->dy - line->dx;
	sx = 1;
	if (line->x1 < line->x0)
		sx = -1;
	while (line->x != line->x1)
	{
		img_pixel_put(fdf, line, 1);
		if (d > 0)
		{
			line->y += sy;
			d = d - 2 * line->dx;
		}
		d = d + 2 * line->dy;
		line->x += sx;
	}
	img_pixel_put(fdf, line, 1);
}

static void	draw_rise_over_run(t_fdf *fdf, t_line *line)
{
	int	d;
	int	sy;
	int	sx;

	sx = (line->x1 > line->x0);
	if (line->x0 > line->x1)
		sx = -1;
	d = 2 * line->dx - line->dy;
	sy = 1;
	if (line->y1 < line->y0)
		sy = -1;
	while (line->y != line->y1)
	{
		img_pixel_put(fdf, line, 0);
		if (d > 0)
		{
			line->x += sx;
			d = d - 2 * line->dy;
		}
		d = d + 2 * line->dx;
		line->y += sy;
	}
	img_pixel_put(fdf, line, 0);
}

void		draw_line(t_fdf *fdf, t_line *line)
{
	line->dx = ft_abs(line->x1 - line->x0);
	line->dy = ft_abs(line->y1 - line->y0);
	if (line->dx > line->dy)
	{
		draw_run_over_rise(fdf, line);
		line->mz = (line->z1 - line->z0) / line->dx;
	}
	else
	{
		draw_rise_over_run(fdf, line);
		line->mz = (line->z1 - line->z0) / line->dy;
	}
}
