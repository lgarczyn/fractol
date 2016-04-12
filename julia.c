/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 06:23:36 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/16 06:23:37 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

UINT				get_julia_color(t_itype coord, t_meta *meta)
{
	t_itype			z;
	t_itype			d;
	int				i;

	i = 0;
	z = coord;
	d.r = z.r * z.r;
	d.i = z.i * z.i;
	coord = meta->julia_param;
	while (d.r + d.i < 4 && i < meta->max_iter)
	{
		z.i = 2 * z.i * z.r + coord.i;
		z.r = d.r - d.i + coord.r;
		d.r = z.r * z.r;
		d.i = z.i * z.i;
		i++;
	}
	if (i >= meta->max_iter)
		return (BASE_COLOR);
	return (meta->colors[i % COLORS_SIZE]);
}

void				*dis_julia_thread(void *data)
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
			put_pixel(i, get_julia_color(coord, d.meta), d.meta);
			coord.r += d.meta->upp;
			i += d.meta->inc;
		}
	}
	return (NULL);
}

int					dis_julia(t_meta *meta)
{
	t_data			d;

	d.pos = 0;
	d.thn = 1;
	d.meta = meta;
	meta->is_julia = 1;
	dis_julia_thread(&d);
	mlx_put_image_to_window(meta->mlx, meta->win, meta->img, 0, 0);
	return (0);
}

int					set_julia_thread(t_meta *meta)
{
	pthread_t		t[THREAD_NUM];
	t_data			d[THREAD_NUM];
	int				i;
	int				rc;

	i = -1;
	meta->is_julia = 1;
	while (++i < THREAD_NUM)
	{
		d[i] = (t_data){i, THREAD_NUM, meta};
		rc = pthread_create(&t[i], NULL, dis_julia_thread, &d[i]);
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
