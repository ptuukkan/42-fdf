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

void		set_angles(t_fdf *fdf, double ax, double ay, double az)
{
	fdf->mvp.rot.x = ax;
	fdf->mvp.rot.y = ay;
	fdf->mvp.rot.z = az;
}

static int	rotate_isometric(int key, t_fdf *fdf)
{
	if (key == KEY_D)
		fdf->mvp.rot.z += 90.0f;
	if (key == KEY_A)
		fdf->mvp.rot.z -= 90.0f;
	if (fdf->mvp.rot.z == 405.0f || fdf->mvp.rot.z == -405.0f)
		fdf->mvp.rot.z = 45.0f;
	fdf->mvp.rot.matrix = new_rotation_matrix(fdf->mvp.rot.x * (M_PI / 180),
		fdf->mvp.rot.y * (M_PI / 180), fdf->mvp.rot.z * (M_PI / 180));
	draw_map(fdf);
	return (0);
}

static int	rotate_parallel(int key, t_fdf *fdf)
{
	if (key == KEY_S && fdf->mvp.rot.x == 0.0f)
		fdf->mvp.rot.x = 90.f;
	else if (key == KEY_W && fdf->mvp.rot.x != 0.0f)
		fdf->mvp.rot.x = 0.0f;
	else if (key == KEY_D && fdf->mvp.rot.x != 0.0f)
		fdf->mvp.rot.z += 90.0f;
	else if (key == KEY_A && fdf->mvp.rot.x != 0.0f)
		fdf->mvp.rot.z -= 90.0f;
	else if (key == KEY_D && fdf->mvp.rot.x == 0.0f)
		fdf->mvp.rot.z += 90.0f;
	else if (key == KEY_A && fdf->mvp.rot.x == 0.0f)
		fdf->mvp.rot.z -= 90.0f;
	if (fdf->mvp.rot.x == 360.0f || fdf->mvp.rot.x == -360.0f)
		fdf->mvp.rot.x = 0.0f;
	if (fdf->mvp.rot.y == 360.0f || fdf->mvp.rot.y == -360.0f)
		fdf->mvp.rot.y = 0.0f;
	if (fdf->mvp.rot.z == 360.0f || fdf->mvp.rot.z == -360.0f)
		fdf->mvp.rot.z = 0.0f;
	fdf->mvp.rot.matrix = new_rotation_matrix(fdf->mvp.rot.x * (M_PI / 180),
			fdf->mvp.rot.y * (M_PI / 180), fdf->mvp.rot.z * (M_PI / 180));
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
		fdf->mvp.rot.x += 1.0f;
	else if (key == KEY_S)
		fdf->mvp.rot.x -= 1.0f;
	else if (key == KEY_D)
		fdf->mvp.rot.z += 1.0f;
	else if (key == KEY_A)
		fdf->mvp.rot.z -= 1.0f;
	else if (key == KEY_E)
		fdf->mvp.rot.y += 1.0f;
	else if (key == KEY_Q)
		fdf->mvp.rot.y -= 1.0f;
	if (fdf->mvp.rot.x == 360.0f || fdf->mvp.rot.x == -360.0f)
		fdf->mvp.rot.x = 0.0f;
	if (fdf->mvp.rot.y == 360.0f || fdf->mvp.rot.y == -360.0f)
		fdf->mvp.rot.y = 0.0f;
	if (fdf->mvp.rot.z == 360.0f || fdf->mvp.rot.z == -360.0f)
		fdf->mvp.rot.z = 0.0f;
	fdf->mvp.rot.matrix = new_rotation_matrix(fdf->mvp.rot.x * (M_PI / 180),
		fdf->mvp.rot.y * (M_PI / 180), fdf->mvp.rot.z * (M_PI / 180));
	draw_map(fdf);
	return (0);
}
