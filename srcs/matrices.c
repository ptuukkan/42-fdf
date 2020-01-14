/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:00:53 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/19 12:00:54 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_mat4	new_translation_matrix(double m12, double m13, double m14)
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
	m.m[12] = m12;
	m.m[13] = m13;
	m.m[14] = m14;
	m.m[15] = 1.0;
	return (m);
}

void			multiply_vertex(t_mat4 *m, t_vec4 *v)
{
	double	x;
	double	y;
	double	z;
	double	w;

	x = v->x;
	y = v->y;
	z = v->z;
	w = v->w;
	v->x = m->m[0] * x + m->m[4] * y + m->m[8] * z + m->m[12] * w;
	v->y = m->m[1] * x + m->m[5] * y + m->m[9] * z + m->m[13] * w;
	v->z = m->m[2] * x + m->m[6] * y + m->m[10] * z + m->m[14] * w;
	v->w = m->m[3] * x + m->m[7] * y + m->m[11] * z + m->m[15] * w;
}

void			translate(t_fdf *fdf, double m12, double m13, double m14)
{
	t_mat4	m;
	int		i;
	int		j;

	m = new_translation_matrix(m12, m13, m14);
	j = 0;
	while (j < fdf->map.height)
	{
		i = 0;
		while (i < fdf->map.width)
		{
			multiply_vertex(&m, &fdf->map.vertices[j][i]);
			i++;
		}
		j++;
	}
}
