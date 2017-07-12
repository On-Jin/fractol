/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:17:35 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/12 22:49:02 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				event_mouse(int button, int x, int y, t_env *e)
{
	(void)e;
	if (button == 1)
	{
		if (e->num == NUM_TRI)
			zoom_tri_basic_in(e, y, x);
		else if (e->num == NUM_TREE)
			zoom_tree_basic_in(e, y, x);
		else
			zoom_complexe_in(e, y, x);
	}
	else if (button == 5)
	{
		if (e->num == NUM_TRI)
			zoom_tri_basic_in(e, y, x);
		else if (e->num == NUM_TREE)
			zoom_tree_basic_in(e, y, x);
		else
			zoom_complexe_in(e, y, x);
	}
	else if (button == 4)
	{
		if (e->num == NUM_TRI)
			zoom_tri_basic_ar(e, y, x);
		else if (e->num == NUM_TREE)
			zoom_tree_basic_ar(e, y, x);
		else
			zoom_complexe_ar(e, y, x);
	}
	return (1);
}
