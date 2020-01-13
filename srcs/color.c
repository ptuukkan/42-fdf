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

void	set_color(t_fdf *fdf)
{
	fdf->img.start.red = 0x57;
	fdf->img.start.green = 0x34;
	fdf->img.start.blue = 0x0;
	fdf->img.end.red = 0xFF;
	fdf->img.end.green = 0xE0;
	fdf->img.end.blue = 0xC9;
}
