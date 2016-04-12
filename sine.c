/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sine.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 00:43:23 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/16 00:43:25 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

UINT				get_sine_color(t_itype coord, t_meta *meta)
{
	t_itype			z;
	FTYPE			tmp;
	int				i;

	i = 0;
	z = coord;
	while (z.r * z.r + z.i * z.i < 100 && i < meta->max_iter)
	{
		tmp = sin(z.r) * cosh(z.i) + coord.r;
		z.i = cos(z.r) * sinh(z.i) + coord.i;
		z.r = tmp;
		i++;
	}
	if (i >= meta->max_iter)
		return (BASE_COLOR);
	return (meta->colors[i % COLORS_SIZE]);
}

void				*dis_sine_thread(void *data)
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
			put_pixel(i, get_sine_color(coord, d.meta), d.meta);
			coord.r += d.meta->upp;
			i += d.meta->inc;
		}
	}
	return (NULL);
}

int					dis_sine(t_meta *meta)
{
	t_data			d;

	d.pos = 0;
	d.thn = 1;
	d.meta = meta;
	dis_sine_thread(&d);
	mlx_put_image_to_window(meta->mlx, meta->win, meta->img, 0, 0);
	return (0);
}

int					set_sine_thread(t_meta *meta)
{
	pthread_t		t[THREAD_NUM];
	t_data			d[THREAD_NUM];
	int				i;
	int				rc;

	i = -1;
	while (++i < THREAD_NUM)
	{
		d[i] = (t_data){i, THREAD_NUM, meta};
		rc = pthread_create(&t[i], NULL, dis_sine_thread, &d[i]);
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
