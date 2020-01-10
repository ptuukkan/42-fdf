/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:00:53 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/19 12:00:54 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_quat	*rot_to_quat(t_quat *q, float az, float ay, float ax)
{
	float	cy;
	float	sy;
	float	cp;
	float	sp;
	float	cr;

	ax = ax * (3.14 / 180);
	ay = ay * (3.14 / 180);
	az = az * (3.14 / 180);
	cy = cos(az / 2);
	sy = sin(az / 2);
	cp = cos(ay / 2);
	sp = sin(ay / 2);
	cr = cos(ax / 2);
	q->w = cy * cp * cr + sy * sp * sin(ax / 2);
	q->x = cy * cp * sin(ax / 2) - sy * sp * cr;
	q->y = sy * cp * sin(ax / 2) + cy * sp * cr;
	q->z = sy * cp * cr - cy * sp * sin(ax / 2);
}

void	quat_multiply(t_quat *q1, t_quat *q2)
{
	float	w;
	float	x;
	float	y;
	float	z;

	w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z;
	x = q1->w * q2->x + q1->x * q2->w + q1->y * q2->z - q1->z * q2->y;
	y = q1->w * q2->y + q1->y * q2->w + q1->z * q2->x - q2->x * q2->z;
	z = q1->w * q2->z + q1->z * q2->w + q1->x * q2->y - q1->y * q2->x;
	q1->w = w;
	q1->x = x;
	q1->y = y;
	q1->z = z;
}

void	quat_conjugate(t_quat *q)
{
	q->x = -q->x;
	q->y = -q->y;
	q->z = -q->z;
}

void	vec_to_quat(t_quat *p, int x, int y, int z)
{
	p->w = 0;
	p->x = x;
	p->y = y;
	p->z = z;
}

void	quat_to_vec(t_quat *p0, t_quat *p1, t_fdf *fdf)
{
	fdf->line.x0 = p0->x;
	fdf->line.y0 = p0->y;
	fdf->line.z0 = p0->z;
	fdf->line.x1 = p1->x;
	fdf->line.y1 = p1->y;
	fdf->line.z1 = p1->z;
}

void	quat_rotate(t_fdf *fdf)
{
	t_quat	*q;
	t_quat	*p0;
	t_quat	*p1;

	if (!(p0 = (t_quat *)ft_memalloc(sizeof(t_quat))))
		ft_exiterror("error", 3, 2);
	if (!(p1 = (t_quat *)ft_memalloc(sizeof(t_quat))))
		ft_exiterror("error", 3, 2);
	if (!(q = (t_quat *)ft_memalloc(sizeof(t_quat))))
		ft_exiterror("error", 3, 2);
	rot_to_quat(q, fdf->line.z_angle, fdf->line.y_angle, fdf->line.x_angle);
	vec_to_quat(p0, fdf->line.x0, fdf->line.y0, fdf->line.z0);
	vec_to_quat(p1, fdf->line.x1, fdf->line.y1, fdf->line.z1);
	quat_multiply(p0, q);
	quat_multiply(p1, q);
	quat_conjugate(q);
	quat_multiply(p0, q);
	quat_multiply(p1, q);
	quat_to_vec(p0, p1, fdf);
}
