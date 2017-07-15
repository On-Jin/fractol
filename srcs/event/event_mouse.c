/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:17:35 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/16 00:07:13 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		event_scrool_ar(t_env *e, int y, int x)
{
	if (e->num == NUM_TRI)
		zoom_tri_basic_ar(e, y, x);
	else if (e->num == NUM_TREE)
		zoom_tree_basic_ar(e, y, x);
	else
		zoom_complexe_ar(e, y, x);
}

static void		event_scrool_in(t_env *e, int y, int x)
{
	if (e->num == NUM_TRI)
		zoom_tri_basic_in(e, y, x);
	else if (e->num == NUM_TREE)
		zoom_tree_basic_in(e, y, x);
	else
		zoom_complexe_in(e, y, x);
}

static void		event_left_click(t_env *e, int y, int x)
{
	if (e->num == NUM_TRI)
		zoom_tri_basic_in(e, y, x);
	else if (e->num == NUM_TREE)
		zoom_tree_basic_in(e, y, x);
	else
		zoom_complexe_in(e, y, x);
}

int				event_mouse(int button, int x, int y, t_env *e)
{
	if (button == 1)
		event_left_click(e, y, x);
	else if (button == 5)
		event_scrool_in(e, y, x);
	else if (button == 4)
		event_scrool_ar(e, y, x);
	return (1);
}
