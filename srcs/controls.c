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
	if (key == KEY_D)
		fdf->line.z_angle += 90.0f;
	if (key == KEY_A)
		fdf->line.z_angle -= 90.0f;
	if (fdf->line.z_angle == 405.0f || fdf->line.z_angle == -405.0f)
		fdf->line.z_angle = 45.0f;
	draw_map(fdf);
	return (0);
}

static int	rotate_parallel(int key, t_fdf *fdf)
{
	if (key == KEY_S && fdf->line.x_angle == 0.0f)
		fdf->line.x_angle = -90.f;
	else if (key == KEY_W && fdf->line.x_angle != 0.0f)
		fdf->line.x_angle = 0.0f;
	else if (key == KEY_D && fdf->line.x_angle != 0.0f)
		fdf->line.z_angle += 90.0f;
	else if (key == KEY_A && fdf->line.x_angle != 0.0f)
		fdf->line.z_angle -= 90.0f;
	else if (key == KEY_D && fdf->line.x_angle == 0.0f)
		fdf->line.z_angle += 90.0f;
	else if (key == KEY_A && fdf->line.x_angle == 0.0f)
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
	if (key == KEY_W)
		fdf->line.x_angle += 1.0f;
	else if (key == KEY_S)
		fdf->line.x_angle -= 1.0f;
	else if (key == KEY_D)
		fdf->line.z_angle += 1.0f;
	else if (key == KEY_A)
		fdf->line.z_angle -= 1.0f;
	else if (key == KEY_E)
		fdf->line.y_angle += 1.0f;
	else if (key == KEY_Q)
		fdf->line.y_angle -= 1.0f;
	if (fdf->line.x_angle == 360.0f || fdf->line.x_angle == -360.0f)
		fdf->line.x_angle = 0.0f;
	if (fdf->line.y_angle == 360.0f || fdf->line.y_angle == -360.0f)
		fdf->line.y_angle = 0.0f;
	if (fdf->line.z_angle == 360.0f || fdf->line.z_angle == -360.0f)
		fdf->line.z_angle = 0.0f;
	draw_map(fdf);
	return (0);
}

static int	scale_events(int key, t_fdf *fdf)
{
	if (key == KEY_J)
	{
		if (fdf->map.zoom > 1.0)
		{
			fdf->map.zoom *= 0.9;
			fdf->map.alt_mul *= 0.9;
		}
	}
	else if (key == KEY_K)
	{
		fdf->map.zoom *= 1.1;
		fdf->map.alt_mul *= 1.1;
	}
	else if (key == KEY_N)
	{
		if (fdf->map.alt_mul > 1.0)
			fdf->map.alt_mul *= 0.9;
	}
	else if (key == KEY_M)
		fdf->map.alt_mul *= 1.1;
	draw_map(fdf);
	return (0);
}

int			key_events(int key, t_fdf *fdf)
{
	printf("%x\n", key);
	if (key == KEY_ESC)
		exit(0);
	if (key == KEY_J || key == KEY_K || key == KEY_N || key == KEY_M)
		return (scale_events(key, fdf));
	if (key == KEY_A || key == KEY_W || key == KEY_D || key == KEY_S ||
		key == KEY_Q || key == KEY_E)
		return (rotate_events(key, fdf));
	else if (key == KEY_SPACE)
	{
		if (fdf->map.projection == 3)
			reset_map(fdf);
		else if (fdf->map.projection == 2)
		{
			fdf->map.projection = 3;
			fdf->line.x_angle = -70.0f;
			fdf->line.y_angle = 0.0f;
			fdf->line.z_angle = 0.0f;
		}
		else if (fdf->map.projection == 1)
		{
			fdf->map.projection = 2;
			fdf->line.x_angle = 0.0f;
			fdf->line.y_angle = 0.0f;
			fdf->line.z_angle = 0.0f;
		}
	}
	else if (key == KEY_R)
		reset_map(fdf);
	else if (key == 0x11 || key == 0x74)
	{
		fdf->map.projection = 4;
		fdf->test = 1;
		fdf->line.x_angle = 0.0f;
		fdf->line.y_angle = 0.0f;
		fdf->line.z_angle = 0.0f;
	}
	draw_map(fdf);
	return (0);
}
