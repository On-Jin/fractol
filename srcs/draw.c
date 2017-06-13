/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 22:46:52 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/13 05:21:13 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		mandelbrot(t_env *e, t_px *px,  int y, int x)
{
	V_PRECI	c_r = 0;
	V_PRECI	c_i = 0;
	V_PRECI	z_r = 0;
	V_PRECI	z_i = 0;
	V_PRECI x1 = -2.1;
	V_PRECI y1 = -1.2;
	V_PRECI tmp;
	int		i = 0;
	c_r = (x + e->ajj_x + e->move_x) / e->zoom + x1;
	c_i = (y + e->ajj_y + e->move_y) / e->zoom + y1;
	while (z_r * z_r + z_i * z_i < 4 && i < e->iter)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * z_i * tmp + c_i;
		i++;
	}
	if (x > 0 && x < WIDTH &&
			y > 0 && y < HEIGHT)
	{
		if (i == e->iter)
			mlxji_put_pixel(e->img, x, y, px);
		else
		{
			px->b = i * 255 / e->iter;
			mlxji_put_pixel(e->img, x, y, px);
		}
	}
}

static void		julia(t_env *e, t_px *px,  int y, int x)
{
	V_PRECI	c_r = 0;
	V_PRECI	c_i = 0;
	V_PRECI	z_r = 0;
	V_PRECI	z_i = 0;
	V_PRECI x1 = -2.1;
	V_PRECI y1 = -1.2;
	V_PRECI tmp;
	int		i = 0;

	z_r = (x + e->ajj_x + e->move_x) / e->zoom + x1;
	z_i = (y + e->ajj_y + e->move_y) / e->zoom + y1;
	c_r = e->jul_x;
	c_i = e->jul_y;
	while (z_r * z_r + z_i * z_i < 4 && i < e->iter)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * z_i * tmp + c_i;
		i++;
	}
	if (x > 0 && x < WIDTH &&
			y > 0 && y < HEIGHT)
	{
		if (i == e->iter)
			mlxji_put_pixel(e->img, x, y, px);
		else
		{
			px->b = i * 255 / e->iter;
			mlxji_put_pixel(e->img, x, y, px);
		}
	}
}

static void		buddhabrot(t_env *e, int y, int x)
{
	V_PRECI	c_r = 0;
	V_PRECI	c_i = 0;
	V_PRECI	z_r = 0;
	V_PRECI	z_i = 0;
	V_PRECI x1 = -2.1;
	V_PRECI y1 = -1.2;
	V_PRECI tmp;
	int         tab_x[10000];
	int         tab_y[10000];
	int         k;
	V_PRECI     kx, ky;
	int		i = 0;
	c_r = (x + e->ajj_x + e->move_x) / e->zoom + x1;
	c_i = (y + e->ajj_y + e->move_y) / e->zoom + y1;
	while (z_r * z_r + z_i * z_i < 4 && i < e->iter)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * z_i * tmp + c_i;
		ky = (z_i - y1) * (V_PRECI)e->zoom - (V_PRECI)e->ajj_y - e->move_y;
		kx = (z_r - x1) * (V_PRECI)e->zoom - (V_PRECI)e->ajj_x - e->move_x;
		tab_y[i] = (int)ky;
		tab_x[i] = (int)kx;
		i++;
	}
	k = 0;
	if (i != e->iter)
	{
		while (k < i)
		{
			if (tab_y[k] > 0 && tab_y[k] < HEIGHT &&
					tab_x[k] > 0 && tab_x[k] < WIDTH &&
					i > e->seuil)
			{
				if ((unsigned char)e->img->data[(tab_x[k] * 4) +
											(tab_y[k] * WIDTH * 4)] < 254)
				{
					e->img->data[(tab_x[k] * 4) + (tab_y[k] * WIDTH * 4)]++;
					e->img->data[(tab_x[k] * 4) + (tab_y[k] * WIDTH * 4) + 1]++;
					e->img->data[(tab_x[k] * 4) + (tab_y[k] * WIDTH * 4) + 2]++;
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
	if (!e->num)
		buddhabrot_color(e);
	return (1);
}
