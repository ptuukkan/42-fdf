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

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	close(int keycode, void *param)
{
	(void)param;
	if (keycode == ESC)
		exit(0);
	return (0);
}

void	draw_line(int start_x, int start_y, int end_x, int end_y, void *mlx_ptr, void *win_ptr)
{
	int	dx;
	int	dy;
	int	d;
	int	s;

	dx = end_x - start_x;
	dy = end_y - start_y;
	s = 0;
	if (ft_abs(dx) > ft_abs(dy))
	{
		if (end_y > start_y)
			s = 1;
		else if (start_y > end_y)
			s = -1;
		while (start_x != end_x)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, start_x, start_y, 0xFFFFFF);
			if (d > 0)
			{
				start_y += s;
				d = d - 2 * dx;
			}
			d = d + 2 * dy;
			start_x++;
		}
	}
	else
	{
		if (end_x > start_x)
			s = 1;
		else if (start_x > end_x)
			s = -1;
		while (start_y != end_y)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, start_x, start_y, 0xFFFFFF);
			if (d > 0)
			{
				start_x += s;
				d = d - 2 * dy;
			}
			d = d + 2 * dx;
			start_y++;
		}
	}
}

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
	draw_line(50, 50, 50, 300, mlx_ptr, win_ptr);
	mlx_key_hook(win_ptr, close, 0);
	mlx_loop(mlx_ptr);
	return (0);
}
