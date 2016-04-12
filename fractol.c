/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fravtol2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 21:43:15 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/20 21:43:17 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				main(int ac, char **av)
{
	t_meta		meta;
	int			owin;

	owin = 0;
	meta.fractals = analyse(ac, av);
	meta.prog_name = av[0];
	meta.windows = &owin;
	setup_coord(&meta);
	setup_colors(meta.colors);
	meta.mlx = mlx_init();
	if (!meta.mlx)
		error_memory(&meta);
	setup_windows(&meta);
	mlx_loop(meta.mlx);
	return (1);
}

void			setup_coord(t_meta *meta)
{
	meta->img_height = SCREEN_HEIGHT;
	meta->img_width = SCREEN_WIDTH;
	meta->max_iter = ITER_START;
	meta->center = CENTER_START;
	meta->upp = ZOOM_START;
	meta->mmult = 1;
}

void			setup_colors(UINT *colors)
{
	int			i;

	i = -1;
	while (++i < COLORS_SIZE)
		colors[i] = COLORS[i];
}

void			setup_windows(t_meta *m)
{
	t_fractal	t;

	t = m->fractals & threaded;
	if (m->fractals & sine)
		setup_window(m, t ? set_sine_thread : dis_sine, "Sine");
	if (m->fractals & ship)
		setup_window(m, t ? set_ship_thread : dis_ship, "Burning Ship");
	if (m->fractals & weird)
		setup_window(m, t ? set_weird_thread : dis_weird, "Zn2 + Zn + c");
	if (m->fractals & julia)
		setup_window(m, t ? set_julia_thread : dis_julia, "Julia");
	if (m->fractals & squares)
		setup_window(m, t ? set_squares_thread : dis_squares, "Squares");
	if (m->fractals & garczyn)
		setup_window(m, t ? set_garczyn_thread : dis_garczyn, "Garczyn");
	if (m->fractals & julia3di)
		setup_window(m, t ? set_julia3di_thread : dis_julia3di, "Julia 3D xyr");
	if (m->fractals & julia3dr)
		setup_window(m, t ? set_julia3dr_thread : dis_julia3dr, "Julia 3D xyi");
	if (m->fractals & triangles)
		setup_window(m, t ? set_triangles_thread : dis_triangles, "Triangles");
	if (m->fractals & mandelbrot)
		setup_window(m, t ? set_mandelbrot_thread : dis_mandelbrot, "Mandel");
}

void			setup_window(t_meta *meta, int (*f)(t_meta*), char *name)
{
	t_meta		*m;

	m = (t_meta*)malloc(sizeof(t_meta));
	if (!m)
		error_memory(meta);
	*m = *meta;
	m->win = mlx_new_window(m->mlx, m->img_width, m->img_height, name);
	if (!m->win)
		error_memory(meta);
	m->img = mlx_new_image(m->mlx, m->img_width, m->img_height);
	if (!m->img)
		error_memory(meta);
	m->pixels = mlx_get_data_addr(m->img, &m->bpp, &m->sizeline, &m->endian);
	m->inc = m->bpp / 8;
	(*(m->windows))++;
	m->display = f;
	meta->is_init = 0;
	meta->is_julia = 0;
	mlx_expose_hook(m->win, expose_hook, m);
	mlx_hook(m->win, KeyPress, KeyPressMask, key_down, m);
	mlx_hook(m->win, KeyRelease, KeyReleaseMask, key_up, m);
	mlx_hook(m->win, ButtonRelease, ButtonReleaseMask, mouse_up, m);
	mlx_hook(m->win, ButtonPress, ButtonPressMask, mouse_down, m);
	mlx_hook(m->win, MotionNotify, PointerMotionMask, mouse_move, m);
}
