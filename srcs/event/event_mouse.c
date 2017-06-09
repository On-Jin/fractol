/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:17:35 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/09 02:58:11 by ntoniolo         ###   ########.fr       */
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
		e->ajj_x += (x / 3.6);
		e->ajj_y += (y / 3.6);
		ft_printf("%i / 6 = %i\n%i / 6 = %i\n\n", y, e->ajj_y, x, e->ajj_x);
		e->zoom *=  1.4;
		e->ajj_y *= 1.4;
		e->ajj_x *= 1.4;
		ft_printf("Ajj_y = %i\n Ajj_x = %i\n", e->ajj_y, e->ajj_x);
		ft_printf("Zoom %f\n", e->zoom);
	}
	return (1);
}
