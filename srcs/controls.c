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

static int	rotate_isometric(int key, t_fdf *fdf)
{
	if (key == L_D)
		fdf->line.y_angle += 90.0f;
	if (key == L_A)
		fdf->line.y_angle -= 90.0f;
	if (fdf->line.y_angle == 405.0f || fdf->line.y_angle == -405.0f)
		fdf->line.y_angle = 0.0f;
	draw_map(fdf);
	return (0);
}

static int	rotate_parallel(int key, t_fdf *fdf)
{
	if (key == L_S && fdf->line.x_angle == 0.0f)
		fdf->line.x_angle == 90.f;
	else if (key == L_W == fdf->line.x_angle != 0.0f)
		fdf->line.x_angle == 0.0f;
	else if (key == L_D == fdf->line.x_angle != 0.0f)
		fdf->line.y_angle += 90.0f;
	else if (key == L_A == fdf->line.x_angle != 0.0f)
		fdf->line.y_angle -= 90.0f;
	else if (key == L_D == fdf->line.x_angle == 0.0f)
		fdf->line.z_angle += 90.0f;
	else if (key == L_A == fdf->line.x_angle == 0.0f)
		fdf->line.z_angle -= 90.0f;
	if (fdf->line.x_angle == 360.0f || fdf->line.x_angle == -360.0f)
		fdf->line.x_angle = 0.0f;
	if (fdf->line.y_angle == 360.0f || fdf->line.y_angle == -360.0f)
		fdf->line.y_angle = 0.0f;
	if (fdf->line.z_angle == 360.0f || fdf->line.z_angle == -360.0f)
		fdf->line.z_angle = 0.0f;
	draw_map(fdf);
	return (0);
}

static int	rotate_events(int key, t_fdf *fdf)
{
	if (fdf->map.projection == 1)
		return (rotate_isometric(key, fdf));
	if (fdf->map.projection == 2)
		return (rotate_parallel(key, fdf));
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
	if (key == L_LEFT || key == L_UP || key == L_RIGHT || key == L_DOWN)
		return (rotate_events(key, fdf));
	else if (key == L_SPACE)
	{
		if (fdf->map.projection == 3)
			reset_map(fdf);
		else if (fdf->map.projection == 2)
		{
			fdf->map.projection == 3;
			fdf->line.x_angle = 10.0f;
			fdf->line.y_angle = 10.0f;
			fdf->line.z_angle = 0.0f;
		}
		else if (fdf->map.projection == 1)
		{
			fdf->map.projection = 2;
			fdf->line.x_angle = 0;
			fdf->line.y_angle = 0;
			fdf->line.z_angle = 0;
		}
	}
	draw_map(fdf);
	return (0);
}
