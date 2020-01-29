/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 10:52:34 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/17 10:52:36 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_endian(void)
{
	unsigned int	i;
	unsigned char	*c;

	i = 1;
	c = (unsigned char *)&i;
	if (*c)
		return (0);
	else
		return (1);
}

void	reset_map(t_fdf *fdf)
{
	fdf->img.line_size = WIN_WIDTH * 4;
	fdf->map.view = 1;
	set_angles(fdf, 54.736f, 0.0f, 45.0f);
	fdf->map.x_offset = 0;
	fdf->map.y_offset = 0;
	init_color(fdf);
	fdf->viewport.width = 896;
	fdf->viewport.height = 504;
	fdf->viewport.near = 1;
	fdf->viewport.far = 10000;
	fdf->camera.x = 0;
	fdf->camera.y = 0;
	fdf->camera.z = fdf->viewport.width / -2;
	fdf->map.zoom = fdf->viewport.height / ft_max(fdf->map.peak / 6 -
		fdf->map.bottom / 6, ft_max(fdf->map.width, fdf->map.height));
	fdf->map.alt_mul = 0.1;
	construct_matrices(fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	fdf.img.bpp = 4;
	fdf.img.endian = get_endian();
	if (argc != 2)
		return (write(1, "usage: fdf <input file>\n", 25));
	read_file(argv[1], &fdf);
	if (!(fdf.mlx.mlx_ptr = mlx_init()))
		ft_exiterror("MLX initialization failed", 6, 2);
	if (!(fdf.mlx.win_ptr = mlx_new_window(fdf.mlx.mlx_ptr, WIN_WIDTH,
											WIN_HEIGHT, "FdF")))
		ft_exiterror("Window creation failed", 7, 2);
	translate(&fdf, (fdf.map.width - 1) / -2.0, (fdf.map.height - 1) / -2.0,
				0.0);
	reset_map(&fdf);
	draw_map(&fdf);
	mlx_hook(fdf.mlx.win_ptr, 2, (1L<<0), key_events, &fdf);
	mlx_loop(fdf.mlx.mlx_ptr);
	return (0);
}
