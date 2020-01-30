/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_matrices.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:00:53 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/19 12:00:54 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4	new_translation_matrix(double trans_x, double trans_y, double trans_z)
{
	t_mat4	m;

	m.m[0] = 1.0;
	m.m[1] = 0.0;
	m.m[2] = 0.0;
	m.m[3] = 0.0;
	m.m[4] = 0.0;
	m.m[5] = 1.0;
	m.m[6] = 0.0;
	m.m[7] = 0.0;
	m.m[8] = 0.0;
	m.m[9] = 0.0;
	m.m[10] = 1.0;
	m.m[11] = 0.0;
	m.m[12] = trans_x;
	m.m[13] = trans_y;
	m.m[14] = trans_z;
	m.m[15] = 1.0;
	return (m);
}

t_mat4	new_rotation_matrix(double ax, double ay, double az)
{
	t_mat4	m;
	double	cx;
	double	cy;
	double	cz;

	cx = cos(ax);
	cy = cos(ay);
	cz = cos(az);
	m.m[0] = cy * cz;
	m.m[1] = sin(ax) * sin(ay) * cz + cx * sin(az);
	m.m[2] = -cx * sin(ay) * cz + sin(ax) * sin(az);
	m.m[3] = 0.0;
	m.m[4] = -cy * sin(az);
	m.m[5] = -sin(ax) * sin(ay) * sin(az) + cx * cz;
	m.m[6] = cx * sin(ay) * sin(az) + sin(ax) * cz;
	m.m[7] = 0.0;
	m.m[8] = sin(ay);
	m.m[9] = -sin(ax) * cy;
	m.m[10] = cx * cy;
	m.m[11] = 0.0;
	m.m[12] = 0.0;
	m.m[13] = 0.0;
	m.m[14] = 0.0;
	m.m[15] = 1.0;
	return (m);
}

t_mat4	new_scaling_matrix(double scale_x, double scale_y, double scale_z)
{
	t_mat4	m;

	m.m[0] = scale_x;
	m.m[1] = 0.0;
	m.m[2] = 0.0;
	m.m[3] = 0.0;
	m.m[4] = 0.0;
	m.m[5] = scale_y;
	m.m[6] = 0.0;
	m.m[7] = 0.0;
	m.m[8] = 0.0;
	m.m[9] = 0.0;
	m.m[10] = scale_z;
	m.m[11] = 0.0;
	m.m[12] = 0.0;
	m.m[13] = 0.0;
	m.m[14] = 0.0;
	m.m[15] = 1.0;
	return (m);
}

t_mat4			new_viewport_matrix(t_fdf *fdf)
{
	t_mat4	mt;
	t_mat4	ms;

	mt = new_translation_matrix(WIN_WIDTH / 2 + 100, WIN_HEIGHT / 2 + 30, 0.0);
	ms = new_scaling_matrix(fdf->viewport.width / 2, fdf->viewport.height / 2,
			(fdf->viewport.far - fdf->viewport.near) / 2);
	return (multiply_matrix(&mt, &ms));
}
