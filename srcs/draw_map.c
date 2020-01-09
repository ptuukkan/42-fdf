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

static void	plot(t_fdf *fdf, int x, int y, int dir)
{
	fdf->line.x0 = (x - fdf->map.width / 2) * fdf->map.zoom;
	fdf->line.y0 = (y - fdf->map.height / 2) * fdf->map.zoom;
	fdf->line.z0 = fdf->map.altitude[y][x] * fdf->map.alt_mul;
	fdf->line.x1 = ((x + dir) - fdf->map.width / 2) * fdf->map.zoom;
	fdf->line.y1 = ((y + (dir == 0)) - fdf->map.height / 2) * fdf->map.zoom;
	fdf->line.z1 = fdf->map.altitude[(y + (dir == 0))][(x + dir)] *
					fdf->map.alt_mul;
	rotate(fdf, fdf->line.x_angle, fdf->line.y_angle, fdf->line.z_angle);
	fdf->line.x0 += WIN_WIDTH / 2;
	fdf->line.x1 += WIN_WIDTH / 2;
	fdf->line.y0 += WIN_HEIGHT / 2;
	fdf->line.y1 += WIN_HEIGHT / 2;
	draw_line(fdf);
}

void		draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	if (!(fdf->mlx.img_ptr = mlx_new_image(fdf->mlx.mlx_ptr, WIN_WIDTH,
											WIN_HEIGHT)))
		ft_exiterror("Image creation failed", 8, 2);
	fdf->img.img_data = mlx_get_data_addr(fdf->mlx.img_ptr, &fdf->img.bpp,
										&fdf->img.line_size, &fdf->img.endian);
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
	mlx_put_image_to_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr,
							fdf->mlx.img_ptr, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx_ptr, fdf->mlx.img_ptr);
}
