/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 00:43:23 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/16 00:43:25 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

UINT				get_ship_color(t_itype coord, t_meta *meta)
{
	t_itype			z;
	t_itype			d;
	int				i;

	i = 0;
	z.r = 0;
	z.i = 0;
	d.r = z.r * z.r;
	d.i = z.i * z.i;
	while (d.r + d.i < 4 && i < meta->max_iter)
	{
		z.i = 2 * fabsl(z.i) * fabsl(z.r) + coord.i;
		z.r = d.r - d.i + coord.r;
		d.r = z.r * z.r;
		d.i = z.i * z.i;
		i++;
	}
	if (i >= meta->max_iter)
		return (BASE_COLOR);
	return (meta->colors[i % COLORS_SIZE]);
}

UINT				get_real_color(t_itype a, t_meta *meta)
{
	t_itype			b;
	t_itype			c;
	t_itype			d;

	c.r = a.r + meta->halfupp;
	c.i = a.i + meta->halfupp;
	b.r = a.r;
	b.i = c.i;
	d.r = c.r;
	d.i = a.i;
	return (interpolate(
	interpolate(get_ship_color(a, meta), get_ship_color(b, meta)),
	interpolate(get_ship_color(c, meta), get_ship_color(d, meta))));
}

void				*dis_ship_thread(void *data)
{
	t_data			d;
	int				i;
	int				lin;
	int				max;
	t_itype			coord;

	d = *(t_data*)data;
	i = d.meta->img_height * d.pos / d.thn * d.meta->sizeline;
	lin = i;
	max = d.meta->img_height * (d.pos + 1) / d.thn * d.meta->sizeline;
	while (i < max)
	{
		coord = get_real_coord(0, i / d.meta->sizeline, d.meta);
		lin += d.meta->sizeline;
		while (i < lin)
		{
			put_pixel(i, get_real_color(coord, d.meta), d.meta);
			coord.r += d.meta->upp;
			i += d.meta->inc;
		}
	}
	return (NULL);
}

int					dis_ship(t_meta *meta)
{
	t_data			d;

	d.pos = 0;
	d.thn = 1;
	d.meta = meta;
	d.meta->halfupp = d.meta->upp / 2;
	dis_ship_thread(&d);
	mlx_put_image_to_window(meta->mlx, meta->win, meta->img, 0, 0);
	return (0);
}

int					set_ship_thread(t_meta *meta)
{
	pthread_t		t[THREAD_NUM];
	t_data			d[THREAD_NUM];
	int				i;
	int				rc;

	i = -1;
	meta->halfupp = meta->upp / 2;
	while (++i < THREAD_NUM)
	{
		d[i] = (t_data){i, THREAD_NUM, meta};
		rc = pthread_create(&t[i], NULL, dis_ship_thread, &d[i]);
		if (rc)
			error_thread(meta);
	}
	i = -1;
	while (++i < THREAD_NUM)
	{
		pthread_join(t[i], NULL);
	}
	mlx_put_image_to_window(meta->mlx, meta->win, meta->img, 0, 0);
	return (0);
}
