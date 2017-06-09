/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_move_mouse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:16:45 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/09 00:24:41 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			event_move_mouse(int x, int y, t_env *e)
{
	e->mouse_x = x;
	e->mouse_y = y;
	return (1);
}