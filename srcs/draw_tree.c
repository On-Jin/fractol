/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 06:48:09 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/19 07:12:58 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include "math.h"

int		draw_tree(t_env *e)
{
	t_pxtopx	to;
	t_px		px;
	px.r = 255;
	px.g = 255;
	px.b = 255;
//	int			len = 100;

	to.x1 = WIDTH / 2;
	to.y1 = HEIGHT;
	double angle = 3.14159265;
	int	iter = 8;
	to.x2 = to.x1 + (cos(angle) * iter);
	to.y2 = to.y1 + (sin(angle) * iter) - 100;
	mlxji_draw_line(e->img, &px, &to);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
