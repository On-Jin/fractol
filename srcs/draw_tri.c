/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tri.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 05:55:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/19 07:28:24 by ntoniolo         ###   ########.fr       */
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
		to.x1 = new_tr.tx[k % 3];
		to.x2 = new_tr.tx[(k + 1) % 3];
		to.y1 = new_tr.ty[k % 3];
		to.y2 = new_tr.ty[(k + 1) % 3];
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

double	conversion_radians(double degre)
{
	    return (degre/180*3.14159265);
}
#include <math.h>
int		draw_tri(t_env *e)
{
	t_tr		*tr;
	t_tr		new;
	t_pxtopx	to;
	t_px		px;
	int			k;
	t_tool		*tool;

	tr = &e->tr;
	tool = &e->tool;
	px.r = 255;
	px.g = 255;
	px.b = 255;
	/*double angle = 10;
	double ca = cos(conversion_radians(angle));
	double sa = sin(conversion_radians(angle));
	new.tx[0] = tool->zoom * ((tr->tx[0] * ca - tr->ty[0] * sa) - tool->ajj_x) + tool->ajj_x;
	new.ty[0] = tool->zoom * ((tr->ty[0] * ca - tr->tx[0] * sa) - tool->ajj_y) + tool->ajj_y;
	new.tx[1] = tool->zoom * ((tr->tx[1] * ca - tr->ty[1] * sa) - tool->ajj_x) + tool->ajj_x;
	new.ty[1] = tool->zoom * ((tr->ty[1] * ca - tr->tx[1] * sa) - tool->ajj_y) + tool->ajj_y;
	new.tx[1] = tool->zoom * ((tr->tx[2] * ca - tr->ty[2] * sa) - tool->ajj_x) + tool->ajj_x;
	new.ty[1] = tool->zoom * ((tr->ty[2] * ca - tr->tx[2] * sa) - tool->ajj_y) + tool->ajj_y;
	*/
	new.tx[0] = tool->zoom * (tr->tx[0] - tool->ajj_x) + tool->ajj_x;
	new.ty[0] = tool->zoom * (tr->ty[0] - tool->ajj_y) + tool->ajj_y;
	new.tx[1] = tool->zoom * (tr->tx[1] - tool->ajj_x) + tool->ajj_x;
	new.ty[1] = tool->zoom * (tr->ty[1] - tool->ajj_y) + tool->ajj_y;
	new.tx[2] = tool->zoom * (tr->tx[2] - tool->ajj_x) + tool->ajj_x;
	new.ty[2] = tool->zoom * (tr->ty[2] - tool->ajj_y) + tool->ajj_y;
	k = -1;
	while (++k < 3)
	{
		tr->tx[k] = (int)(tr->tx[k]);
 		tr->ty[k] = (int)(tr->ty[k]);
	}
	k = 0;
	while (k < 3)
	{
		to.x1 = new.tx[k % 3];
		to.x2 = new.tx[(k + 1) % 3];
		to.y1 = new.ty[k % 3];
		to.y2 = new.ty[(k + 1) % 3];
		mlxji_draw_line(e->img, &px, &to);
		k++;
	}
	recur_a(e, 0, new);
	return (1);
}
