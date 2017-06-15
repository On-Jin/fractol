/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_buddha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 05:13:30 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/15 20:54:58 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	buddhabrot_color(t_env *e, char *tab)
{
	int i, j;
	int	max_r = 0;
	int	max_g = 0;
	int	max_b = 0;
	char *img;
	int	px_r;
	int	px_g;
	int	px_b;
	int ret;

//	img = e->img->data;
	img = tab;
	i = 0;
	while (i < e->height_bud)
	{
		j = 0;
		while (j < e->width_bud)
		{
			px_b = img[(j * 4) + (i * e->width_bud * 4)];
			px_g = img[(j * 4) + (i * e->width_bud * 4) + 1];
			px_r = img[(j * 4) + (i * e->width_bud * 4) + 2];
			if (px_r > max_r)
				max_r = px_r;
			if (px_g > max_g)
				max_g = px_g;
			if (px_b > max_b)
				max_b = px_b;
			j++;
		}
		i++;
	}
	i = 0;
	///////////////////////// Les couleurs sont géré indépendament... Ensemble ? :)
	e->gain = 1;
	while (i < e->height_bud)
	{
		j = 0;
		while (j < e->width_bud)
		{
			px_b = img[(j * 4) + (i * e->width_bud * 4)];
			ret = 255 / (max_b / e->gain) * px_b;
			if (ret > 250)
				ret = 250;
			img[(j * 4) + (i * e->width_bud * 4)] = ret;

			px_g = img[(j * 4) + (i * e->width_bud * 4) + 1];
			ret = 255 / (max_g / e->gain) * px_g;
			if (ret > 250)
				ret = 250;
			img[(j * 4) + (i * e->width_bud * 4) + 1] = ret;

			px_r = img[(j * 4) + (i * e->width_bud * 4) + 2];
			ret = 255 / (max_r / e->gain)* px_r;
			if (ret > 250)
				ret = 250;
			img[(j * 4) + (i * e->width_bud * 4) + 2] = ret;
			j++;
		}
		i++;
	}
}
