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

double	percent(double start, double current, double end)
{
	double perc;

	if (current == end)
		return (1.0f);
	else
		perc = (current - start) / (end - start);
	return (perc);
}

t_color	get_color(t_color color_start, t_color color_end, double perc)
{
	t_color	new;

	new.red = color_start.red + perc * (color_end.red - color_start.red);
	new.green = color_start.green + perc *
		(color_end.green - color_start.green);
	new.blue = color_start.blue + perc * (color_end.blue - color_start.blue);
	return (new);
}

t_color	read_color(char **line)
{
	t_color			new;
	unsigned int	u;

	*line += 3;
	u = ft_atoi_base(*line, 16);
	new.red = u >> 16;
	new.green = u >> 8;
	new.blue = u;
	new.set = 1;
	while (ft_ishex(**line))
		*line += 1;
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
}
