/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 20:34:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/17 05:15:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_tri_basic_ar(t_env *e, int y, int x)
{
	t_tr	*tr;

	tr = &e->tr;
	tr->tx[0] = 0.8 * (tr->tx[0] - x) + x;
	tr->ty[0] = 0.8 * (tr->ty[0] - y) + y;
	tr->tx[1] = 0.8 * (tr->tx[1] - x) + x;
	tr->ty[1] = 0.8 * (tr->ty[1] - y) + y;
	tr->tx[2] = 0.8 * (tr->tx[2] - x) + x;
	tr->ty[2] = 0.8 * (tr->ty[2] - y) + y;
}

void	zoom_tri_basic_in(t_env *e, int y, int x)
{
	t_tr	*tr;

	tr = &e->tr;
	tr->tx[0] = 1.2 * (tr->tx[0] - x) + x;
	tr->ty[0] = 1.2 * (tr->ty[0] - y) + y;
	tr->tx[1] = 1.2 * (tr->tx[1] - x) + x;
	tr->ty[1] = 1.2 * (tr->ty[1] - y) + y;
	tr->tx[2] = 1.2 * (tr->tx[2] - x) + x;
	tr->ty[2] = 1.2 * (tr->ty[2] - y) + y;
}

void	zoom_tree_basic_ar(t_env *e, int y, int x)
{
	t_pxtopx	*to;

	to = &e->to;
	to->x1 = 0.8 * (to->x1 - x) + x;
	to->y1 = 0.8 * (to->y1 - y) + y;
	e->size_tree *= 0.8;
}

void	zoom_tree_basic_in(t_env *e, int y, int x)
{
	t_pxtopx	*to;

	to = &e->to;
	to->x1 = 1.2 * (to->x1 - x) + x;
	to->y1 = 1.2 * (to->y1 - y) + y;
	e->size_tree *= 1.2;
}
