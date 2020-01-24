/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:08:41 by ptuukkan          #+#    #+#             */
/*   Updated: 2020/01/20 11:08:42 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	calc_outcode(double (*bc)[6])
{
	int	outcode;

	outcode = OC_IN;
	if ((*bc)[0] < 0.0)
		outcode |= OC_LEFT;
	else if ((*bc)[1] < 0.0)
		outcode |= OC_RIGHT;
	if ((*bc)[2] < 0.0)
		outcode |= OC_BOTTOM;
	else if ((*bc)[3] < 0.0)
		outcode |= OC_TOP;
	if ((*bc)[4] < 0.0)
		outcode |= OC_NEAR;
	else if ((*bc)[5] < 0.0)
		outcode |= OC_FAR;
	return (outcode);
}

static void	calc_boundary(double (*bc)[2][6], t_vec4 *a, t_vec4 *b)
{
	(*bc)[0][0] = a->w + a->x;
	(*bc)[0][1] = a->w - a->x;
	(*bc)[0][2] = a->w + a->y;
	(*bc)[0][3] = a->w - a->y;
	(*bc)[0][4] = a->w + a->z;
	(*bc)[0][5] = a->w - a->z;
	(*bc)[1][0] = b->w + b->x;
	(*bc)[1][1] = b->w - b->x;
	(*bc)[1][2] = b->w + b->y;
	(*bc)[1][3] = b->w - b->y;
	(*bc)[1][4] = b->w + b->z;
	(*bc)[1][5] = b->w - b->z;
}

static void	chop(t_vec4 *a, t_vec4 *b, double t_in, double t_out)
{
	t_vec4	tmp;

	if (t_in > 0.0)
	{
		tmp.x = a->x + t_in * (b->x - a->x);
		tmp.y = a->y + t_in * (b->y - a->y);
		tmp.z = a->z + t_in * (b->z - a->z);
		tmp.w = a->w + t_in * (b->w - a->w);
	}
	if (t_out < 1.0)
	{
		b->x = a->x + t_out * (b->x - a->x);
		b->y = a->y + t_out * (b->y - a->y);
		b->z = a->z + t_out * (b->z - a->z);
		b->w = a->w + t_out * (b->w - a->w);
	}
	if (t_in > 0.0)
	{
		a->x = tmp.x;
		a->y = tmp.y;
		a->z = tmp.z;
		a->w = tmp.w;
	}
}

static int	calc_chop(t_vec4 *a, t_vec4 *b, int (*oc)[2], double (*bc)[2][6])
{
	int				i;
	double			t_out;
	double			t_in;
	static t_vec4	tmp;

	t_out = 1.0;
	t_in = 0.0;
	i = 0;
	while (i < 6)
	{
		if ((*bc)[0][i] < 0.0)
			t_in = ft_dmax(t_in, (*bc)[0][i] / ((*bc)[0][i] - (*bc)[1][i]));
		if ((*bc)[1][i] < 0.0)
			t_out = ft_dmin(t_out, (*bc)[0][i] / ((*bc)[0][i] - (*bc)[1][i]));
		if (t_in > t_out)
			return (0);
		i++;
	}
	chop(a, b, t_in, t_out);
	return (1);
}

int			clip(t_fdf *fdf, t_vec4 *a, t_vec4 *b)
{
	int		oc[2];
	double	bc[2][6];

	calc_boundary(&bc, a, b);
	oc[0] = calc_outcode(&bc[0]);
	oc[1] = calc_outcode(&bc[1]);
	if (!(oc[0] | oc[1]))
		return (1);
	if (oc[0] & oc[1])
		return (0);
	return (calc_chop(a, b, &oc, &bc));
}
