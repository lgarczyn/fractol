/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 21:45:22 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/20 21:45:26 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			close_window(t_meta **m)
{
	t_meta		*meta;

	meta = *m;
	(*(meta->windows))--;
	if (*(meta->windows) == 0)
		exit(0);
	mlx_loop_hook(meta->mlx, NULL, NULL);
	mlx_expose_hook(meta->win, NULL, NULL);
	mlx_hook(meta->win, KeyPress, KeyPressMask, NULL, NULL);
	mlx_hook(meta->win, ButtonRelease, ButtonReleaseMask, NULL, NULL);
	mlx_hook(meta->win, ButtonPress, ButtonPressMask, NULL, NULL);
	mlx_hook(meta->win, MotionNotify, PointerMotionMask, NULL, NULL);
	mlx_destroy_window(meta->mlx, meta->win);
	mlx_destroy_image(meta->mlx, meta->img);
	free(meta);
	*m = NULL;
}
