/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tri.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 05:55:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/18 11:53:54 by ntoniolo         ###   ########.fr       */
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
	new_tr.tx[0] = ft_abs(tr.tx[0] - (ft_abs(tr.tx[0] - tr.tx[2]) / 2));
	new_tr.ty[0] = ft_abs(tr.ty[2] - (ft_abs(tr.ty[2] - tr.ty[0]) / 2));
	new_tr.tx[1] = ft_abs(tr.tx[1] - (ft_abs(tr.tx[1] - tr.tx[0]) / 2));
	new_tr.ty[1] = ft_abs(tr.ty[1] - (ft_abs(tr.ty[1] - tr.ty[0]) / 2));
	new_tr.tx[2] = ft_abs(tr.tx[1] - (ft_abs(tr.tx[1] - tr.tx[2]) / 2));
	new_tr.ty[2] = ft_abs(tr.ty[1] - (ft_abs(tr.ty[1] - tr.ty[2]) / 2));
	while (k < 3)
	{
		to.x1 = new_tr.tx[k % 3];
		to.x2 = new_tr.tx[(k + 1) % 3];
		to.y1 = new_tr.ty[k % 3];
		to.y2 = new_tr.ty[(k + 1) % 3];
		if ((to.x1 > 0 && to.x2 < WIDTH) || ( to.y1 > 0 && to.y2 < HEIGHT))
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
	t_tr		tr;
	t_pxtopx	to;
	t_px		px;
	int			k;
	t_tool		*tool;

	tool = &e->tool;
	px.r = 255;
	px.g = 255;
	px.b = 255;
	int y = tool->move_y ;//+ tool->ajj_y;
	int x = tool->move_x ;//+ tool->ajj_x;
	tr.tx[0] = e->tr.tx[0] + x;
	tr.ty[0] = e->tr.ty[0] + y;
	tr.tx[1] = e->tr.tx[1] + x;
	tr.ty[1] = e->tr.ty[1] + y;
	tr.tx[2] = e->tr.tx[2] + x;
	tr.ty[2] = e->tr.ty[2] + y;
	k = -1;
	while (++k < 3)
	{
		tr.tx[k] = tr.tx[k] * e->tool.zoom / 10;
 		tr.ty[k] = tr.ty[k] * e->tool.zoom / 10;
	}
	k = 0;
	while (k < 3)
	{
		to.x1 = tr.tx[k % 3] + 1;
		to.x2 = tr.tx[(k + 1) % 3];
		to.y1 = tr.ty[k % 3];
		to.y2 = tr.ty[(k + 1) % 3];
		if ((to.x1 > 0 && to.x2 < WIDTH) || ( to.y1 > 0 && to.y2 < HEIGHT))
			mlxji_draw_line(e->img, &px, &to);
		k++;
	}
	recur_a(e, 0, tr);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
