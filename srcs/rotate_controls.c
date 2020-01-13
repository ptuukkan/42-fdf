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

int			rotate_events(int key, t_fdf *fdf)
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
