/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 06:48:09 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/13 20:03:38 by ntoniolo         ###   ########.fr       */
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
	if (e->tool.mode % 2 == 0)
		to.x2 = to.x1 - (e->size_tree / (e->tool.iter - iter + 1));
	else
		to.x2 = to.x1 - (e->size_tree / 2 / (e->tool.iter / iter));
	to.y2 = to.y1;
	to = rotation_tree(to, angle);
	if (e->tool.color & 1)
		mlxji_hsv_to_rgb(&e->px, ((360 / (e->tool.iter / iter)) + e->clock) % 360, e->satu, e->value);
	else
		mlxji_hsv_to_rgb(&e->px, ((int)e->hue + e->clock) % 360, e->satu, e->value);
	mlxji_draw_line(e->img, &e->px, &to);
	to.x1 = to.x2;
	to.y1 = to.y2;
	recur_tree(e, to, iter - 1, loop_angle(angle - (e->mouse_x / 10)));
	recur_tree(e, to, iter - 1, loop_angle(angle + (e->mouse_y / 10)));
	return (1);
}

int				draw_tree(t_env *e)
{
	t_pxtopx to;

	to = e->to;
	to.x1 += e->tool.move_x;
	to.y1 += e->tool.move_y;
	ft_bzero(e->img->data, WIDTH * HEIGHT * 4);
	if (!e->psy)
		recur_tree(e, to, e->tool.iter, 90);
	else
		recur_tree(e, to, e->tool.iter, e->mouse_x / 5);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
