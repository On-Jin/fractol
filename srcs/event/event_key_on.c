/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key_on.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:11:47 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/16 00:00:39 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	event_iter(int keycode, t_env *e)
{
	if (keycode == 69)
		(e->tool.iter + e->incr_dir) < (e->max_iter) ?
								(e->tool.iter) += e->incr_dir : 0;
	else if (keycode == 78)
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

static void	event_mode(int keycode, t_env *e)
{
	if (keycode == 86 && e->tab_mode[e->num])
		e->tool.mode = (e->tool.mode + 1) % e->tab_mode[e->num];
	else if (keycode == 89 && e->tab_color[e->num])
		e->tool.color = (e->tool.color + 1) % e->tab_color[e->num];
	else if (keycode == 83)
		e->hue = e->hue + 1 % 360;
	else if (e->key[82] && keycode == 84)
		e->satu > 0 ? (e->satu -= 0.1) : 0;
	else if (e->key[82] && keycode == 85)
		e->value > 0 ? (e->value -= 0.1) : 0;
	else if (keycode == 84)
		e->satu < 1 ? (e->satu += 0.1) : 0;
	else if (keycode == 85)
		e->value < 1 ? (e->value += 0.1) : 0;
	else if (keycode == 7)
	{
		if (e->psy == 0)
			(e->psy = 1);
		else
			(e->psy = 0);
	}
}

static void	event_other(int keycode, t_env *e)
{
	if (keycode == 91)
	{
		if (e->dir_clock < 350)
			e->dir_clock++;
	}
	else if (keycode == 87)
	{
		if (e->dir_clock > 0)
			e->dir_clock--;
	}
	else if (keycode == 49)
	{
		if (e->move == 0)
			(e->move = 1);
		else
			(e->move = 0);
		e->turn = 1;
	}
}

int			event_key_on(int keycode, t_env *e)
{
	if (keycode == 53)
		end_of_program(e, NULL);
	event_iter(keycode, e);
	event_move(keycode, e);
	event_other(keycode, e);
	event_mode(keycode, e);
	if (keycode)
		e->key[keycode] = 1;
	return (1);
}
