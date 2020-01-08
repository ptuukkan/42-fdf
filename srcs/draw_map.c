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

void	calculate_isometric(t_fdf *fdf, int x, int y, int direction)
{
	int	nx;
	int	ny;

//	fdf->map.x_angle = cos(0.46373398);
//	fdf->map.y_angle = sin(0.46373398);
	nx = x - fdf->map.width / 2;
	ny = y - fdf->map.height / 2;
	fdf->line.x0 = ((nx - ny) * cos(0.46373398) * fdf->map.zoom);
	fdf->line.y0 = ((nx + ny) * sin(0.46373398) * fdf->map.zoom);
	
	fdf->line.x1 = (((nx + direction) - (ny + (direction == 0))) * cos(0.46373398) * fdf->map.zoom);
	fdf->line.y1 = (((nx + direction) + (ny + (direction == 0))) * sin(0.46373398) * fdf->map.zoom);
	
	rotate_x(fdf, fdf->map.altitude[y][x], fdf->map.altitude[y + (direction == 0)][x + direction]);
	rotate_z(fdf);
	fdf->line.y0 -= fdf->map.alt_mul * fdf->line.z0;
	fdf->line.y1 -= fdf->map.alt_mul * fdf->line.z1;
	fdf->line.x0 += WIN_WIDTH / 2;
	fdf->line.x1 += WIN_WIDTH / 2;
	fdf->line.y0 += WIN_HEIGHT / 2;
	fdf->line.y1 += WIN_HEIGHT / 2;
}

void	plot(t_fdf *fdf, int x, int y, int dir)
{
	int nx;
	int ny;


	fdf->line.x0 = (x - fdf->map.width / 2) * fdf->map.zoom;
	fdf->line.y0 = (y - fdf->map.height / 2) * fdf->map.zoom;
	fdf->line.z0 = fdf->map.altitude[y][x] * fdf->map.alt_mul;
	fdf->line.x1 = ((x + dir) - fdf->map.width / 2) * fdf->map.zoom;
	fdf->line.y1 = ((y + (dir == 0)) - fdf->map.height / 2) * fdf->map.zoom;
	fdf->line.z1 = fdf->map.altitude[(y + (dir == 0))][(x + dir)] * 
					fdf->map.alt_mul;
	if (fdf->map.isometric)
		calculate_isometric(fdf, x, y, direction);
	else
	{
		nx = x - fdf->map.width / 2;
		ny = y - fdf->map.height / 2;
		fdf->line.x0 = nx * fdf->map.zoom;
		fdf->line.y0 = ny * fdf->map.zoom;
		//fdf->map.y0 -= fdf->map.alt_mul * fdf->map.altitude[y][x];
		fdf->line.x1 = (nx + direction) * fdf->map.zoom;
		fdf->line.y1 = (ny + (direction == 0)) * fdf->map.zoom;
		//fdf->map.y1 -= fdf->map.alt_mul * fdf->map.altitude[y + (direction == 0)][x + direction];
	//	rotate_x(fdf, fdf->map.altitude[y][x], fdf->map.altitude[y + (direction == 0)][x + direction]);
		rotate_z(fdf);
	//	fdf->map.y0 -= fdf->map.alt_mul * fdf->map.z0;
	//	fdf->map.y1 -= fdf->map.alt_mul * fdf->map.z1;
		
		fdf->line.x0 += WIN_WIDTH / 2;
		fdf->line.x1 += WIN_WIDTH / 2;
		fdf->line.y0 += WIN_HEIGHT / 2;
		fdf->line.y1 += WIN_HEIGHT / 2;
		//printf("x: %d x0: %d * %lf - y0: %d * %lf\n", x, fdf->map.x0, fdf->map.x_angle, fdf->map.y0, fdf->map.y_angle);
	}
}

void		draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	if (!(fdf->mlx.img_ptr = mlx_new_image(fdf->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT)))
		ft_exiterror("Image creation failed", 8, 2);
	fdf->img.img_data = mlx_get_data_addr(fdf->mlx.img_ptr, &fdf->img.bpp, &fdf->img.line_size, &fdf->img.endian);
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < (fdf->map.width - 1))
				plot(fdf, x, y, 1);
			if (y < (fdf->map.height - 1))
				plot(fdf, x, y, 0);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, fdf->mlx.img_ptr, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx_ptr, fdf->mlx.img_ptr);
}
