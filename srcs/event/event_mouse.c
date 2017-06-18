/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:17:35 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/18 05:08:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				event_mouse(int button, int x, int y, t_env *e)
{
	(void)e;
//	if (button)
//		ft_printf("Button :%i | Y[%i] X[%i]\n", button, y, x);
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
		}
/*
		e->tool.ajj_x += (-1 * ((((float)x) / WIDTH) *
					(0.6 + 2.1)));
		e->tool.ajj_y += (((((float)y) / HEIGHT) *
					(1.2)));
		ft_printf("x = %f\n", (((float)x) / WIDTH));
		ft_printf("x = %f\n", (((float)y) / HEIGHT));
*/
//		ft_printf("ajj_x %f", e->tool.ajj_x);
		e->tool.zoom *=  1.2;
		e->tool.ajj_y *= 1.2;
		e->tool.ajj_x *= 1.2;
//		ft_printf("Ajj_y = %i\n Ajj_x = %i\n", e->tool.ajj_y, e->tool.ajj_x);
//		ft_printf("Zoom %f\n", e->tool.zoom);
	}
	else if (button == 5) //AV
	{
		e->tool.ajj_x += ((x * e->varover[e->bud.over] + e->tool.move_x) / 6);//3.6 4
		e->tool.ajj_y += ((y * e->varover[e->bud.over] + e->tool.move_y) / 6);
		e->tool.zoom *=  1.2;
		e->tool.ajj_y *= 1.2;
		e->tool.ajj_x *= 1.2;
	}
	else if (button == 4) //AR
	{
		e->tool.zoom /=  1.2;
		e->tool.ajj_y /= 1.2;
		e->tool.ajj_x /= 1.2;
		e->tool.ajj_x -= ((x * e->varover[e->bud.over] + e->tool.move_x) / 6);//3.6 4
		e->tool.ajj_y -= ((y * e->varover[e->bud.over] + e->tool.move_y) / 6);
	}
	return (1);
}
