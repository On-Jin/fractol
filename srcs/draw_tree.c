/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 06:48:09 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/07 16:03:45 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	conversion_radians(double degre)
{
	return (degre / 180 * 3.1415);
}

int		recur_tree(t_env *e, t_px *px, t_pxtopx *to, int iter, double angle)
{
	if (iter == 1)
		return (1);
	to->x2 = to->x1 + (cos(conversion_radians(angle)) * iter * 6);
	to->y2 = to->y1 + (sin(conversion_radians(angle)) * iter * 9) + 100;
	mlxji_draw_line(e->img, px, to);
	to->x1 = to->x2;
	to->y1 = to->y2;
	recur_tree(e, px, to, iter++, angle + 45);
	return (1);
}

int		draw_tree(t_env *e)
{
	t_pxtopx	to;
	t_px		px;

	px.r = 255;
	px.g = 255;
	px.b = 255;
	to.x1 = WIDTH / 2;
	to.y1 = HEIGHT;
	recur_tree(e, &px, &to, 0, 0);
	ft_printf("Finish\n");
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
