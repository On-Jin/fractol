/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:17:35 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/29 08:46:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				event_mouse(int button, int x, int y, t_env *e)
{
	(void)e;
	if (button == 1)
	{
		//image poussé par le zoom
		//donc je la rattrape :risitas:
		if (!e->num)
		{
			e->tool.ajj_y += ((x * e->varover[e->bud.over] + e->tool.move_y) / 6);//3.6 4
			e->tool.ajj_x += ((y * e->varover[e->bud.over] + e->tool.move_x) / 6);
		}
		else
		{
			e->tool.ajj_x += ((x * e->varover[e->bud.over] + e->tool.move_x) / 6);//3.6 4
			e->tool.ajj_y += ((y * e->varover[e->bud.over] + e->tool.move_y) / 6);
/*			e->tool.ajj_x = 0.8 * (e->tool.ajj_x - x) + x + e->tool.ajj_x * 0.4;
			e->tool.ajj_y = 0.8 * (e->tool.ajj_y - y) + y + e->tool.ajj_y * 0.4;
			e->tool.zoom *= 1.2;*/
		}
		//		ft_printf("ajj_x %f", e->tool.ajj_x);
		if (e->num == 3)
		{
			e->tool.ajj_x = x;
			e->tool.ajj_y = y;
			t_tr *tr;
			t_tool *tool;
			tr = &e->tr;
			tool = &e->tool;
			tr->tx[0] = 1.2 * (tr->tx[0] - tool->ajj_x) + tool->ajj_x ;
			tr->ty[0] = 1.2 * (tr->ty[0] - tool->ajj_y) + tool->ajj_y ;
			tr->tx[1] = 1.2 * (tr->tx[1] - tool->ajj_x) + tool->ajj_x ;
			tr->ty[1] = 1.2 * (tr->ty[1] - tool->ajj_y) + tool->ajj_y ;
			tr->tx[2] = 1.2 * (tr->tx[2] - tool->ajj_x) + tool->ajj_x ;
			tr->ty[2] = 1.2 * (tr->ty[2] - tool->ajj_y) + tool->ajj_y ;
		}
		else
		{
			e->tool.zoom *= 1.2;
			e->tool.ajj_y *= 1.2;
			e->tool.ajj_x *= 1.2;
		}
	}
	else if (button == 5) //AV
	{
		if (e->num == 3)
		{
			e->tool.ajj_x = x;
			e->tool.ajj_y = y;
			t_tr *tr;
			t_tool *tool;
			tr = &e->tr;
			tool = &e->tool;
			tr->tx[0] = 1.2 * (tr->tx[0] - tool->ajj_x) + tool->ajj_x ;
			tr->ty[0] = 1.2 * (tr->ty[0] - tool->ajj_y) + tool->ajj_y ;
			tr->tx[1] = 1.2 * (tr->tx[1] - tool->ajj_x) + tool->ajj_x ;
			tr->ty[1] = 1.2 * (tr->ty[1] - tool->ajj_y) + tool->ajj_y ;
			tr->tx[2] = 1.2 * (tr->tx[2] - tool->ajj_x) + tool->ajj_x ;
			tr->ty[2] = 1.2 * (tr->ty[2] - tool->ajj_y) + tool->ajj_y ;
		}
		else
		{
			/*
			e->tool.ajj_x += ((x * e->varover[e->bud.over] + e->tool.move_x) / 6);//3.6 4
			e->tool.ajj_y += ((y * e->varover[e->bud.over] + e->tool.move_y) / 6);
			e->tool.zoom *=  1.2;
			e->tool.ajj_y *= 1.2;
			e->tool.ajj_x *= 1.2;
			*/
			V_PRECI ratio_x = (V_PRECI)x / (HEIGHT * 1.125);
			V_PRECI ratio_y = (V_PRECI)y / HEIGHT;
			V_PRECI dx = e->tool.xmax - e->tool.xmin;
			V_PRECI dy = e->tool.ymax - e->tool.ymin;
			e->tool.xmin += (dx / 20) * ratio_x;
			e->tool.xmax -= (dx / 20) * (1 - ratio_x);
			e->tool.ymin += (dy / 20) * ratio_y;
			e->tool.ymax -= (dy / 20) * (1 - ratio_y);
			return (1);
		}
	}
	else if (button == 4) //AR
	{
		if (e->num == 3)
		{
			e->tool.ajj_x = x;
			e->tool.ajj_y = y;
			t_tr *tr;
			t_tool *tool;
			tr = &e->tr;
			tool = &e->tool;
			tr->tx[0] = 0.8 * (tr->tx[0] - tool->ajj_x) + tool->ajj_x ;
			tr->ty[0] = 0.8 * (tr->ty[0] - tool->ajj_y) + tool->ajj_y ;
			tr->tx[1] = 0.8 * (tr->tx[1] - tool->ajj_x) + tool->ajj_x ;
			tr->ty[1] = 0.8 * (tr->ty[1] - tool->ajj_y) + tool->ajj_y ;
			tr->tx[2] = 0.8 * (tr->tx[2] - tool->ajj_x) + tool->ajj_x ;
			tr->ty[2] = 0.8 * (tr->ty[2] - tool->ajj_y) + tool->ajj_y ;
		}
		else
		{
			e->tool.zoom /=  1.2;
			e->tool.ajj_y /= 1.2;
			e->tool.ajj_x /= 1.2;
			e->tool.ajj_x -= ((x * e->varover[e->bud.over] + e->tool.move_x) / 6);//3.6 4
		}
		e->tool.ajj_y -= ((y * e->varover[e->bud.over] + e->tool.move_y) / 6);
	}
	return (1);
}
