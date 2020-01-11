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

void	quat_normalize(t_quat *q)
{
	double	mag;

	mag = sqrt(q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z);
	q->w /= mag;
	q->x /= mag;
	q->y /= mag;
	q->z /= mag;
}

void	rot_to_quat(t_quat *q, float az, float ay, float ax)
{
	float	cy;
	float	sy;
	float	cp;
	float	sp;
	float	cr;
	float	sr;

	ax = ax * (3.14f / 180.0f);
	ay = ay * (3.14f / 180.0f);
	az = az * (3.14f / 180.0f);
	cy = cos(az / 2.0f);
	sy = sin(az / 2.0f);
	cp = cos(ay / 2.0f);
	sp = sin(ay / 2.0f);
	cr = cos(ax / 2.0f);
	sr = sin(ax / 2.0f);
	q->w = cy * cp * cr + sy * sp * sr;
	q->x = cy * cp * sr - sy * sp * cr;
	q->y = sy * cp * sr + cy * sp * cr;
	q->z = sy * cp * cr - cy * sp * sr;
	quat_normalize(q);
}

t_quat	*quat_multiply(t_quat *q1, t_quat *q2)
{
	t_quat	*q;

	if (!(q = (t_quat *)ft_memalloc(sizeof(t_quat))))
		ft_exiterror("error", 3, 2);
	q->w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z;
	q->x = q1->w * q2->x + q1->x * q2->w + q1->y * q2->z - q1->z * q2->y;
	q->y = q1->w * q2->y + q1->y * q2->w + q1->z * q2->x - q2->x * q2->z;
	q->z = q1->w * q2->z + q1->z * q2->w + q1->x * q2->y - q1->y * q2->x;
	return (q);
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
	p0 = quat_multiply(q, p0);
	p1 = quat_multiply(q, p1);
	quat_conjugate(q);
	p0 = quat_multiply(p0, q);
	p1 = quat_multiply(p1, q);
	quat_to_vec(p0, p1, fdf);
}
