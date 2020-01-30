/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_matrices.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:00:53 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/19 12:00:54 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4			new_ortho_matrix(t_fdf *fdf)
{
	t_mat4	m;

	m.m[0] = 2 / fdf->viewport.width;
	m.m[1] = 0.0;
	m.m[2] = 0.0;
	m.m[3] = 0.0;
	m.m[4] = 0.0;
	m.m[5] = 2 / fdf->viewport.height;
	m.m[6] = 0.0;
	m.m[7] = 0.0;
	m.m[8] = 0.0;
	m.m[9] = 0.0;
	m.m[10] = -2 / (fdf->viewport.far - fdf->viewport.near);
	m.m[11] = 0.0;
	m.m[12] = 0.0;
	m.m[13] = 0.0;
	m.m[14] = -(fdf->viewport.far + fdf->viewport.near) /
				(fdf->viewport.far - fdf->viewport.near);
	m.m[15] = 1.0;
	return (m);
}

t_mat4			new_perspective_matrix(t_fdf *fdf, double ar)
{
	double	tanhf;
	t_mat4	m;

	tanhf = tan(45.0 * 0.5 * (M_PI / 180));
	m.m[0] = 1.0 / (fdf->viewport.near * tanhf * ar);
	m.m[1] = 0.0;
	m.m[2] = 0.0;
	m.m[3] = 0.0;
	m.m[4] = 0.0;
	m.m[5] = 1.0 / (fdf->viewport.near * tanhf);
	m.m[6] = 0.0;
	m.m[7] = 0.0;
	m.m[8] = 0.0;
	m.m[9] = 0.0;
	m.m[10] = -(fdf->viewport.far + fdf->viewport.near) /
				(fdf->viewport.far - fdf->viewport.near);
	m.m[11] = -1.0;
	m.m[12] = 0.0;
	m.m[13] = 0.0;
	m.m[14] = -(2 * fdf->viewport.far * fdf->viewport.near) /
				(fdf->viewport.far - fdf->viewport.near);
	m.m[15] = 0.0;
	return (m);
}
