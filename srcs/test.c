/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 10:52:34 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/17 10:52:36 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


/*
void	rot_x(t_fdf *fdf)
{
	double	x_rad;

	x_rad = fdf->line.x_angle * (3.14 / 180);
	fdf->line.x_matrix[0] = 1;
	fdf->line.x_matrix[1] = 0;
	fdf->line.x_matrix[2] = 0;
	fdf->line.x_matrix[3] = 0;
	fdf->line.x_matrix[4] = cos(x_rad);
	fdf->line.x_matrix[5] = sin(x_rad);
	fdf->line.x_matrix[6] = 0;
	fdf->line.x_matrix[7] = -sin(x_rad);
	fdf->line.x_matrix[8] = cos(x_rad);
}

void	rot_y(t_fdf *fdf)
{
	double	y_rad;

	y_rad = fdf->line.y_angle * (3.14 / 180);
	fdf->line.y_matrix[0] = cos(y_rad);
	fdf->line.y_matrix[1] = 0;
	fdf->line.y_matrix[2] = -sin(y_rad);
	fdf->line.y_matrix[3] = 0;
	fdf->line.y_matrix[4] = 1;
	fdf->line.y_matrix[5] = 0;
	fdf->line.y_matrix[6] = sin(y_rad);
	fdf->line.y_matrix[7] = 0;
	fdf->line.y_matrix[8] = cos(y_rad);
}

void	rot_z(t_fdf *fdf)
{
	fdf->line.z_matrix[0] = cos(fdf->line.z_angle);
	fdf->line.z_matrix[1] = sin(fdf->line.z_angle);
	fdf->line.z_matrix[2] = 0;
	fdf->line.z_matrix[3] = -sin(fdf->line.z_angle);
	fdf->line.z_matrix[4] = cos(fdf->line.z_angle);
	fdf->line.z_matrix[5] = 0;
	fdf->line.z_matrix[6] = 0;
	fdf->line.z_matrix[7] = 0;
	fdf->line.z_matrix[8] = 1;
}

void	multiply_matrix(t_fdf *fdf, double my[9], double mx[9])
{
	int	x0;
	int	y0;
	int	z0;
	int	x1;
	int	y1;
	int	z1;

	x0 = fdf->line.x0;
	y0 = fdf->line.y0;
	z0 = fdf->line.z0;
	x1 = fdf->line.x1;
	y1 = fdf->line.y1;
	z1 = fdf->line.z1;

	fdf->line.x0 = x0 * my[0] + y0 * my[3] + z0 * my[6];
	fdf->line.y0 = x0 * my[1] + y0 * my[4] + z0 * my[7];
	fdf->line.z0 = x0 * my[2] + y0 * my[5] + z0 * my[8];
	fdf->line.x1 = x1 * my[0] + y1 * my[3] + z1 * my[6];
	fdf->line.y1 = x1 * my[1] + y1 * my[4] + z1 * my[7];
	fdf->line.z1 = x1 * my[2] + y1 * my[5] + z1 * my[8];

	x0 = fdf->line.x0;
	y0 = fdf->line.y0;
	z0 = fdf->line.z0;
	x1 = fdf->line.x1;
	y1 = fdf->line.y1;
	z1 = fdf->line.z1;

	fdf->line.x0 = x0 * mx[0] + y0 * mx[3] + z0 * mx[6];
	fdf->line.y0 = x0 * mx[1] + y0 * mx[4] + z0 * mx[7];
	fdf->line.z0 = x0 * mx[2] + y0 * mx[5] + z0 * mx[8];
	fdf->line.x1 = x1 * mx[0] + y1 * mx[3] + z1 * mx[6];
	fdf->line.y1 = x1 * mx[1] + y1 * mx[4] + z1 * mx[7];
	fdf->line.z1 = x1 * mx[2] + y1 * mx[5] + z1 * mx[8];
}



void	rotate(t_fdf *fdf)
{
	rot_x(fdf);
	rot_y(fdf);
	rot_z(fdf);
	multiply_matrix(fdf, fdf->line.y_matrix, fdf->line.x_matrix);
	//multiply_matrix(fdf, fdf->line.y_matrix, fdf->line.x_matrix);
	//calculate_point(fdf, 1);
}
*/

