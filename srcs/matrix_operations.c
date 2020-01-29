/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:00:53 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/19 12:00:54 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void			multiply_vertices(t_fdf *fdf, t_mat4 *m)
{
	int	i;
	int	j;

	j = 0;
	while (j < fdf->map.height)
	{
		i = 0;
		while (i < fdf->map.width)
		{
			multiply_vertex(m, &fdf->map.vertices[j][i]);
			i++;
		}
		j++;
	}
}

t_mat4			multiply_matrix(t_mat4 *m1, t_mat4 *m2)
{
	t_mat4	new;

	int		o1;
	int		o2;
	int		n;

	n = 0;
	o1 = 0;
	o2 = 0;
	while (n < 16)
	{
		new.m[n] = 0;
		while (o1 < 16)
		{
			new.m[n] += m1->m[o1] * m2->m[o2];
			o1 += 4;
			o2 += 1;
		}
		n++;
		o1 = n % 4;
		o2 = (n / 4) * 4;
	}
	return (new);
}
