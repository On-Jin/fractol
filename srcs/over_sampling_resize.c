/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   over_sampling_resize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:26:01 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/16 00:41:19 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	add_val(t_env *e, int y, int x, char *data, int add)
{
	int y_s, x_s, i = 0, val = 0, ret;
(void)e;
	y_s = 0;
	while (y_s < e->over)
	{
		x_s = 0;
		while (x_s < e->over)
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
	new_data = ft_memalloc((MEM_OPENCL));
	(void)e;(void)new_data;
//	ft_printf("%i to %i\n", (MEM_OPENCL * 4), (MEM_OPENCL * 4) / 4);

	int y = 0, x, val;
	char	*data;
	int		nb = e->over;
	int		div = e->varover[e->over];

	data = tab;
	while (y < e->height_bud)
	{
		x = 0;
		while (x < e->width_bud)
		{
			val = 0;
			val = add_val(e, y, x, data, 0);
			new_data[(x / div) * OPP + (y / div) * (WIDTH * 4)] = val;
			val = add_val(e, y, x, data, 1);
			new_data[(x / div) * OPP + (y / div) * (WIDTH * 4) + 1] = val;
			val = add_val(e, y, x, data, 2);
			new_data[(x / div) * OPP + (y / div) * (WIDTH * 4) + 2] = val;
			x += nb;
		}
		y += nb;
	}
	mlxji_clear_img(e->img);
	ft_memcpy(e->img->data, new_data, (MEM_OPENCL));
	free(new_data);
}
