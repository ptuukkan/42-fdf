/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:00:53 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/19 12:00:54 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	rotate_events(int key, t_fdf *fdf)
{
	if (key == L_W)
		fdf->line.x_angle++;
	else if (key == L_S)
		fdf->line.x_angle--;
	else if (key == L_D)
		fdf->line.y_angle++;
	else if (key == L_A)
		fdf->line.y_angle--;
	else if (key == L_E)
		fdf->line.z_angle++;
	else if (key == L_Q)
		fdf->line.z_angle--;
	else if (fdf->line.x_angle == 360 || fdf->line.x_angle == -360)
		fdf->line.x_angle = 0;
	else if (fdf->line.y_angle == 360 || fdf->line.y_angle == -360)
		fdf->line.y_angle = 0;
	else if (fdf->line.z_angle == 360 || fdf->line.z_angle == -360)
		fdf->line.z_angle = 0;
	draw_map(fdf);
	return (0);
}

static int	zoom_events(int key, t_fdf *fdf)
{
	if (key == L_J)
	{
		if (fdf->map.zoom > 1.0)
		{
			fdf->map.zoom *= 0.9;
			fdf->map.alt_mul *= 0.9;
		}
	}
	else if (key == L_K)
	{
		fdf->map.zoom *= 1.1;
		fdf->map.alt_mul *= 1.1;
	}
	else if (key == L_N)
	{
		if (fdf->map.alt_mul > 1.0)
			fdf->map.alt_mul *= 0.9;
	}
	else if (key == L_M)
		fdf->map.alt_mul *= 1.1;
	draw_map(fdf);
	return (0);
}

int			key_events(int key, t_fdf *fdf)
{
	printf("%x\n", key);
	if (key == M_ESC || key == L_ESC)
		exit(0);
	if (key == L_J || key == L_K || key == L_N || key == L_M)
		return (zoom_events(key, fdf));
	if (key == L_LEFT || key == L_UP || key == L_RIGHT || key = L_DOWN)
		return (rotate_events(key, fdf));
	else if (key == 0x20)
	{
		if (fdf->map.isometric == 1)
		{
			fdf->line.x_angle = 0;
			fdf->line.y_angle = 0;
			fdf->line.z_angle = 0;
			fdf->map.isometric = 0;
		}
		else
			reset_map(fdf);
	}
	draw_map(fdf);
	return (0);
}
