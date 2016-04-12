/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 21:47:00 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/20 21:47:02 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			put_pixel(int i, UINT color, t_meta *meta)
{
	meta->pixels[i] = mlx_get_color_value(meta->mlx, color);
	meta->pixels[i + 1] = mlx_get_color_value(meta->mlx, color >> 8);
	meta->pixels[i + 2] = mlx_get_color_value(meta->mlx, color >> 16);
}

void			put_rectangle(t_pcoord a, t_pcoord b, t_meta *meta)
{
	t_pcoord	c;
	t_pcoord	d;
	t_meta		m;
	int			i;

	m = *meta;
	c.x = MIN(a.x, b.x);
	c.y = MIN(a.y, b.y);
	d.x = MAX(a.x, b.x);
	d.y = MAX(a.y, b.y);
	i = c.x;
	d.x--;
	while (++i < d.x)
	{
		mlx_pixel_put(m.mlx, m.win, i, c.y, -(i & 1));
		mlx_pixel_put(m.mlx, m.win, i, d.y, -(i & 1));
	}
	i = c.y - 1;
	d.x++;
	while (++i < d.y)
	{
		mlx_pixel_put(m.mlx, m.win, c.x, i, -(i & 1));
		mlx_pixel_put(m.mlx, m.win, d.x, i, -(i & 1));
	}
}
