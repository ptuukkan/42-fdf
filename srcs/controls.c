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
	if (fdf->map.view == 3)
	{
		fdf->map.view = 1;
		fdf->mvp.projection = new_ortho_matrix(fdf);
		set_angles(fdf, 54.736f, 0.0f, 45.0f);
	}
	else if (fdf->map.view == 2)
	{
		fdf->map.view = 3;
		fdf->mvp.projection = new_perspective_matrix(fdf, 16.0 / 9.0);
		set_angles(fdf, 54.736f, 0.0f, 45.0f);
	}
	else if (fdf->map.view == 1)
	{
		fdf->map.view = 2;
		fdf->mvp.projection = new_ortho_matrix(fdf);
		set_angles(fdf, 0.0f, 0.0f, 0.0f);
	}
	fdf->mvp.rot.matrix = new_rotation_matrix(fdf->mvp.rot.x * (M_PI / 180),
		fdf->mvp.rot.y * (M_PI / 180), fdf->mvp.rot.z * (M_PI / 180));
	draw_map(fdf);
	return (0);
}

static int	scale_events(int key, t_fdf *fdf)
{
	if (key == KEY_J)
		fdf->map.zoom *= 0.9;
	else if (key == KEY_K)
		fdf->map.zoom *= 1.1;
	else if (key == KEY_N)
		fdf->map.alt_mul -= 0.01;
	else if (key == KEY_M)
		fdf->map.alt_mul += 0.01;
	fdf->mvp.scale = new_scaling_matrix(fdf->map.zoom, fdf->map.zoom,
			fdf->map.alt_mul * fdf->map.zoom);
	draw_map(fdf);
	return (0);
}

static int	move_events(int key, t_fdf *fdf)
{
	if (key == KEY_LEFT)
		fdf->mvp.x_offset += 10;
	else if (key == KEY_UP)
		fdf->mvp.y_offset += 10;
	else if (key == KEY_RIGHT)
		fdf->mvp.x_offset -= 10;
	else if (key == KEY_DOWN)
		fdf->mvp.y_offset -= 10;
	fdf->mvp.move = new_translation_matrix(fdf->mvp.x_offset,
		fdf->mvp.y_offset, 0);
	draw_map(fdf);
	return (0);
}

int			close_program(t_fdf *fdf)
{
	(void)fdf;
	exit(0);
}

int			key_events(int key, t_fdf *fdf)
{
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
		return (toggle_view(fdf));
	else if (key == KEY_R)
		reset_map(fdf);
	draw_map(fdf);
	return (0);
}
