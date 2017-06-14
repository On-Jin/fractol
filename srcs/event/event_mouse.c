/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:17:35 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/14 04:46:50 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				event_mouse(int button, int x, int y, t_env *e)
{
	(void)e;
	if (button)
		ft_printf("Button :%i | Y[%i] X[%i]\n", button, y, x);
	if (button == 1)
	{
		//image poussé par le zoom
		//donc je la rattrape :risitas:
		e->ajj_x += ((x + e->move_x) / 6);//3.6 4
		e->ajj_y += ((y + e->move_y) / 6);
/*
		e->ajj_x += (-1 * ((((float)x) / WIDTH) *
					(0.6 + 2.1)));
		e->ajj_y += (((((float)y) / HEIGHT) *
					(1.2)));
		ft_printf("x = %f\n", (((float)x) / WIDTH));
		ft_printf("x = %f\n", (((float)y) / HEIGHT));
*/
		ft_printf("ajj_x %f", e->ajj_x);
		e->zoom *=  1.2;
		e->ajj_y *= 1.2;
		e->ajj_x *= 1.2;
		ft_printf("Ajj_y = %i\n Ajj_x = %i\n", e->ajj_y, e->ajj_x);
		ft_printf("Zoom %f\n", e->zoom);
	}
	else if (button == 5) //AV
	{
		e->ajj_x += ((x + e->move_x) / 6);//3.6 4
		e->ajj_y += ((y + e->move_y) / 6);
		e->zoom *=  1.2;
		e->ajj_y *= 1.2;
		e->ajj_x *= 1.2;
	}
	else if (button == 4) //AR
	{
		e->zoom /=  1.2;
		e->ajj_y /= 1.2;
		e->ajj_x /= 1.2;
		e->ajj_x -= ((x + e->move_x) / 6);//3.6 4
		e->ajj_y -= ((y + e->move_y) / 6);
	}
	return (1);
}
