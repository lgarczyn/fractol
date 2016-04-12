/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 10:15:59 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/16 10:18:19 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
		if (*s1 != *s2)
			return (*s1 - *s2);
		else
		{
			s1++;
			s2++;
		}
	return (0);
}

t_fractal		analyse_arg(char *arg, char *prog)
{
	if (ft_strcmp(arg, "mandelbrot") == 0)
		return (mandelbrot);
	else if (ft_strcmp(arg, "julia") == 0)
		return (julia);
	else if (ft_strcmp(arg, "garczyn") == 0)
		return (garczyn);
	else if (ft_strcmp(arg, "julia3di") == 0)
		return (julia3di);
	else if (ft_strcmp(arg, "julia3dr") == 0)
		return (julia3dr);
	else if (ft_strcmp(arg, "weird") == 0)
		return (weird);
	else if (ft_strcmp(arg, "sine") == 0)
		return (sine);
	else if (ft_strcmp(arg, "ship") == 0)
		return (ship);
	else if (ft_strcmp(arg, "triangles") == 0)
		return (triangles);
	else if (ft_strcmp(arg, "squares") == 0)
		return (squares);
	else if (ft_strcmp(arg, "-t") == 0)
		return (threaded);
	error_argument(prog, arg);
	return (0);
}

t_fractal		analyse(int ac, char **av)
{
	int			i;
	t_fractal	r;

	r = 0;
	i = 0;
	while (++i < ac)
		if (ft_strcmp(av[i], "all") == 0)
			r |= 0xFFFFFFFF ^ threaded;
		else
			r |= analyse_arg(av[i], av[0]);
	if (r == (r & threaded))
		error_no_argument(av[0]);
	return (r);
}
