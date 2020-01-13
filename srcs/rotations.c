/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:00:53 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/19 12:00:54 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_x(t_fdf *fdf, float ax)
{
	int	y;
	int	z;

	y = fdf->line.y0;
	z = fdf->line.z0;
	fdf->line.y0 = y * cos(ax) + z * sin(ax);
	fdf->line.z0 = -y * sin(ax) + z * cos(ax);
	y = fdf->line.y1;
	z = fdf->line.z1;
	fdf->line.y1 = y * cos(ax) + z * sin(ax);
	fdf->line.z1 = -y * sin(ax) + z * cos(ax);
}

static void	rotate_y(t_fdf *fdf, float ay)
{
	int	x;
	int	z;

	x = fdf->line.x0;
	z = fdf->line.z0;
	fdf->line.x0 = x * cos(ay) + z * sin(ay);
	fdf->line.z0 = -x * sin(ay) + z * cos(ay);
	x = fdf->line.x1;
	z = fdf->line.z1;
	fdf->line.x1 = x * cos(ay) + z * sin(ay);
	fdf->line.z1 = -x * sin(ay) + z * cos(ay);
}

static void	rotate_z(t_fdf *fdf, float az)
{
	int	x;
	int	y;

	x = fdf->line.x0;
	y = fdf->line.y0;
	fdf->line.x0 = x * cos(az) - y * sin(az);
	fdf->line.y0 = x * sin(az) + y * cos(az);
	x = fdf->line.x1;
	y = fdf->line.y1;
	fdf->line.x1 = x * cos(az) - y * sin(az);
	fdf->line.y1 = x * sin(az) + y * cos(az);
}

void		rotate(t_fdf *fdf, float ax, float ay, float az)
{
	ax = ax * (M_PI / 180);
	ay = ay * (M_PI / 180);
	az = az * (M_PI / 180);



	rotate_z(fdf, az);
	rotate_y(fdf, ay);
	rotate_x(fdf, ax);


}
