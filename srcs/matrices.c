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

void	print_matrix(t_mat4 m)
{
	printf("%-20f%-20f%-20f%-20f\n", m.m[0], m.m[4], m.m[8], m.m[12]);
	printf("%-20f%-20f%-20f%-20f\n", m.m[1], m.m[5], m.m[9], m.m[13]);
	printf("%-20f%-20f%-20f%-20f\n", m.m[2], m.m[6], m.m[10], m.m[14]);
	printf("%-20f%-20f%-20f%-20f\n\n", m.m[3], m.m[7], m.m[11], m.m[15]);
}

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
	m.m[9] = -sin(ax) * cz;
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
			//printf("new %d is old1 %d * old2 %d\n", n, o1, o2);
			o1 += 4;
			o2 += 1;
		}
		n++;
		o1 = n % 4;
		o2 = (n / 4) * 4;
	}
	return (new);

	/*
	new.m[0] = m1->m[0] * m2->m[0] + m1->m[4] * m2->m[1] + m1->m[8] * m2->m[2] + m1->m[12] * m2->m[3];
	new.m[1] = m1->m[1] * m2->m[0] + m1->m[5] * m2->m[1] + m1->m[9] * m2->m[2] + m1->m[13] * m2->m[3];
	new.m[2] = m1->m[2] * m2->m[0] + m1->m[6] * m2->m[1] + m1->m[10] * m2->m[2] + m1->m[14] * m2->m[3];
	new.m[3] = m1->m[3] * m2->m[0] + m1->m[7] * m2->m[1] + m1->m[11] * m2->m[2] + m1->m[15] * m2->m[3];
	new.m[4] = m1->m[0] * m2->m[4] + m1->m[4] * m2->m[5] + m1->m[8] * m2->m[6] + m1->m[12] * m2->m[7];
	new.m[5] = m1->m[1] * m2->m[4] + m1->m[5] * m2->m[5] + m1->m[9] * m2->m[6] + m1->m[13] * m2->m[7];
	new.m[6] = m1->m[2] * m2->m[4] + m1->m[6] * m2->m[5] + m1->m[10] * m2->m[6] + m1->m[14] * m2->m[7];
	new.m[7] = m1->m[3] * m2->m[4] + m1->m[7] * m2->m[5] + m1->m[11] * m2->m[6] + m1->m[15] * m2->m[7];
	new.m[8] = m1->m[0] * m2->m[8] + m1->m[4] * m2->m[9] + m1->m[8] * m2->m[10] + m1->m[12] * m2->m[11];
	new.m[9] = m1->m[1] * m2->m[8] + m1->m[5] * m2->m[9] + m1->m[9] * m2->m[10] + m1->m[13] * m2->m[11];
	new.m[10] = m1->m[2] * m2->m[8] + m1->m[6] * m2->m[9] + m1->m[10] * m2->m[10] + m1->m[14] * m2->m[11];
	new.m[11] = m1->m[3] * m2->m[8] + m1->m[7] * m2->m[9] + m1->m[11] * m2->m[10] + m1->m[15] * m2->m[11];
	new.m[12] = m1->m[0] * m2->m[12] + m1->m[4] * m2->m[13] + m1->m[8] * m2->m[14] + m1->m[12] * m2->m[15];
	new.m[13] = m1->m[1] * m2->m[12] + m1->m[5] * m2->m[13] + m1->m[9] * m2->m[14] + m1->m[13] * m2->m[15];
	new.m[14] = m1->m[2] * m2->m[12] + m1->m[6] * m2->m[13] + m1->m[10] * m2->m[14] + m1->m[14] * m2->m[15];
	new.m[15] = m1->m[3] * m2->m[12] + m1->m[7] * m2->m[13] + m1->m[11] * m2->m[14] + m1->m[15] * m2->m[15];
	*/
	return (new);
}

void			translate(t_fdf *fdf, double trans_x, double trans_y, double trans_z)
{
	t_mat4	m;

	m = new_translation_matrix(trans_x, trans_y, trans_z);
	multiply_vertices(fdf, &m);
}

void			build_mvp_matrix(t_fdf *fdf)
{
	//fdf->map.mvp = multiply_matrix(&fdf->map.projection, &fdf->map.moving);
	//fdf->map.mvp = multiply_matrix(&fdf->map.mvp, &fdf->map.rotation);
	//fdf->map.mvp = multiply_matrix(&fdf->map.mvp, &fdf->map.scaling);
	//fdf->map.mvp = multiply_matrix(&fdf->map.projection, &fdf->map.scaling);
	//fdf->map.mvp = fdf->map.scaling;
	//fdf->map.mvp = multiply_matrix(&fdf->map.scaling, &fdf->map.rotation);
	//fdf->map.mvp = multiply_matrix(&fdf->map.mvp, );

	fdf->map.mvp = fdf->map.moving;
	fdf->map.mvp = multiply_matrix(&fdf->map.mvp, &fdf->map.rotation);
	fdf->map.mvp = multiply_matrix(&fdf->map.mvp, &fdf->map.scaling);

}

t_mat4			new_ortho_matrix(t_fdf *fdf)
{
	double	width = 100;
	double	height = 100;
	double	far = 10;
	double	near = 1;
	t_mat4	m;

	m.m[0] = 1 / width;
	m.m[1] = 0.0;
	m.m[2] = 0.0;
	m.m[3] = 0.0;
	m.m[4] = 0.0;
	m.m[5] = 1 / height;
	m.m[6] = 0.0;
	m.m[7] = 0.0;
	m.m[8] = 0.0;
	m.m[9] = 0.0;
	m.m[10] = -2 / (far - near);
	m.m[11] = 0.0;
	m.m[12] = 0.0;
	m.m[13] = 0.0;
	m.m[14] = -(far + near) / (far - near);
	m.m[15] = 1.0;
	return (m);
}

void			construct_matrices(t_fdf *fdf)
{
	fdf->map.rotation = new_rotation_matrix(fdf->line.x_angle * (M_PI / 180),
			fdf->line.y_angle * (M_PI / 180), fdf->line.z_angle * (M_PI / 180));
	fdf->map.moving = new_translation_matrix(fdf->map.x_offset,
			fdf->map.y_offset, 0);
	fdf->map.scaling = new_scaling_matrix(fdf->map.zoom, fdf->map.zoom,
			fdf->map.zoom);
	fdf->map.projection = new_ortho_matrix(fdf);
}

t_vec4			viewport_transform(t_fdf *fdf, t_vec4 *v)
{
	t_mat4	ms;
	t_mat4	mt;
	t_vec4	new;
	t_mat4	m;

	new.x = v->x;
	new.y = v->y;
	new.z = v->z;
	new.w = v->w;
	multiply_vertex(&fdf->map.mvp, &new);
	multiply_vertex(&fdf->map.projection, &new);
	ms = new_scaling_matrix(100, 100, 1);
	print_matrix(ms);
	//multiply_vertex(&m, &new);
	mt = new_translation_matrix(WIN_WIDTH / 2.0, WIN_HEIGHT / 2.0, 0.0);
	print_matrix(mt);
	m = multiply_matrix(&mt, &ms);
	print_matrix(m);
	multiply_vertex(&m, &new);
	//printf("x: %f y: %f z: %f w: %f\n", new.x, new.y, new.z, new.w);

	new.x = (int)(new.x + 0.5);
	new.y = (int)(new.y + 0.5);
	return (new);
}
