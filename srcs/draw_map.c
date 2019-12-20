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

void	calculate_xy(t_fdf *fdf, int x, int y, int direction)
{
	int	nx;
	int	ny;

	fdf->map.x_angle = cos(0.46373398);
	fdf->map.y_angle = sin(0.46373398);

	nx = x - fdf->map.width / 2;
	ny = y - fdf->map.height / 2;


	fdf->map.x0 = ((nx - ny) * fdf->map.zoom) * fdf->map.x_angle;
	fdf->map.y0 = ((nx + ny) * fdf->map.zoom) * fdf->map.y_angle - fdf->map.altitude[y][x];
	fdf->map.x1 = (((nx + direction) - (ny + (direction == 0))) * fdf->map.zoom) * fdf->map.x_angle;
	fdf->map.y1 = (((nx + direction) + (ny + (direction == 0))) * fdf->map.zoom) * fdf->map.y_angle -\
	fdf->map.altitude[y + (direction == 0)][x + direction];
	/*
	fdf->map.x0 = ((nx - ny) * fdf->map.zoom) * fdf->map.x_angle;
	fdf->map.y0 = ((nx + ny) * fdf->map.zoom) * fdf->map.y_angle;
	fdf->map.y0 -= fdf->map.altitude[y][x];
	if (direction == 1)
	{
		fdf->map.x1 = (((nx + 1) - ny) * fdf->map.zoom) * fdf->map.x_angle;
		fdf->map.y1 = (((nx + 1) + ny) * fdf->map.zoom) * fdf->map.y_angle;
		fdf->map.y1 -= fdf->map.altitude[y][x + 1];
	}
	else
	{
		fdf->map.x1 = ((nx - (ny + 1)) * fdf->map.zoom) * fdf->map.x_angle;
		fdf->map.y1 = ((nx + (ny + 1)) * fdf->map.zoom) * fdf->map.y_angle;
		fdf->map.y1 -= fdf->map.altitude[y + 1][x];
	}
	*/
	fdf->map.x0 += WIN_WIDTH / 2;
	fdf->map.x1 += WIN_WIDTH / 2;
	fdf->map.y0 += WIN_HEIGHT / 2;
	fdf->map.y1 += WIN_HEIGHT / 2;


}

void		draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < (fdf->map.width - 1))
			{
				calculate_xy(fdf, x, y, 1);
				draw_line(fdf);
			}
			if (y < (fdf->map.height - 1))
			{
				calculate_xy(fdf, x, y, 0);
				draw_line(fdf);
			}
			x++;
		}
		y++;
	}
}