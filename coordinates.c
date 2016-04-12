/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 00:42:15 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/16 00:42:17 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_pcoord		get_pixel_coord(t_itype coord, t_meta *m)
{
	t_pcoord	pixel;

	pixel.x = round((coord.r - m->center.r) / m->upp) + m->img_width / 2;
	pixel.y = round((coord.i - m->center.i) / m->upp) + m->img_height / 2;
	return (pixel);
}

t_itype			get_real_coord(int x, int y, t_meta *m)
{
	t_itype		coord;

	coord.r = ((FTYPE)x - m->img_width / 2 + 0.5) * m->upp + m->center.r;
	coord.i = ((FTYPE)y - m->img_height / 2 + 0.5) * m->upp + m->center.i;
	return (coord);
}

t_itype			get_float_coord(int x, int y, t_meta *m)
{
	t_itype		coord;

	coord.r = ((FTYPE)(x - m->img_width / 2) + 0.5) / m->img_width * 2,
	coord.i = ((FTYPE)(y - m->img_height / 2) + 0.5) / m->img_height * 2;
	return (coord);
}

void			zoom_at(t_itype coord, FTYPE ratio, t_meta *m)
{
	m->upp *= ratio;
	m->center.r -= (coord.r - m->center.r) * (ratio - 1);
	m->center.i -= (coord.i - m->center.i) * (ratio - 1);
}

void			zoom_at_square(t_pcoord a, t_pcoord b, t_meta *meta)
{
	t_itype		az;
	t_itype		bz;
	FTYPE		ratio;

	az = get_real_coord(a.x, a.y, meta);
	bz = get_real_coord(b.x, b.y, meta);
	meta->center.r = (az.r + bz.r) / 2;
	meta->center.i = (az.i + bz.i) / 2;
	if (a.x != b.x && a.y != b.y)
	{
		ratio = fabsl(az.r - bz.r) / fabsl(az.i - bz.i);
		if (ratio > (FTYPE)meta->img_width / (FTYPE)meta->img_height)
			meta->upp = fabsl(az.r - bz.r) / meta->img_width;
		else
			meta->upp = fabsl(az.i - bz.i) / meta->img_height;
	}
	else if (a.x != b.x)
		meta->upp = fabsl(az.r - bz.r) / meta->img_width;
	else if (a.y != b.y)
		meta->upp = fabsl(az.i - bz.i) / meta->img_height;
}
