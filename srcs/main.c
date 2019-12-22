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

int	close_window(int keycode, t_fdf *fdf)
{
	printf("%x\n", keycode);
	if (keycode == ESC || keycode == 0xff1b)
		exit(0);
	if (keycode == 0x6a)
	{
		fdf->map.zoom -= 1;
		fdf->map.alt_mul = fdf->map.zoom / 20.0f;
		draw_map(fdf);
	}
	if (keycode == 0x6b)
	{
		fdf->map.zoom += 1;
		fdf->map.alt_mul = fdf->map.zoom / 20.0f;
		draw_map(fdf);
	}
	if (keycode == 0x6e)
	{
		fdf->map.alt_mul += 1;
		draw_map(fdf);
	}
	if (keycode == 0x6d)
	{
		fdf->map.alt_mul -= 1;
		draw_map(fdf);
	}
	return (0);
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

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		ft_exiterror("usaage.", 5, 1);
	read_map(argv[1], &fdf);
	//print_int_array(fdf.map.altitude, fdf.map.width, fdf.map.height);
	if (!(fdf.mlx.mlx_ptr = mlx_init()))
		ft_exiterror("MLX initialization failed", 6, 2);
	if (!(fdf.mlx.win_ptr = mlx_new_window(fdf.mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF")))
		ft_exiterror("Window creation failed", 7, 2);
	fdf.img.line_size = WIN_WIDTH * 4;
	fdf.img.total_size = WIN_WIDTH * 4 * WIN_HEIGHT;
	fdf.img.color.blue = 0x00;
	fdf.img.color.green = 0xFF;
	fdf.img.color.red = 0x28;
	fdf.map.zoom = 20;
	fdf.map.alt_mul = 1;
	draw_map(&fdf);
	mlx_key_hook(fdf.mlx.win_ptr, close_window, &fdf);
	mlx_loop(fdf.mlx.mlx_ptr);
	return (0);
}
