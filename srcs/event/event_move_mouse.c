/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_move_mouse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:16:45 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/15 23:05:11 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			event_move_mouse(int x, int y, t_env *e)
{
	if (e->move)
	{
		e->mouse_x = x;
		e->mouse_y = y;
	}
	e->jul_y = ((float)e->mouse_y / (float)e->height) * 3 - 1.5;
	e->jul_x = ((float)e->mouse_x / (float)e->width) * 3 - 1.5;
	return (1);
}
