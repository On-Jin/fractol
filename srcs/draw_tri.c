/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tri.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 05:55:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/15 23:57:45 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		tri_top(t_env *e, t_tr *tr, t_tr *new_tr, int iter)
{
	t_tr	ret;

	ft_bzero(&ret, sizeof(t_tr));
	ret.tx[0] = tr->tx[0];
	ret.ty[0] = tr->ty[0];
	ret.tx[1] = new_tr->tx[1];
	ret.ty[1] = new_tr->ty[1];
	ret.tx[2] = new_tr->tx[0];
	ret.ty[2] = new_tr->ty[0];
	tri_recur(e, iter + 1, ret);
	ret.tx[0] = new_tr->tx[0];
	ret.ty[0] = new_tr->ty[0];
	ret.tx[1] = new_tr->tx[2];
	ret.ty[1] = new_tr->ty[2];
	ret.tx[2] = tr->tx[2];
	ret.ty[2] = tr->ty[2];
	tri_recur(e, iter + 1, ret);
	ret.tx[0] = new_tr->tx[1];
	ret.ty[0] = new_tr->ty[1];
	ret.tx[1] = tr->tx[1];
	ret.ty[1] = tr->ty[1];
	ret.tx[2] = new_tr->tx[2];
	ret.ty[2] = new_tr->ty[2];
	tri_recur(e, iter + 1, ret);
}

static void		tri_take_middle(t_tr *new_tr, t_tr tr)
{
	new_tr->tx[0] = (tr.tx[0] - ((tr.tx[0] - tr.tx[2]) / 2));
	new_tr->ty[0] = (tr.ty[2] - ((tr.ty[2] - tr.ty[0]) / 2));
	new_tr->tx[1] = (tr.tx[1] - ((tr.tx[1] - tr.tx[0]) / 2));
	new_tr->ty[1] = (tr.ty[1] - ((tr.ty[1] - tr.ty[0]) / 2));
	new_tr->tx[2] = (tr.tx[1] - ((tr.tx[1] - tr.tx[2]) / 2));
	new_tr->ty[2] = (tr.ty[1] - ((tr.ty[1] - tr.ty[2]) / 2));
}

static void		tri_draw_tri(t_env *e, t_tr new_tr)
{
	int			k;
	t_pxtopx	to;
	t_px		px;

	px.r = 255;
	px.g = 50;
	px.b = 0;
	k = 0;
	while (k < 3)
	{
		to.x1 = new_tr.tx[k % 3] + e->tool.move_x;
		to.x2 = new_tr.tx[(k + 1) % 3] + e->tool.move_x;
		to.y1 = new_tr.ty[k % 3] + e->tool.move_y;
		to.y2 = new_tr.ty[(k + 1) % 3] + e->tool.move_y;
		if ((to.x1 >= 0 || to.x2 >= 0) && (to.y1 >= 0 || to.y2 >= 0) &&
			(to.x1 < e->width || to.x2 < e->width) &&
							(to.y1 < e->height || to.y2 < e->height))
			mlxji_draw_line(e->img, &px, &to);
		k++;
	}
}

int				tri_recur(t_env *e, int iter, t_tr tr)
{
	t_tr		new_tr;

	if (iter == e->tool.iter)
		return (1);
	ft_bzero(&new_tr, sizeof(t_tr));
	tri_take_middle(&new_tr, tr);
	tri_draw_tri(e, new_tr);
	tri_top(e, &tr, &new_tr, iter);
	return (1);
}

int				draw_tri(t_env *e)
{
	t_tr		tr;
	t_tool		*tool;

	tr = e->tr;
	tool = &e->tool;
	if (e->move == 1)
	{
		tr.tx[0] += tool->move_x / 30;
		tr.tx[1] += tool->move_x / 30 + e->mouse_x;
		tr.tx[2] += tool->move_x / 30 - e->mouse_x;
		tr.ty[0] += tool->move_y / 30 - e->mouse_y;
		tr.ty[1] += tool->move_y / 30;
		tr.ty[2] += tool->move_y / 30;
	}
	tri_draw_tri(e, tr);
	tri_recur(e, 0, tr);
	return (1);
}
