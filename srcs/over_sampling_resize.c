/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   over_sampling_resize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:26:01 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/18 05:03:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	add_val(t_env *e, int y, int x, char *data, int add)
{
	int y_s, x_s, i = 0, val = 0, ret;
(void)e;
	y_s = 0;
	while (y_s < e->bud.over)
	{
		x_s = 0;
		while (x_s < e->bud.over)
		{
			val += data[(x + x_s) * OPP + (y + y_s) * (e->width_bud * 4) + add];
			i++;
			x_s++;
		}
		y_s++;
	}
	ret = val / i;
	if (ret < 0)
		ret = 0;
	if (ret > 254)
		ret = 254;
	return (ret);
}

void		over_sampling_resize(t_env *e, char *tab)
{
	char	*new_data;
	int y = 0, x, val;
	int		div = e->varover[e->bud.over];

	new_data = ft_memalloc((MEM_OPENCL));
	while (y < e->height_bud)
	{
		x = 0;
		while (x < e->width_bud)
		{
			val = 0;
			val = add_val(e, y, x, tab, 0);
			new_data[((e->height_bud - y - 1) / div) * OPP + (x / div) * (WIDTH * 4)] = val;
			val = add_val(e, y, x, tab, 1);
			new_data[((e->height_bud - y - 1) / div) * OPP + (x / div) * (WIDTH * 4) + 1] = val;
			val = add_val(e, y, x, tab, 2);
			new_data[((e->height_bud - y - 1) / div) * OPP + (x / div) * (WIDTH * 4) + 2] = val;
			x += e->bud.over;
		}
		y += e->bud.over;
	}
	mlxji_clear_img(e->img);
	ft_memcpy(e->img->data, new_data, (MEM_OPENCL));
	free(new_data);
}
