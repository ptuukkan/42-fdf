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

int	close_window(int keycode, void *param)
{
	(void)param;
	if (keycode == ESC)
		exit(0);
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
	if (!(fdf.mlx.img_ptr = mlx_new_image(fdf.mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT)))
		ft_exiterror("Image creation failed", 8, 2);
	fdf.img.line_size = WIN_WIDTH * 4;
	fdf.img.total_size = WIN_WIDTH * 4 * WIN_HEIGHT;
	fdf.img.color.blue = 0x00;
	fdf.img.color.green = 0xFF;
	fdf.img.color.red = 0x28;
	fdf.map.zoom = 20;
	fdf.img.img_data = mlx_get_data_addr(fdf.mlx.img_ptr, &fdf.img.bpp, &fdf.img.line_size, &fdf.img.endian);
	draw_map(&fdf);
	mlx_key_hook(fdf.mlx.win_ptr, close_window, 0);
	mlx_loop(fdf.mlx.mlx_ptr);
	/*
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;




	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1280, 720, "mlx 42");
	img_ptr = mlx_new_image(mlx_ptr, 1280, 720);
	endian = get_endian();
	size_line = 1280 * 4;
	img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	draw_line(img_data, 50, 50, 700, 60, size_line);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);


*/
	return (0);
}
