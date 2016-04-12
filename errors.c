/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 00:52:30 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/01/16 00:52:31 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_putstr(char *str)
{
	int			len;

	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
}

void			error_memory(t_meta *meta)
{
	ft_putstr(meta->prog_name);
	ft_putstr(": Not enough memory\n");
	exit(1);
}

void			error_thread(t_meta *meta)
{
	ft_putstr(meta->prog_name);
	ft_putstr(": Failed to open new thread\n");
	exit(1);
}

void			error_no_argument(char *name)
{
	ft_putstr(name);
	ft_putstr(": No fractal name entered\n");
	ft_putstr("Possible arguments: -t mandelbrot julia garczyn julia3di ");
	ft_putstr("julia3dr weird sine ship triangles squares all\n");
	exit(1);
}

void			error_argument(char *name, char *arg)
{
	ft_putstr(name);
	ft_putstr(": Invalid argument: ");
	ft_putstr(arg);
	ft_putstr("\nPossible arguments: -t mandelbrot julia garczyn julia3di ");
	ft_putstr("julia3dr weird sine ship triangles squares all\n");
	exit(1);
}
