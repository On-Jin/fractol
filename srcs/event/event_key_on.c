/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key_on.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:11:47 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/09 04:44:51 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			event_key_on(int keycode, t_env *e)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 69)
	{
		if (e->iter < 500)
			e->iter += 10;
	}
	else if (keycode == 78)
	{
		if (e->iter > 20)
			e->iter -= 10;
	}
	else if (keycode == 123) //G
		e->move_x -= 10;
	else if (keycode == 124) //D
		e->move_x += 10;
	else if (keycode == 125) //B
		e->move_y += 10;
	else if (keycode == 126) //H
		e->move_y -= 10;
	if (keycode)
		e->key[keycode] = 1;
	return (1);
}