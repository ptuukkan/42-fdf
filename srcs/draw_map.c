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

static void	plot(t_fdf *fdf, int x, int y)
{
	t_vec3	a;

	a = viewport_transform(fdf, &fdf->map.vertices[y][x]);
	a.color = get_color(fdf->img.color_start, fdf->img.color_end,
						percent(fdf->map.bott))

	fdf->line.color_start = get_color(fdf->img.color_start, fdf->img.color_end,
					percent(fdf->map.bottom * fdf->map.alt_mul,
							fdf->line.z0, fdf->map.peak * fdf->map.alt_mul));
	fdf->line.color_end = get_color(fdf->img.color_start, fdf->img.color_end,
					percent(fdf->map.bottom * fdf->map.alt_mul,
							fdf->line.z1, fdf->map.peak * fdf->map.alt_mul));
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
