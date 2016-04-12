/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia3di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 06:23:36 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/16 06:23:37 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

UINT				get_julia3di_color(t_itype coord, int j, t_data3d t)
{
	t_itype			z;
	t_itype			d;
	int				i;

	i = 0;
	z = coord;
	d.r = z.r * z.r;
	d.i = z.i * z.i;
	while (d.r + d.i < 4 && i < t.meta->max_iter)
	{
		z.i = 2 * z.i * z.r + t.param.i;
		z.r = d.r - d.i + t.param.r;
		d.r = z.r * z.r;
		d.i = z.i * z.i;
		i++;
	}
	if (i >= t.meta->max_iter)
		return (t.meta->colors[(j - 10) & 31 ? j : (j + 30) % 255]);
	coord.r = coord.r - 0.02;
	coord.i = coord.i + 0.02;
	t.param.r -= 0.01;
	if (j < 256 - 2)
		return (get_julia3di_color(coord, j + 2, t));
	return (BASE_COLOR);
}

void				*dis_julia3di_thread(void *data)
{
	t_data3d		d;
	int				i;
	int				lin;
	int				max;
	t_itype			coord;

	d = *(t_data3d*)data;
	i = d.meta->img_height * d.pos / d.thn * d.meta->sizeline;
	lin = i;
	max = d.meta->img_height * (d.pos + 1) / d.thn * d.meta->sizeline;
	while (i < max)
	{
		coord = get_real_coord(0, i / d.meta->sizeline, d.meta);
		coord.i = coord.i;
		coord.r = coord.r;
		lin += d.meta->sizeline;
		while (i < lin)
		{
			put_pixel(i, get_julia3di_color(coord, 0, d), d.meta);
			coord.r += d.meta->upp;
			i += d.meta->inc;
		}
	}
	return (NULL);
}

int					dis_julia3di(t_meta *meta)
{
	t_data3d		data;

	meta->is_julia = 1;
	data.pos = 0;
	data.thn = 1;
	data.meta = meta;
	data.param = (t_itype){0.6, meta->julia_param.r};
	dis_julia3di_thread(&data);
	mlx_put_image_to_window(meta->mlx, meta->win, meta->img, 0, 0);
	return (0);
}

int					set_julia3di_thread(t_meta *meta)
{
	pthread_t		t[THREAD_NUM];
	t_data3d		d[THREAD_NUM];
	t_itype			param;
	int				i;
	int				rc;

	meta->is_julia = 1;
	i = -1;
	while (++i < THREAD_NUM)
	{
		param = (t_itype){0.6, meta->julia_param.r};
		d[i] = (t_data3d){i, THREAD_NUM, meta, param};
		rc = pthread_create(&t[i], NULL, dis_julia3di_thread, &d[i]);
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
