/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 22:46:52 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/19 05:37:02 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		mandelbrot(t_env *e, t_px *px,  int y, int x)
{
	t_kit	kit;

	ft_bzero(&kit, sizeof(t_kit));
	kit.c_r = (x + e->tool.ajj_x + e->tool.move_x) / (long int)e->tool.zoom + X1_MAN;
	kit.c_i = (y + e->tool.ajj_y + e->tool.move_y) / (long int)e->tool.zoom + Y1_MAN;
	while (kit.z_r * kit.z_r + kit.z_i * kit.z_i < 4 && kit.i < e->tool.iter)
	{
		kit.tmp = kit.z_r;
		kit.z_r = kit.z_r * kit.z_r - kit.z_i * kit.z_i + kit.c_r;
		kit.z_i = 2 * kit.z_i * kit.tmp + kit.c_i;
		kit.i++;
	}
	if (x > 0 && x < WIDTH &&
			y > 0 && y < HEIGHT)
	{
		if (kit.i == e->tool.iter)
			mlxji_put_pixel(e->img, x, y, px);
		else
		{
			px->b = kit.i * 255 / e->tool.iter;
			mlxji_put_pixel(e->img, x, y, px);
		}
	}
}

static void		julia(t_env *e, t_px *px,  int y, int x)
{
	t_kit	kit;

	ft_bzero(&kit, sizeof(t_kit));
	kit.z_r = (x + e->tool.ajj_x + e->tool.move_x) / (long int)e->tool.zoom + X1_MAN;
	kit.z_i = (y + e->tool.ajj_y + e->tool.move_y) / (long int)e->tool.zoom + Y1_MAN;
	kit.c_r = e->jul_x;
	kit.c_i = e->jul_y;
	while (kit.z_r * kit.z_r + kit.z_i * kit.z_i < 4 && kit.i < e->tool.iter)
	{
		kit.tmp = kit.z_r;
		kit.z_r = kit.z_r * kit.z_r - kit.z_i * kit.z_i + kit.c_r;
		kit.z_i = 2 * kit.z_i * kit.tmp + kit.c_i;
		kit.i++;
	}
	if (x > 0 && x < WIDTH &&
			y > 0 && y < HEIGHT)
	{
		if (kit.i == e->tool.iter)
			mlxji_put_pixel(e->img, x, y, px);
		else
		{
			px->b = kit.i * 255 / e->tool.iter;
			mlxji_put_pixel(e->img, x, y, px);
		}
	}
}

static void	draw_mandel_set(t_env *e)
{
	t_px	px;
	int		y;
	int		x;

	px.r = 0;
	px.b = 0;
	px.g = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			px.b = 0;
			if (e->num == NUM_MANDEL)
				mandelbrot(e, &px, y, x);
			else if (e->num == NUM_JULIA)
				julia(e, &px, y, x);
			x++;
		}
		y++;
	}
}

int			draw(t_env *e)
{
	if (e->num == 3)
		draw_tri(e);
	else
		draw_mandel_set(e);
	return (1);
}
