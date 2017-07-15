/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 22:46:52 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/15 23:53:35 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		mandelbrot(t_env *e, int y, int x)
{
	t_kit	kit;

	ft_bzero(&kit, sizeof(t_kit));
	kit.c_r = (x / (V_PRECI)(e->height * 1.125)) *
		((V_PRECI)e->tool.xmax - (V_PRECI)e->tool.xmin) + e->tool.xmin;
	kit.c_i = (y / (V_PRECI)e->height) *
		((V_PRECI)e->tool.ymax - (V_PRECI)e->tool.ymin) + e->tool.ymin;
	while (kit.z_r * kit.z_r + kit.z_i * kit.z_i < 4 && kit.i < e->tool.iter)
	{
		kit.tmp = kit.z_r;
		kit.z_r = kit.z_r * kit.z_r - kit.z_i * kit.z_i + kit.c_r;
		kit.z_i = 2 * kit.z_i * kit.tmp + kit.c_i;
		kit.i++;
	}
	return (kit.i);
}

static int		julia(t_env *e, int y, int x)
{
	t_kit	kit;

	ft_bzero(&kit, sizeof(t_kit));
	kit.c_r = (x / (V_PRECI)(e->height * 1.125)) *
		((V_PRECI)e->tool.xmax - (V_PRECI)e->tool.xmin) + e->tool.xmin;
	kit.c_i = (y / (V_PRECI)e->height) *
		((V_PRECI)e->tool.ymax - (V_PRECI)e->tool.ymin) + e->tool.ymin;
	kit.z_r = e->jul_x;
	kit.z_i = e->jul_y;
	while (kit.c_r * kit.c_r + kit.c_i * kit.c_i < 4 && kit.i < e->tool.iter)
	{
		kit.tmp = kit.c_r;
		kit.c_r = kit.c_r * kit.c_r - kit.c_i * kit.c_i + kit.z_r;
		kit.c_i = 2 * kit.c_i * kit.tmp + kit.z_i;
		kit.i++;
	}
	return (kit.i);
}

static void		draw_mandel_set(t_env *e)
{
	t_px	px;
	int		y;
	int		x;
	int		ret;

	px.r = 0;
	px.b = 0;
	px.g = 0;
	y = 0;
	while (y < e->height)
	{
		x = 0;
		while (x++ < e->width)
		{
			px.b = 0;
			if (e->num == NUM_MANDEL)
				ret = mandelbrot(e, y, x);
			else if (e->num == NUM_JULIA)
				ret = julia(e, y, x);
			if (ret != e->tool.iter)
				px.b = ret * 255 / e->tool.iter;
			mlxji_put_pixel(e->img, x, y, &px);
		}
		y++;
	}
}

int				draw(t_env *e)
{
	if (e->num == 3)
		draw_tri(e);
	else if (e->num == 4)
		draw_tree(e);
	else
		draw_mandel_set(e);
	return (1);
}
