/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 22:46:52 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/16 06:45:22 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		mandelbrot(t_env *e, t_px *px,  int y, int x)
{
	t_kit	kit;

	ft_bzero(&kit, sizeof(t_kit));
	kit.c_r = (x + e->tool.ajj_x + e->tool.move_x) / e->tool.zoom + X1_MAN;
	kit.c_i = (y + e->tool.ajj_y + e->tool.move_y) / e->tool.zoom + Y1_MAN;
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
	kit.z_r = (x + e->tool.ajj_x + e->tool.move_x) / e->tool.zoom + X1_MAN;
	kit.z_i = (y + e->tool.ajj_y + e->tool.move_y) / e->tool.zoom + Y1_MAN;
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

static void		buddhabrot(t_env *e, int y, int x)
{
	t_kit	kit;
	int         k;
	int     kx, ky;

	ft_bzero(&kit, sizeof(t_kit));
	kit.c_r = (x + e->tool.ajj_x + e->tool.move_x) / e->tool.zoom + X1_MAN;
	kit.c_i = (y + e->tool.ajj_y + e->tool.move_y) / e->tool.zoom + Y1_MAN;
	while (kit.z_r * kit.z_r + kit.z_i * kit.z_i < 4 && kit.i < e->tool.iter)
	{
		kit.tmp = kit.z_r;
		kit.z_r = kit.z_r * kit.z_r - kit.z_i * kit.z_i + kit.c_r;
		kit.z_i = (kit.z_i + kit.z_i) * kit.tmp + kit.c_i;
		kit.i++;
	}
	k = 0;
	if (kit.i != e->tool.iter)
	{
		kit.c_r = (x + e->tool.ajj_x + e->tool.move_x) / e->tool.zoom + X1_MAN;
		kit.c_i = (y + e->tool.ajj_y + e->tool.move_y) / e->tool.zoom + Y1_MAN;
		kit.z_i = 0;
		kit.z_r = 0;
		while (k < kit.i)
		{
			kit.tmp = kit.z_r;
			kit.z_r = kit.z_r * kit.z_r - kit.z_i * kit.z_i + kit.c_r;
			kit.z_i = (kit.z_i + kit.z_i) * kit.tmp + kit.c_i;
			ky = (int)((kit.z_i - Y1_MAN) *
					(V_PRECI)e->tool.zoom - (V_PRECI)e->tool.ajj_y - e->tool.move_y);
			kx = (int)((kit.z_r - X1_MAN) *
					(V_PRECI)e->tool.zoom - (V_PRECI)e->tool.ajj_x - e->tool.move_x);
			k++;
			if (ky > 0 && ky < HEIGHT &&
					kx > 0 && kx < WIDTH &&
					k > e->bud.min[0])
			{
				if ((unsigned char)e->img->data[(kx * 4) +
											(ky * WIDTH * 4)] < 254)
				{
					e->img->data[(kx * 4) + (ky * WIDTH * 4)]++;
					e->img->data[(kx * 4) + (ky * WIDTH * 4) + 1]++;
					e->img->data[(kx * 4) + (ky * WIDTH * 4) + 2]++;
				}
			}
			k++;
		}
	}
}

int			draw(t_env *e)
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
			else
				buddhabrot(e, y, x);
			x++;
		}
		y++;
	}
//	if (!e->num)
//		buddhabrot_color(e, e->img->data);
	return (1);
}
