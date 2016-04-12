/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 23:27:40 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/20 23:28:13 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				expose_hook(t_meta *m)
{
	if (!m)
		return (0);
	if (m->is_init)
		mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	else
	{
		m->display(m);
		m->is_init = 1;
	}
	return (0);
}

int				loop_hook(t_meta *m)
{
	if (!m)
		return (0);
	m->display(m);
	mlx_loop_hook(m->mlx, NULL, NULL);
	return (0);
}
