/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:17:35 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/20 23:37:05 by ntoniolo         ###   ########.fr       */
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
			//e->tool.ajj_x += ((x * e->varover[e->bud.over] + e->tool.move_x) / 6);//3.6 4
			//e->tool.ajj_y += ((y * e->varover[e->bud.over] + e->tool.move_y) / 6);
			e->tool.ajj_x = 0.8 * (e->tool.ajj_x - x) + x + e->tool.ajj_x * 0.4;
			e->tool.ajj_y = 0.8 * (e->tool.ajj_y - y) + y + e->tool.ajj_y * 0.4;
			e->tool.zoom *= 1.2;

			return (1);
		
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
		//		ft_printf("Ajj_y = %i\n Ajj_x = %i\n", e->tool.ajj_y, e->tool.ajj_x);
		//		ft_printf("Zoom %f\n", e->tool.zoom);
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
			e->tool.ajj_x += ((x * e->varover[e->bud.over] + e->tool.move_x) / 6);//3.6 4
			e->tool.ajj_y += ((y * e->varover[e->bud.over] + e->tool.move_y) / 6);
			e->tool.zoom *=  1.2;
			e->tool.ajj_y *= 1.2;
			e->tool.ajj_x *= 1.2;
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
