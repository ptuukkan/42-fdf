/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_controls.c                                  :+:      :+:    :+:   */
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
		fdf->map.z_angle += 90.0f;
	if (key == KEY_A)
		fdf->map.z_angle -= 90.0f;
	if (fdf->map.z_angle == 405.0f || fdf->map.z_angle == -405.0f)
		fdf->map.z_angle = 45.0f;
	fdf->map.rotation = new_rotation_matrix(fdf->map.x_angle * (M_PI / 180), fdf->map.y_angle * (M_PI / 180), fdf->map.z_angle * (M_PI / 180));
	draw_map(fdf);
	return (0);
}

static int	rotate_parallel(int key, t_fdf *fdf)
{
	if (key == KEY_S && fdf->map.x_angle == 0.0f)
		fdf->map.x_angle = 90.f;
	else if (key == KEY_W && fdf->map.x_angle != 0.0f)
		fdf->map.x_angle = 0.0f;
	else if (key == KEY_D && fdf->map.x_angle != 0.0f)
		fdf->map.z_angle += 90.0f;
	else if (key == KEY_A && fdf->map.x_angle != 0.0f)
		fdf->map.z_angle -= 90.0f;
	else if (key == KEY_D && fdf->map.x_angle == 0.0f)
		fdf->map.z_angle += 90.0f;
	else if (key == KEY_A && fdf->map.x_angle == 0.0f)
		fdf->map.z_angle -= 90.0f;
	if (fdf->map.x_angle == 360.0f || fdf->map.x_angle == -360.0f)
		fdf->map.x_angle = 0.0f;
	if (fdf->map.y_angle == 360.0f || fdf->map.y_angle == -360.0f)
		fdf->map.y_angle = 0.0f;
	if (fdf->map.z_angle == 360.0f || fdf->map.z_angle == -360.0f)
		fdf->map.z_angle = 0.0f;
	fdf->map.rotation = new_rotation_matrix(fdf->map.x_angle * (M_PI / 180), fdf->map.y_angle * (M_PI / 180), fdf->map.z_angle * (M_PI / 180));
	draw_map(fdf);
	return (0);
}

int			rotate_events(int key, t_fdf *fdf)
{
	if (fdf->map.view == 1)
		return (rotate_isometric(key, fdf));
	if (fdf->map.view == 2)
		return (rotate_parallel(key, fdf));
	if (key == KEY_W)
		fdf->map.x_angle += 1.0f;
	else if (key == KEY_S)
		fdf->map.x_angle -= 1.0f;
	else if (key == KEY_D)
		fdf->map.z_angle += 1.0f;
	else if (key == KEY_A)
		fdf->map.z_angle -= 1.0f;
	else if (key == KEY_E)
		fdf->map.y_angle += 1.0f;
	else if (key == KEY_Q)
		fdf->map.y_angle -= 1.0f;
	if (fdf->map.x_angle == 360.0f || fdf->map.x_angle == -360.0f)
		fdf->map.x_angle = 0.0f;
	if (fdf->map.y_angle == 360.0f || fdf->map.y_angle == -360.0f)
		fdf->map.y_angle = 0.0f;
	if (fdf->map.z_angle == 360.0f || fdf->map.z_angle == -360.0f)
		fdf->map.z_angle = 0.0f;
	fdf->map.rotation = new_rotation_matrix(fdf->map.x_angle * (M_PI / 180), fdf->map.y_angle * (M_PI / 180), fdf->map.z_angle * (M_PI / 180));
	draw_map(fdf);
	return (0);
}
