/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:07:25 by ptuukkan          #+#    #+#             */
/*   Updated: 2020/01/13 16:07:26 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	percent(int start, int current, int end)
{
	double perc;
	if (current == end)
		return (1.0f);
	else
		perc = ((float)current - (float)start) / ((float)end - (float)start);
	return(perc);
}

t_color	get_color(t_color color_start, t_color color_end, double perc)
{
	t_color	new;

	new.red = color_start.red + perc * (color_end.red - color_start.red);
	new.green = color_start.green + perc * (color_end.green - color_start.green);
	new.blue = color_start.blue + perc * (color_end.blue - color_start.blue);
	return (new);
}

void	init_color(t_fdf *fdf)
{

	fdf->img.color_start.red = 0x57;
	fdf->img.color_start.green = 0x34;
	fdf->img.color_start.blue = 0x0;
	fdf->img.color_end.red = 0xFF;
	fdf->img.color_end.green = 0xE0;
	fdf->img.color_end.blue = 0xC9;

	/*
	fdf->img.color_start.red = 0x3a;
	fdf->img.color_start.green = 0x00;
	fdf->img.color_start.blue = 0x80;
	fdf->img.color_end.red = 0x00;
	fdf->img.color_end.green = 0xff;
	fdf->img.color_end.blue = 0x2a;
	*/
}
