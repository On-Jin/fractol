/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key_on.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:11:47 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/07 16:57:58 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	incr_iter(int keycode, t_env *e)
{
	if (keycode == 69 && e->num != NUM_TRI)
		(e->tool.iter + e->incr_dir) < (e->max_iter) ?
								(e->tool.iter) += e->incr_dir : 0;
	else if (keycode == 78 && e->num != NUM_TRI)
		(e->tool.iter + e->incr_dir) > (e->min_iter) ?
								(e->tool.iter) -= e->incr_dir : 0;
	else if (keycode == 88)
		e->incr_dir < MAX_INCR ? (e->incr_dir) *= 10 : 0;
	else if (keycode == 92)
		e->incr_dir > 10 ? (e->incr_dir) /= 10 : 0;
}

int			event_key_on(int keycode, t_env *e)
{
	if (keycode == 53)
		end_of_program(e, NULL);
	incr_iter(keycode, e);
	if (keycode == 123) //G
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
