/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_buddha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 05:13:30 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/17 22:29:03 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void find_max_rgb(t_env *e, char *img, int *px, int *max)
{
	int i;
	int j;

	i = 0;
	while (i < e->height_bud)
	{
		j = 0;
		while (j < e->width_bud)
		{
			px[0] = img[(j * 4) + (i * e->width_bud * 4)];
			px[1] = img[(j * 4) + (i * e->width_bud * 4) + 1];
			px[2] = img[(j * 4) + (i * e->width_bud * 4) + 2];
			if (px[0] > max[0])
				max[0] = px[0];
			if (px[1] > max[1])
				max[1] = px[1];
			if (px[2] > max[2])
				max[2] = px[2];
			j++;
		}
		i++;
	}
}

//			ret = trunc(255*sqrt(px_b)/sqrt(max_b));
static void	set_color(t_env *e, char *img, int *px, int *max)
{
	int i;
	int j;
	int	ret;

	i = 0;
	while (i < e->height_bud)
	{
		j = 0;
		while (j < e->width_bud)
		{
			px[0] = img[(j * 4) + (i * e->width_bud * 4)];
			ret = 255 / (max[0] / e->bud.gain) * px[0];
			if (ret > 255)
				ret = 255;
			img[(j * 4) + (i * e->width_bud * 4)] = ret;

			px[1] = img[(j * 4) + (i * e->width_bud * 4) + 1];
			ret = 255 / (max[1] / e->bud.gain) * px[1];
			if (ret > 255)
				ret = 255;
			img[(j * 4) + (i * e->width_bud * 4) + 1] = ret;

			px[2] = img[(j * 4) + (i * e->width_bud * 4) + 2];
			ret = 255 / (max[2] / e->bud.gain)* px[2];
			if (ret > 255)
				ret = 255;
			img[(j * 4) + (i * e->width_bud * 4) + 2] = ret;
			j++;
		}
		i++;
	}
}

void	buddhabrot_color(t_env *e, char *img)
{
	int max[3] = {0, 0, 0};
	int px[3] = {0, 0, 0};

	find_max_rgb(e, img, px, max);
	set_color(e, img, px, max);
}
