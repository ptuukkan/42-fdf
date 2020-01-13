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
	fdf->map.alt_mul = fdf->map.zoom / 20;
	fdf->img.color.blue = 0x00;
	fdf->img.color.green = 0xFF;
	fdf->img.color.red = 0x28;
	fdf->img.line_size = WIN_WIDTH * 4;
	fdf->map.projection = 1;
	set_angles(fdf, -54.736f, 0.0f, 45.0f);
	fdf->test = 0;
	fdf->map.x_offset = 0;
	fdf->map.y_offset = 0;
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		ft_exiterror("usaage.", 5, 1);
	read_map(argv[1], &fdf);
	//print_int_array(fdf.map.altitude, fdf.map.width, fdf.map.height);
	if (!(fdf.mlx.mlx_ptr = mlx_init()))
		ft_exiterror("MLX initialization failed", 6, 2);
	if (!(fdf.mlx.win_ptr = mlx_new_window(fdf.mlx.mlx_ptr, WIN_WIDTH,
											WIN_HEIGHT, "FdF")))
		ft_exiterror("Window creation failed", 7, 2);
	reset_map(&fdf);
	draw_map(&fdf);
	mlx_hook(fdf.mlx.win_ptr, 2, (1L<<0), key_events, &fdf);
	mlx_loop(fdf.mlx.mlx_ptr);
	return (0);
}
