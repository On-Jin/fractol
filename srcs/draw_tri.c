/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tri.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 05:55:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/20 01:06:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		recur_a(t_env *e, int iter, t_tr tr)
{
	int 		i;
	t_tr		new_tr;
	t_tr		ret;
	t_px		px;
	t_pxtopx	to;
	px.r = 255;
	px.g = 255;
	px.b = 255;

	if (iter == e->tool.iter)
		return (1);
	ft_bzero(&new_tr, sizeof(t_tr));
	ft_bzero(&ret, sizeof(t_tr));
	i = 0;
	int k = 0;
	new_tr.tx[0] = (tr.tx[0] - (ft_abs(tr.tx[0] - tr.tx[2]) / 2));
	new_tr.ty[0] = (tr.ty[2] - (ft_abs(tr.ty[2] - tr.ty[0]) / 2));
	new_tr.tx[1] = (tr.tx[1] - (ft_abs(tr.tx[1] - tr.tx[0]) / 2));
	new_tr.ty[1] = (tr.ty[1] - (ft_abs(tr.ty[1] - tr.ty[0]) / 2));
	new_tr.tx[2] = (tr.tx[1] - (ft_abs(tr.tx[1] - tr.tx[2]) / 2));
	new_tr.ty[2] = (tr.ty[1] - (ft_abs(tr.ty[1] - tr.ty[2]) / 2));
	while (k < 3)
	{
		to.x1 = new_tr.tx[k % 3] + e->tool.move_x;
		to.x2 = new_tr.tx[(k + 1) % 3] + e->tool.move_x;
		to.y1 = new_tr.ty[k % 3] + e->tool.move_y;
		to.y2 = new_tr.ty[(k + 1) % 3] + e->tool.move_y;
		if ((to.x1 >= 0 || to.x2 >= 0) && (to.y1 >= 0 || to.y2 >= 0) &&
			(to.x1 < WIDTH || to.x2 < WIDTH) && (to.y1 < HEIGHT || to.y2 < HEIGHT))
			mlxji_draw_line(e->img, &px, &to);
		k++;
	}
	ret.tx[0] = tr.tx[0];
	ret.ty[0] = tr.ty[0];
	ret.tx[1] = new_tr.tx[1];
	ret.ty[1] = new_tr.ty[1];
	ret.tx[2] = new_tr.tx[0];
	ret.ty[2] = new_tr.ty[0];
	recur_a(e, iter+1, ret);

	ret.tx[0] = new_tr.tx[0];
	ret.ty[0] = new_tr.ty[0];
	ret.tx[1] = new_tr.tx[2];
	ret.ty[1] = new_tr.ty[2];
	ret.tx[2] = tr.tx[2];
	ret.ty[2] = tr.ty[2];
	recur_a(e, iter+1, ret);

	ret.tx[0] = new_tr.tx[1];
	ret.ty[0] = new_tr.ty[1];
	ret.tx[1] = tr.tx[1];
	ret.ty[1] = tr.ty[1];
	ret.tx[2] = new_tr.tx[2];
	ret.ty[2] = new_tr.ty[2];
	recur_a(e, iter+1, ret);
	return (1);
}

int		draw_tri(t_env *e)
{
	t_tr		*tr;
	t_pxtopx	to;
	t_px		px;
	int			k;
	t_tool		*tool;

	tr = &e->tr;
	tool = &e->tool;
	px.r = 255;
	px.g = 255;
	px.b = 255;

	k = 0;
	while (k < 3)
	{
		to.x1 = e->tr.tx[k % 3] + e->tool.move_x;
		to.x2 = e->tr.tx[(k + 1) % 3] + e->tool.move_x;
		to.y1 = e->tr.ty[k % 3] + e->tool.move_y;
		to.y2 = e->tr.ty[(k + 1) % 3] + e->tool.move_y;
		mlxji_draw_line(e->img, &px, &to);
		k++;
	}
	recur_a(e, 0, e->tr);
	return (1);
}
