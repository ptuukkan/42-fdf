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
		fdf->map.projection = new_ortho_matrix(fdf);
		set_angles(fdf, 54.736f, 0.0f, 45.0f);
	}
	else if (fdf->map.view == 2)
	{
		fdf->map.view = 3;
		fdf->map.projection = new_perspective_matrix(fdf);
		set_angles(fdf, 54.736f, 0.0f, 45.0f);
	}
	else if (fdf->map.view == 1)
	{
		fdf->map.view = 2;
		fdf->map.projection = new_ortho_matrix(fdf);
		set_angles(fdf, 0.0f, 0.0f, 0.0f);
	}
	fdf->map.rotation = new_rotation_matrix(fdf->map.x_angle * (M_PI / 180),
		fdf->map.y_angle * (M_PI / 180), fdf->map.z_angle * (M_PI / 180));
	return (0);
}

static int	scale_events(int key, t_fdf *fdf)
{
	if (key == KEY_J)
	{
		fdf->map.zoom *= 0.9;
		//fdf->map.alt_mul *= 0.9;
	}
	else if (key == KEY_K)
	{
		fdf->map.zoom *= 1.1;
		//fdf->map.alt_mul *= 1.1;
	}
	else if (key == KEY_N)
	{
		fdf->map.alt_mul -= 0.01;
	}
	else if (key == KEY_M)
		fdf->map.alt_mul += 0.01;
	fdf->map.scaling = new_scaling_matrix(fdf->map.zoom, fdf->map.zoom,
			fdf->map.alt_mul * fdf->map.zoom);
	draw_map(fdf);
	return (0);
}

static int	move_events(int key, t_fdf *fdf)
{
	if (key == KEY_LEFT)
		fdf->map.x_offset += 10;
	else if (key == KEY_UP)
		fdf->map.y_offset += 10;
	else if (key == KEY_RIGHT)
		fdf->map.x_offset -= 10;
	else if (key == KEY_DOWN)
		fdf->map.y_offset -= 10;
	fdf->map.moving = new_translation_matrix(fdf->map.x_offset, fdf->map.y_offset, 0.0);
	draw_map(fdf);
	return (0);
}

int	camera_events(int key, t_fdf *fdf)
{
	if (key == KEY_NPP)
		fdf->camera.z += 5;
	else if (key == KEY_NPM)
		fdf->camera.z -= 5;
	if (key == KEY_NP4)
		fdf->camera.x += 10;
	if (key == KEY_NP6)
		fdf->camera.x -= 10;
	if (key == KEY_NP8)
		fdf->camera.y -= 10;
	if (key == KEY_NP5)
		fdf->camera.y += 10;
	fdf->camera.matrix = new_translation_matrix(fdf->camera.x, fdf->camera.y,
			fdf->camera.z);
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
	else if (key >= KEY_NPP && key <= KEY_NP9)
		return (camera_events(key, fdf));
	else if (key == KEY_R)
		reset_map(fdf);
	else if (key == KEY_Y)
	{
		if (fdf->viewport.near > 1)
		{
			fdf->viewport.near -= 1;
			construct_matrices(fdf);
		}
	}
	else if (key == KEY_U)
	{
		fdf->viewport.near += 1;
		construct_matrices(fdf);
	}
	else if (key == KEY_G)
	{
		fdf->viewport.far -= 10;
		construct_matrices(fdf);
	}
	else if (key == KEY_H)
	{
		fdf->viewport.far += 10;
		construct_matrices(fdf);
	}
	draw_map(fdf);
	return (0);
}