void	plot_sq(t_fdf *fdf, int x0, int y0, int z0, int x1, int y1, int z1)
{
	/*
	x0 = (x0 - fdf->map.width / 2) * fdf->map.zoom;
	y0 = (y0 - fdf->map.height / 2) * fdf->map.zoom;
	x1 = (x1 - fdf->map.width / 2) * fdf->map.zoom;
	y1 = (y1 - fdf->map.height / 2) * fdf->map.zoom;
	*/


	x0 = x0 * fdf->map.zoom;
	y0 = y0 * fdf->map.zoom;
	x1 = x1 * fdf->map.zoom;
	y1 = y1 * fdf->map.zoom;
	z0 = z0 * fdf->map.zoom;
	z1 = z1 * fdf->map.zoom;



	fdf->line.x0 = x0;
	fdf->line.y0 = y0;
	fdf->line.z0 = z0;
	fdf->line.x1 = x1;
	fdf->line.y1 = y1;
	fdf->line.z1 = z1;
	rotate(fdf, fdf->line.x_angle, fdf->line.y_angle, fdf->line.z_angle);


	fdf->line.x0 += WIN_WIDTH / 2;
	fdf->line.x1 += WIN_WIDTH / 2;
	fdf->line.y0 += WIN_HEIGHT / 2;
	fdf->line.y1 += WIN_HEIGHT / 2;
}

void	draw_sq(t_fdf *fdf)
{
	if (!(fdf->mlx.img_ptr = mlx_new_image(fdf->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT)))
		ft_exiterror("Image creation failed", 8, 2);
	fdf->img.img_data = mlx_get_data_addr(fdf->mlx.img_ptr, &fdf->img.bpp, &fdf->img.line_size, &fdf->img.endian);

	plot_sq(fdf, -10, 10, 10, 10, 10, 10);
	draw_line(fdf);
	plot_sq(fdf, -10, 10, 10, -10, -10, 10);
	draw_line(fdf);
	plot_sq(fdf, 10, 10, 10, 10, -10, 10);
	draw_line(fdf);
	plot_sq(fdf, -10, -10, 10, 10, -10, 10);
	draw_line(fdf);

	plot_sq(fdf, -10, 10, -10, 10, 10, -10);
	draw_line(fdf);
	plot_sq(fdf, -10, 10, -10, -10, -10, -10);
	draw_line(fdf);
	plot_sq(fdf, 10, 10, -10, 10, -10, -10);
	draw_line(fdf);
	plot_sq(fdf, -10, -10, -10, 10, -10, -10);
	draw_line(fdf);


	plot_sq(fdf, -10, 10, 10, -10, 10, -10);
	draw_line(fdf);
	plot_sq(fdf, 10, 10, 10, 10, 10, -10);
	draw_line(fdf);
	plot_sq(fdf, -10, -10, 10, -10, -10, -10);
	draw_line(fdf);
	plot_sq(fdf, 10, -10, 10, 10, -10, -10);
	draw_line(fdf);


	mlx_put_image_to_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, fdf->mlx.img_ptr, 0, 0);
	mlx_string_put(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, 10, 10, 0xFFFFFF, "x degrees:");
	mlx_string_put(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, 120, 10, 0xFFFFFF, ft_itoa(fdf->line.x_angle));
	mlx_string_put(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, 10, 25, 0xFFFFFF, "y degrees:");
	mlx_string_put(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, 120, 25, 0xFFFFFF, ft_itoa(fdf->line.y_angle));
	mlx_string_put(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, 10, 40, 0xFFFFFF, "z degrees:");
	mlx_string_put(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, 120, 40, 0xFFFFFF, ft_itoa(fdf->line.z_angle));
	mlx_destroy_image(fdf->mlx.mlx_ptr, fdf->mlx.img_ptr);
}
