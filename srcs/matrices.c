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
}

void			translate(t_fdf *fdf, double trans_x, double trans_y, double trans_z)
{
	t_mat4	m;

	m = new_translation_matrix(trans_x, trans_y, trans_z);
	multiply_vertices(fdf, &m);
}

void			build_mvp_matrix(t_fdf *fdf)
{
	fdf->map.mvp = multiply_matrix(&fdf->map.projection, &fdf->map.moving);
	fdf->map.mvp = multiply_matrix(&fdf->map.mvp, &fdf->camera.matrix);
	fdf->map.mvp = multiply_matrix(&fdf->map.mvp, &fdf->map.rotation);
	fdf->map.mvp = multiply_matrix(&fdf->map.mvp, &fdf->map.scaling);

}

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

t_mat4			new_perspective_matrix(void)
{
	double	height = 1 * tan(45 / 2.0 * (M_PI / 180));
	double	width = height * (16 / 9);
	double	far = 500;
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
	m.m[10] = -(far + near) / (far - near);
	m.m[11] = -1.0;
	m.m[12] = 0.0;
	m.m[13] = 0.0;
	m.m[14] = -2 * far * near / (far - near);
	m.m[15] = 0.0;
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

void			construct_matrices(t_fdf *fdf)
{
	fdf->camera.matrix = new_translation_matrix(fdf->camera.x, fdf->camera.y,
			fdf->camera.z);
	fdf->map.rotation = new_rotation_matrix(fdf->map.x_angle * (M_PI / 180),
			fdf->map.y_angle * (M_PI / 180), fdf->map.z_angle * (M_PI / 180));
	fdf->map.moving = new_translation_matrix(fdf->map.x_offset,
			fdf->map.y_offset, 0);
	fdf->map.scaling = new_scaling_matrix(fdf->map.zoom, fdf->map.zoom,
			fdf->map.alt_mul * fdf->map.zoom);
	//fdf->map.projection = new_perspective_matrix();
	fdf->map.projection = new_ortho_matrix(fdf);
	fdf->map.viewport = new_viewport_matrix(fdf);
}

t_vec4			transform_vertex(t_fdf *fdf, t_vec4 *v)
{
	t_vec4	new;
	double	perc;

	new.x = v->x;
	new.y = v->y;
	new.z = v->z;
	new.w = v->w;
	perc = percent(fdf->map.bottom, new.z, fdf->map.peak);
	new.color = get_color(fdf->img.color_start, fdf->img.color_end, perc);
	multiply_vertex(&fdf->map.mvp, &new);
	multiply_vertex(&fdf->map.viewport, &new);
	//printf("x: %f y: %f z: %f w: %f\n", new.x, new.y, new.z, new.w);

	new.x = (int)(new.x + 0.5);
	new.y = (int)(new.y + 0.5);
	new.z = (int)(new.z + 0.5);
	return (new);
}
