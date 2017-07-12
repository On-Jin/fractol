/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 06:48:09 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/12 19:56:06 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	conversion_radians(double degre)
{
	return (degre / 180 * 3.1415);
}

static double	loop_angle(double nb)
{
	if (nb > 360)
		nb -= 360;
	return (nb);
}

static t_pxtopx	rotation_tree(t_pxtopx to, double angle)
{
	double	ret;
	int		nx;
	int		ny;

	ret = conversion_radians(angle);
	nx = to.x2 - to.x1;
	ny = to.y2 - to.y1;
	to.x2 = to.x1 + (nx) * cos(ret) - (ny) * sin(ret);
	to.y2 = to.y1 + (ny) * cos(ret) + (nx) * sin(ret);
	return (to);
}

int				recur_tree(t_env *e, t_pxtopx to,
									int iter, double angle)
{
	if (iter == 0)
		return (1);
	to.x2 = to.x1 - (200 / (12 - iter + 1));
	to.y2 = to.y1;
	to = rotation_tree(to, angle);
	mlxji_draw_line(e->img, e->px, &to);
	to.x1 = to.x2;
	to.y1 = to.y2;
	recur_tree(e, to, iter - 1, loop_angle(angle - (e->mouse_x / 10)));
	recur_tree(e, to, iter - 1, loop_angle(angle + (e->mouse_y / 10)));
	return (1);
}

int				draw_tree(t_env *e)
{
	t_pxtopx	to;
	t_px		px;

	ft_bzero(e->img->data, WIDTH * HEIGHT * 4);
	px.r = 255;
	px.b = 255;
	px.g = 0;
	e->px = &px;
	to.x1 = WIDTH / 2;
	to.y1 = HEIGHT - HEIGHT / 8;
	recur_tree(e, to, 12, 90);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	e->px = NULL;
	return (1);
}
