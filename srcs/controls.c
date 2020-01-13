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

static int	toggle_view(t_fdf *fdf)
{
	if (fdf->map.projection == 3)
	{
		fdf->map.projection = 1;
		set_angles(fdf, -54.736f, 0.0f, 45.0f);
	}
	else if (fdf->map.projection == 2)
	{
		fdf->map.projection = 3;
		set_angles(fdf, -70.0f, 0.0f, 0.0f);
	}
	else if (fdf->map.projection == 1)
	{
		fdf->map.projection = 2;
		set_angles(fdf, 0.0f, 0.0f, 0.0f);
	}
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

static int	move_events(int key, t_fdf *fdf)
{
	if (key == KEY_LEFT)
		fdf->map.x_offset += 50;
	else if (key == KEY_UP)
		fdf->map.y_offset += 50;
	else if (key == KEY_RIGHT)
		fdf->map.x_offset -= 50;
	else if (key == KEY_DOWN)
		fdf->map.y_offset -= 50;
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
	if (key == KEY_LEFT || key == KEY_UP || key == KEY_RIGHT ||
		key == KEY_DOWN)
		return (move_events(key, fdf));
	else if (key == KEY_SPACE)
		toggle_view(fdf);
	else if (key == KEY_R)
		reset_map(fdf);
	else if (key == 0x11 || key == 0x74)
	{
		fdf->map.projection = 4;
		fdf->test = 1;
		set_angles(fdf, -70.0f, 0.0f, 0.0f);
	}
	draw_map(fdf);
	return (0);
}
