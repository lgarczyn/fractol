/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 00:44:17 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/04/09 18:35:07 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				mouse_down(int button, int x, int y, t_meta *meta)
{
	t_pcoord	p;

	if (!meta)
		return (0);
	if (y < 0)
		return (0);
	if (button == 1)
	{
		p.x = CLAMP(x, 0, meta->img_width - 1);
		p.y = CLAMP(y, 0, meta->img_height - 1);
		meta->mdown_coord = p;
		meta->is_mdown = 1;
	}
	return (0);
}

int				mouse_up(int button, int x, int y, t_meta *meta)
{
	t_pcoord	p;

	if (!meta)
		return (0);
	if (button == 1)
	{
		p.x = CLAMP(x, 0, meta->img_width - 1);
		p.y = CLAMP(y, 0, meta->img_height - 1);
		if (meta->is_mdown)
			zoom_at_square(p, meta->mdown_coord, meta);
		meta->is_mdown = 0;
	}
	else if (button == 3)
		meta->center = get_real_coord(x, y, meta);
	else if (button == 4)
		zoom_at(get_real_coord(x, y, meta), 1 / 1.02, meta);
	else if (button == 5)
		zoom_at(get_real_coord(x, y, meta), 1.02, meta);
	else
		return (0);
	mlx_loop_hook(meta->mlx, loop_hook, meta);
	return (0);
}

int				mouse_move(int x, int y, t_meta *meta)
{
	t_pcoord	p;

	if (!meta)
		return (0);
	if (meta->is_julia)
	{
		meta->julia_param = get_float_coord(x, y, meta);
		meta->julia_param.r *= fabsl(meta->julia_param.r) * 2;
		meta->julia_param.i *= fabsl(meta->julia_param.i);
		mlx_loop_hook(meta->mlx, loop_hook, meta);
	}
	if (meta->is_mdown)
	{
		p.x = CLAMP(x, 0, meta->img_width - 1);
		p.y = CLAMP(y, 0, meta->img_height - 1);
		mlx_put_image_to_window(meta->mlx, meta->win, meta->img, 0, 0);
		put_rectangle(p, meta->mdown_coord, meta);
	}
	return (0);
}

#include <stdio.h>

int				apply_key(int keycode, t_meta *meta)
{
	if (keycode == KEYCODE_LEFT)
		meta->center.r -= meta->upp * KEY_SPEED;
	else if (keycode == KEYCODE_UP)
		meta->center.i -= meta->upp * KEY_SPEED;
	else if (keycode == KEYCODE_RIGHT)
		meta->center.r += meta->upp * KEY_SPEED;
	else if (keycode == KEYCODE_DOWN)
		meta->center.i += meta->upp * KEY_SPEED;
	else if (keycode == KEYCODE_A)
		meta->max_iter = MAX(1, meta->max_iter - meta->mmult);
	else if (keycode == KEYCODE_W)
		meta->upp /= ZOOM_SPEED;
	else if (keycode == KEYCODE_D)
		meta->max_iter += meta->mmult;
	else if (keycode == KEYCODE_S)
		meta->upp *= ZOOM_SPEED;
	else if (keycode == KEYCODE_R)
		setup_coord(meta);
	else if (keycode == KEYCODE_MULT)
		meta->mmult = SPEED_MULT;
	else
		return (0);
	mlx_loop_hook(meta->mlx, loop_hook, meta);
	return (0);
}

int				key_down(int keycode, t_meta *meta)
{
	if (!meta)
		return (0);
	if (keycode == KEYCODE_EXIT)
		close_window(&meta);
	else
		apply_key(keycode, meta);
	return (0);
}

int				key_up(int keycode, t_meta *meta)
{
	if (!meta)
		return (0);
	if (keycode == KEYCODE_MULT)
		meta->mmult = 1; 
	return (0);
}
