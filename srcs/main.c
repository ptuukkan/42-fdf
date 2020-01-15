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

void	print_vertices(t_fdf *fdf)
{
	int	i;
	int	j;
	t_vec4 **v;

	v = fdf->map.vertices;
	j = 0;
	while (j < fdf->map.height)
	{
		i = 0;
		while (i < fdf->map.width)
		{
			printf("x: %f y: %f z: %f ", v[j][i].x, v[j][i].y, v[j][i].z);
			i++;
		}
		j++;
		printf("\n");
	}
}

void	print_int_array(int **arr, int width, int height)
{
	int	h = 0;
	int	w;

	while (h < height)
	{
		w = 0;
		while (w < width)
		{
			printf("%2d ", arr[h][w]);
			w++;
		}
		printf("\n");
		h++;
	}
}

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
	if (fdf->map.width > fdf->map.height)
		fdf->map.zoom = WIN_WIDTH / fdf->map.width - fdf->map.width;
	else
		fdf->map.zoom = WIN_HEIGHT / fdf->map.height - fdf->map.height;
	fdf->map.zoom = 30;
	fdf->map.alt_mul = fdf->map.zoom / 20;
	fdf->img.line_size = WIN_WIDTH * 4;
	fdf->map.view = 3;
	//set_angles(fdf, -54.736f, 0.0f, 45.0f);
	set_angles(fdf, 0.0f, 0.0f, 0.0f);
	fdf->test = 0;
	fdf->map.x_offset = 0;
	fdf->map.y_offset = 0;
	init_color(fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	fdf.img.bpp = 4;
	fdf.img.endian = get_endian();
	if (argc != 2)
		ft_exiterror("usaage.", 5, 1);
	read_file(argv[1], &fdf);
	//print_int_array(fdf.map.altitude, fdf.map.width, fdf.map.height);
	if (!(fdf.mlx.mlx_ptr = mlx_init()))
		ft_exiterror("MLX initialization failed", 6, 2);
	if (!(fdf.mlx.win_ptr = mlx_new_window(fdf.mlx.mlx_ptr, WIN_WIDTH,
											WIN_HEIGHT, "FdF")))
		ft_exiterror("Window creation failed", 7, 2);
	translate(&fdf, (fdf.map.width - 1) / -2.0, (fdf.map.height - 1) / -2.0,
				(-fdf.map.peak + -fdf.map.bottom) / 2);

	reset_map(&fdf);
	construct_matrices(&fdf);
	//build_mvp_matrix(&fdf);
	//multiply_vertices(&fdf, &fdf.map.mvp);
	//print_vertices(&fdf);
	//return (0);
	//viewport_transform(&fdf);

	draw_map(&fdf);

	mlx_hook(fdf.mlx.win_ptr, 2, (1L<<0), key_events, &fdf);
	mlx_loop(fdf.mlx.mlx_ptr);
	return (0);
}
