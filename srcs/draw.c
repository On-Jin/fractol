/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 22:46:52 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/09 02:58:07 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		mandelbrot(t_env *e, t_px *px,  int y, int x)
{
	//t_res	res;
	float	c_r = 0;
	float	c_i = 0;
	float	z_r = 0;
	float	z_i = 0;
	float x1 = -2.1;
	float x2 = 0.6;
	float y1 = -1.2;
	float y2 = 1.2;
	float tmp;
	int		i = 0;
(void)x2;(void)y2;
	//ft_bzero(&res, sizeof(t_res));
	c_r = (x + e->ajj_x) / e->zoom + x1;
	c_i = (y + e->ajj_y) / e->zoom + y1;

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
			px->b = i * 255 / e->iter;
				mlxji_put_pixel(e->img, x, y, px);
	}
//	return (res);
}

int			draw(t_env *e)
{
	t_px	px;
//	t_res	res;
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
			mandelbrot(e, &px, y, x);
			x++;
		}
		y++;
	}
	return (1);
}
