/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key_on.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:11:47 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/17 08:40:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			event_key_on(int keycode, t_env *e)
{
	if (keycode == 53)
		end_of_program(e, NULL);
	if (keycode == 69)
	{
		if (e->tool.iter < 2000)
			e->tool.iter += 10;
//		ft_printf("Iter [%i]\n", e->tool.iter);
	}
	else if (keycode == 78)
	{
		if (e->tool.iter > 20)
			e->tool.iter -= 10;
	}
	else if (keycode == 92)
	{
		if (e->tool.iter > 2)
			e->tool.iter--;
	}
	else if (keycode == 82)
	{
			e->tool.iter+=100000;
	}
	else if (keycode == 88)
	{
		if (e->tool.iter < 2000)
			e->tool.iter++;
	}
	else if (keycode == 123) //G
		e->tool.move_x -= 10;
	else if (keycode == 124) //D
		e->tool.move_x += 10;
	else if (keycode == 125) //B
		e->tool.move_y += 10;
	else if (keycode == 126) //H
		e->tool.move_y -= 10;
	else if (keycode == 91)
	{
		if (e->dir_clock < 350)
			e->dir_clock++;
	}
	else if (keycode == 84)
	{
		if (e->dir_clock > 0)
			e->dir_clock--;
	}
	else if (keycode == 49)
	{
		e->turn = 1;
	}
	else if (keycode == 67)
	{
		e->tool.iter += 1000;
	}
	if (keycode)
		e->key[keycode] = 1;
	return (1);
}
