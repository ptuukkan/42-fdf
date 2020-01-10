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
	if (key == L_D || key == M_D)
		fdf->line.z_angle += 90.0f;
	if (key == L_A || key == M_D)
		fdf->line.z_angle -= 90.0f;
	if (fdf->line.z_angle == 405.0f || fdf->line.z_angle == -405.0f)
		fdf->line.z_angle = 45.0f;
	draw_map(fdf);
	return (0);
}

static int	rotate_parallel(int key, t_fdf *fdf)
{
	if ((key == L_S || key == M_S) && fdf->line.x_angle == 0.0f)
		fdf->line.x_angle = -90.f;
	else if ((key == L_W || key == M_W) && fdf->line.x_angle != 0.0f)
		fdf->line.x_angle = 0.0f;
	else if ((key == L_D || key == M_D) && fdf->line.x_angle != 0.0f)
		fdf->line.z_angle += 90.0f;
	else if ((key == L_A || key == M_A) && fdf->line.x_angle != 0.0f)
		fdf->line.z_angle -= 90.0f;
	else if ((key == L_D || key == M_D) && fdf->line.x_angle == 0.0f)
		fdf->line.z_angle += 90.0f;
	else if ((key == L_A || key == M_A) && fdf->line.x_angle == 0.0f)
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
	if (key == L_W || key == M_W)
		fdf->line.x_angle += 1.0f;
	else if (key == L_S || key == M_S)
		fdf->line.x_angle -= 1.0f;
	else if (key == L_D || key == M_D)
		fdf->line.z_angle += 1.0f;
	else if (key == L_A || key == M_A)
		fdf->line.z_angle -= 1.0f;
	else if (key == L_E || key == 0xe)
		fdf->line.z_angle += 1.0f;
	else if (key == L_Q || key == M_Q)
		fdf->line.z_angle -= 1.0f;
	if (fdf->line.x_angle == 360.0f || fdf->line.x_angle == -360.0f)
		fdf->line.x_angle = 0.0f;
	if (fdf->line.y_angle == 360.0f || fdf->line.y_angle == -360.0f)
		fdf->line.y_angle = 0.0f;
	if (fdf->line.z_angle == 360.0f || fdf->line.z_angle == -360.0f)
		fdf->line.z_angle = 0.0f;
	draw_map(fdf);
	return (0);
}

static int	zoom_events(int key, t_fdf *fdf)
{
	if (key == L_J || key == M_J)
	{
		if (fdf->map.zoom > 1.0)
		{
			fdf->map.zoom *= 0.9;
			fdf->map.alt_mul *= 0.9;
		}
	}
	else if (key == L_K || key == M_K)
	{
		fdf->map.zoom *= 1.1;
		fdf->map.alt_mul *= 1.1;
	}
	else if (key == L_N || key == M_N)
	{
		if (fdf->map.alt_mul > 1.0)
			fdf->map.alt_mul *= 0.9;
	}
	else if (key == L_M || key == M_M)
		fdf->map.alt_mul *= 1.1;
	draw_map(fdf);
	return (0);
}

int			key_events(int key, t_fdf *fdf)
{
	printf("%x\n", key);
	if (key == M_ESC || key == L_ESC)
		exit(0);
	if (key == L_J || key == L_K || key == L_N || key == L_M ||
		key == M_J || key == M_K || key == M_N || key == M_M)
		return (zoom_events(key, fdf));
	if (key == L_A || key == L_W || key == L_D || key == L_S ||
		key == M_A || key == M_W || key == M_D || key == M_S ||
		key == M_Q || key == 0xe || key == L_Q || key == L_E)
		return (rotate_events(key, fdf));
	else if (key == L_SPACE || key == M_SPACE)
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
	else if (key == M_R || key == L_R)
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
