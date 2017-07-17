/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_buddha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 05:13:30 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/17 06:40:47 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	find_max_rgb(t_env *e, int *img, int *px, int *max)
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

static int	set_ret(t_env *e, int *px, int *max, int pixel)
{
	int ret;

	ret = 255 / (max[pixel] / e->bud.gain) * px[pixel];
	if (ret > 255)
		ret = 255;
	return (ret);
}

static void	set_color(t_env *e, int *img, int *px, int *max)
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
			img[(j * 4) + (i * e->width_bud * 4)] = set_ret(e, px, max, 0);
			px[1] = img[(j * 4) + (i * e->width_bud * 4) + 1];
			img[(j * 4) + (i * e->width_bud * 4) + 1] = set_ret(e, px, max, 1);
			px[2] = img[(j * 4) + (i * e->width_bud * 4) + 2];
			img[(j * 4) + (i * e->width_bud * 4) + 2] = set_ret(e, px, max, 2);
			j++;
		}
		i++;
	}
}

void		buddhabrot_color(t_env *e, int *img)
{
	int max[3];
	int px[3];

	ft_bzero(&max, sizeof(int) * 3);
	ft_bzero(&px, sizeof(int) * 3);
	find_max_rgb(e, img, px, max);
	set_color(e, img, px, max);
}
