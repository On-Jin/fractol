/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 20:34:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/10 21:54:44 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_complexe_in(t_env *e, int y, int x)
{
	V_PRECI ratio_x;
	V_PRECI ratio_y;
	V_PRECI dx;
	V_PRECI dy;

	ratio_x = (V_PRECI)x / (HEIGHT * 1.125);
	ratio_y = (V_PRECI)y / HEIGHT;
	dx = e->tool.xmax - e->tool.xmin;
	dy = e->tool.ymax - e->tool.ymin;
	e->tool.xmin += (dx / 20) * ratio_x;
	e->tool.xmax -= (dx / 20) * (1 - ratio_x);
	e->tool.ymin += (dy / 20) * ratio_y;
	e->tool.ymax -= (dy / 20) * (1 - ratio_y);
}

void	zoom_basic_in(t_env *e, int y, int x)
{
	t_tr	*tr;
	t_tool	*tool;

	e->tool.ajj_x = x;
	e->tool.ajj_y = y;
	tr = &e->tr;
	tool = &e->tool;
	tr->tx[0] = 1.2 * (tr->tx[0] - tool->ajj_x) + tool->ajj_x;
	tr->ty[0] = 1.2 * (tr->ty[0] - tool->ajj_y) + tool->ajj_y;
	tr->tx[1] = 1.2 * (tr->tx[1] - tool->ajj_x) + tool->ajj_x;
	tr->ty[1] = 1.2 * (tr->ty[1] - tool->ajj_y) + tool->ajj_y;
	tr->tx[2] = 1.2 * (tr->tx[2] - tool->ajj_x) + tool->ajj_x;
	tr->ty[2] = 1.2 * (tr->ty[2] - tool->ajj_y) + tool->ajj_y;
}

void	zoom_complexe_ar(t_env *e, int y, int x)
{
	V_PRECI ratio_x;
	V_PRECI ratio_y;
	V_PRECI dx;
	V_PRECI dy;

	ratio_x = (V_PRECI)x / (HEIGHT * 1.125);
	ratio_y = (V_PRECI)y / HEIGHT;
	dx = e->tool.xmax - e->tool.xmin;
	dy = e->tool.ymax - e->tool.ymin;
	e->tool.xmin -= (dx / 20) * ratio_x;
	e->tool.xmax += (dx / 20) * (1 - ratio_x);
	e->tool.ymin -= (dy / 20) * ratio_y;
	e->tool.ymax += (dy / 20) * (1 - ratio_y);
}

void	zoom_basic_ar(t_env *e, int y, int x)
{
	t_tr	*tr;
	t_tool	*tool;

	e->tool.ajj_x = x;
	e->tool.ajj_y = y;
	tr = &e->tr;
	tool = &e->tool;
	tr->tx[0] = 0.8 * (tr->tx[0] - tool->ajj_x) + tool->ajj_x;
	tr->ty[0] = 0.8 * (tr->ty[0] - tool->ajj_y) + tool->ajj_y;
	tr->tx[1] = 0.8 * (tr->tx[1] - tool->ajj_x) + tool->ajj_x;
	tr->ty[1] = 0.8 * (tr->ty[1] - tool->ajj_y) + tool->ajj_y;
	tr->tx[2] = 0.8 * (tr->tx[2] - tool->ajj_x) + tool->ajj_x;
	tr->ty[2] = 0.8 * (tr->ty[2] - tool->ajj_y) + tool->ajj_y;
}
