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

static int	get_outcode(t_vec4 v)
{
	int	code;

	code = OC_IN;
	if (v.x > 1.0)
		code |= OC_RIGHT;
	else if (v.x < -1.0)
		code |= OC_LEFT;
	if (v.y > 1.0)
		code |= OC_TOP;
	else if (v.y < -1.0)
		code |= OC_BOTTOM;
	return (code);
}

static void	cut(t_fdf *fdf, int oc, t_vec4 *v1, t_vec4 *v2)
{
	if (oc & OC_TOP)
	{
		v1->x = v1->x + (v2->x - v1->x) * (0 - v1->y) / (v2->y - v1->y);
		v1->y = 1;
	}
	if (oc & OC_BOTTOM)
	{
		v1->x = v1->x + (v2->x - v1->x) * (fdf->viewport.height - v1->y) /
				(v2->y - v1->y);
		v1->y = -1;
	}
	if (oc & OC_RIGHT)
	{
		v1->y = v1->y + (v2->y - v1->y) * (fdf->viewport.width - v1->x) /
				(v2->x - v1->x);
		v1->x = 1;
	}
	if (oc & OC_LEFT)
	{
		v1->y = v1->y + (v2->y - v1->y) * (0 - v1->x) / (v2->x - v1->x);
		v1->x = -1;
	}
}

int			clip(t_fdf *fdf, t_vec4 a, t_vec4 b)
{
	int	oc_a;
	int	oc_b;
	int	out;
	return (1);
	while (1)
	{
		oc_a = get_outcode(a);
		oc_b = get_outcode(b);
		if (!(oc_a | oc_b))
			return (1);
		if (oc_a & oc_b)
			return (0);
		if (oc_a)
		{
			cut(fdf, oc_a, &a, &b);
			oc_a = get_outcode(a);
		}
		else
		{
			cut(fdf, oc_b, &b, &a);
			oc_b = get_outcode(b);
		}
	}
}
