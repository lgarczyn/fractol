/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 00:09:47 by lgarczyn          #+#    #+#             */
/*   Updated: 2016/04/09 18:24:49 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FRACTOL_H
# define _FRACTOL_H

# include "X.h"
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# include <pthread.h>
# include "gradient.h"

# define MIN(a,b)		(((a)<(b))?(a):(b))
# define MAX(a,b)		(((a)>(b))?(a):(b))
# define CLAMP(x,lo,hi)	MIN( hi, MAX(lo,x))

# define BASE_COLOR		0

# define UINT			unsigned int
# define UCHAR			unsigned char
# define FTYPE			long double
# define KEYCODE_EXIT	53
# define KEYCODE_MULT	257
# define KEYCODE_LEFT	123
# define KEYCODE_UP		126
# define KEYCODE_RIGHT	124
# define KEYCODE_DOWN	125
# define KEYCODE_A		0
# define KEYCODE_W		13
# define KEYCODE_D		2
# define KEYCODE_S		1
# define KEYCODE_R		15

# define SCREEN_WIDTH	1000
# define SCREEN_HEIGHT	1000
# define ITER_START		10
# define ZOOM_START		(0.002 / MIN(SCREEN_WIDTH, SCREEN_HEIGHT) * 2000)
# define CENTER_START	(t_itype){0, 0}
# define KEY_SPEED		50
# define SCROLL_SPEED	1.5
# define ZOOM_SPEED		1.2
# define SPEED_MULT		20
# define THREAD_NUM		8

# define TRI_HEIGHT		1.732050807568877
# define LOG3			0.47712125472
# define LOG2			0.30102999566

typedef enum
{
	mandelbrot = 1,
	garczyn = 2,
	julia = 4,
	triangles = 8,
	squares = 16,
	ship = 32,
	julia3di = 64,
	julia3dr = 128,
	weird = 256,
	sine = 512,
	threaded = 1024
}	t_fractal;

typedef struct			s_itype
{
	FTYPE				r;
	FTYPE				i;
}						t_itype;

typedef struct			s_pcoord
{
	int					x;
	int					y;
}						t_pcoord;

typedef struct			s_meta
{

	char				*prog_name;
	void				*mlx;
	void				*win;
	void				*img;
	char				*pixels;
	int					sizeline;
	int					endian;
	int					bpp;
	int					inc;
	int					img_height;
	int					img_width;

	t_itype				center;
	t_itype				julia_param;
	t_pcoord			mdown_coord;
	FTYPE				upp;
	FTYPE				halfupp;
	int					max_iter;
	int					is_julia;
	int					is_mdown;
	int					mmult;

	int					is_init;
	int					(*display)(struct s_meta *);

	UINT				colors[sizeof(COLORS)];
	t_fractal			fractals;
	int					*windows;
}						t_meta;

typedef struct			s_tdata
{
	int					pos;
	int					thn;
	t_meta				*meta;
}						t_data;

typedef struct			s_tdata3d
{
	int					pos;
	int					thn;
	t_meta				*meta;
	t_itype				param;
}						t_data3d;

int						main(int ac, char **av);
t_fractal				analyse(int ac, char **av);

void					setup_coord(t_meta *meta);
void					setup_colors(UINT *colors);
void					setup_windows(t_meta *meta);
void					setup_window(t_meta *meta, int (*f)(t_meta*), char *n);
void					close_window(t_meta **meta);

void					error_memory(t_meta *meta);
void					error_thread(t_meta *meta);
void					error_argument(char *name, char *arg);
void					error_no_argument(char *name);

int						dis_sine(t_meta *meta);
int						dis_ship(t_meta *meta);
int						dis_julia(t_meta *meta);
int						dis_weird(t_meta *meta);
int						dis_squares(t_meta *meta);
int						dis_garczyn(t_meta *meta);
int						dis_julia3di(t_meta *meta);
int						dis_julia3dr(t_meta *meta);
int						dis_triangles(t_meta *meta);
int						dis_mandelbrot(t_meta *meta);

int						set_sine_thread(t_meta *meta);
int						set_ship_thread(t_meta *meta);
int						set_weird_thread(t_meta *meta);
int						set_julia_thread(t_meta *meta);
int						set_squares_thread(t_meta *meta);
int						set_garczyn_thread(t_meta *meta);
int						set_julia3di_thread(t_meta *meta);
int						set_julia3dr_thread(t_meta *meta);
int						set_triangles_thread(t_meta *meta);
int						set_mandelbrot_thread(t_meta *meta);

UINT					get_gradient(int t);
UINT					interpolate(UINT a, UINT b);
void					put_pixel(int i, UINT color, t_meta *meta);
void					put_rectangle(t_pcoord a, t_pcoord b, t_meta *meta);

t_itype					get_real_coord(int x, int y, t_meta *m);
t_itype					get_float_coord(int x, int y, t_meta *m);
t_pcoord				get_pixel_coord(t_itype coord, t_meta *m);
void					zoom_at(t_itype coord, FTYPE ratio, t_meta *meta);
void					zoom_at_square(t_pcoord a, t_pcoord b, t_meta *meta);

int						key_down(int keycode, t_meta *meta);
int						key_up(int keycode, t_meta *meta);
int						mouse_up(int button, int x, int y, t_meta *meta);
int						mouse_down(int button, int x, int y, t_meta *meta);
int						mouse_move(int x, int y, t_meta *meta);
int						loop_hook(t_meta *meta);
int						expose_hook(t_meta *meta);

#endif
