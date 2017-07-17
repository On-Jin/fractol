/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_complexe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 05:14:55 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/17 05:15:34 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_complexe_in(t_env *e, int y, int x)
{
	V_PRECI ratio_x;
	V_PRECI ratio_y;
	V_PRECI dx;
	V_PRECI dy;

	ratio_x = ((V_PRECI)x + e->tool.move_x) / (e->height * 1.125);
	ratio_y = ((V_PRECI)y + e->tool.move_y) / e->height;
	dx = e->tool.xmax - e->tool.xmin;
	dy = e->tool.ymax - e->tool.ymin;
	e->tool.xmin += (dx / 20) * ratio_x;
	e->tool.xmax -= (dx / 20) * (1 - ratio_x);
	e->tool.ymin += (dy / 20) * ratio_y;
	e->tool.ymax -= (dy / 20) * (1 - ratio_y);
}

void	zoom_complexe_ar(t_env *e, int y, int x)
{
	V_PRECI ratio_x;
	V_PRECI ratio_y;
	V_PRECI dx;
	V_PRECI dy;

	ratio_x = ((V_PRECI)x + e->tool.move_x) / (e->height * 1.125);
	ratio_y = ((V_PRECI)y + e->tool.move_y) / e->height;
	dx = e->tool.xmax - e->tool.xmin;
	dy = e->tool.ymax - e->tool.ymin;
	e->tool.xmin -= (dx / 20) * ratio_x;
	e->tool.xmax += (dx / 20) * (1 - ratio_x);
	e->tool.ymin -= (dy / 20) * ratio_y;
	e->tool.ymax += (dy / 20) * (1 - ratio_y);
}
