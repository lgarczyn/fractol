/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 00:43:23 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/16 00:43:25 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

UINT				get_triangles_color(t_itype z, t_meta *meta, int max)
{
	t_itype			m;
	int				i;

	if (z.r < 2 || z.r > 4 || z.i > 0)
		return (BASE_COLOR);
	if (z.i < 2 - z.r || z.i < z.r - 4)
		return (BASE_COLOR);
	i = 0;
	while (i <= max)
	{
		z.r += floor(fmod(z.i, 2.0));
		m.r = fmod(z.r, 2.0);
		m.i = 1 - fmod(z.i, 1.0);
		if (m.i > m.r && m.i > 2 - m.r)
			return (meta->colors[i % COLORS_SIZE]);
		z.r *= 2;
		z.i *= 2;
		i += 16;
	}
	return (BASE_COLOR);
}

void				*dis_triangles_thread(void *data)
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
		coord.r = coord.r + 3;
		coord.i = (coord.i - 1) / TRI_HEIGHT;
		lin += d.meta->sizeline;
		while (i < lin)
		{
			put_pixel(i, get_triangles_color(coord, d.meta,
			log(1 / d.meta->upp) * 6.8 / LOG2), d.meta);
			coord.r += d.meta->upp;
			i += d.meta->inc;
		}
	}
	return (NULL);
}

int					dis_triangles(t_meta *meta)
{
	t_data			d;

	d.pos = 0;
	d.thn = 1;
	d.meta = meta;
	dis_triangles_thread(&d);
	mlx_put_image_to_window(meta->mlx, meta->win, meta->img, 0, 0);
	return (0);
}

int					set_triangles_thread(t_meta *meta)
{
	pthread_t		t[THREAD_NUM];
	t_data			d[THREAD_NUM];
	int				i;
	int				rc;

	i = -1;
	while (++i < THREAD_NUM)
	{
		d[i] = (t_data){i, THREAD_NUM, meta};
		rc = pthread_create(&t[i], NULL, dis_triangles_thread, &d[i]);
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
