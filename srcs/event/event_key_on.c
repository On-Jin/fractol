/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key_on.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:11:47 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/10 20:24:42 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	event_iter(int keycode, t_env *e)
{
	if (keycode == 69 && e->num)
		(e->tool.iter + e->incr_dir) < (e->max_iter) ?
								(e->tool.iter) += e->incr_dir : 0;
	else if (keycode == 78 && e->num)
		(e->tool.iter - e->incr_dir) > (e->min_iter) ?
								(e->tool.iter) -= e->incr_dir : 0;
	else if (keycode == 88)
		e->incr_dir < MAX_INCR ? (e->incr_dir) *= 10 : 0;
	else if (keycode == 92)
		e->incr_dir > 1 ? (e->incr_dir) /= 10 : 0;
}

static void	event_move(int keycode, t_env *e)
{
	if (keycode == 123)
		e->tool.move_x -= 10;
	else if (keycode == 124)
		e->tool.move_x += 10;
	else if (keycode == 125)
		e->tool.move_y += 10;
	else if (keycode == 126)
		e->tool.move_y -= 10;
}

static void	event_other(int keycode, t_env *e)
{
	if (keycode == 91)
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
		e->turn = 1;
}

int			event_key_on(int keycode, t_env *e)
{
	if (keycode == 53)
		end_of_program(e, NULL);
	event_iter(keycode, e);
	event_move(keycode, e);
	event_other(keycode, e);
	if (keycode)
		e->key[keycode] = 1;
	return (1);
}
