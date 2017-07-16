/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   over_sampling_resize_buddha.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 06:17:47 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/16 23:12:15 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	add_val(t_env *e, t_coord coord, char *data, int add)
{
	int			i;
	int			val;
	t_coord		cs;

	val = 0;
	ft_bzero(&cs, sizeof(t_coord));
	i = 0;
	while (cs.y < e->bud.over)
	{
		cs.x = 0;
		while (cs.x < e->bud.over)
		{
			val += data[(coord.x + cs.x) * OPP +
					(coord.y + cs.y) * (e->width_bud * 4) + add];
			i++;
			cs.x++;
		}
		cs.y++;
	}
	val = val / i;
	if (val < 0)
		val = 0;
	if (val > 254)
		val = 254;
	return (val);
}

static void	put_val_in_image(t_env *e, t_coord coord, char *tab, char *new_data)
{
	int	val;
	int	div;

	div = e->varover[e->bud.over];
	val = 0;
	val = add_val(e, coord, tab, 0);
	new_data[(coord.x / div) * OPP + (coord.y / div) * (e->width * 4)] = val;
	/*
	new_data[((e->height_bud - coord.y - 1) / div) * OPP
						+ (coord.x / div) * (e->width * 4)] = val;
	val = add_val(e, coord, tab, 1);
	new_data[((e->height_bud - coord.y - 1) / div) * OPP
					+ (coord.x / div) * (e->width * 4) + 1] = val;
	val = add_val(e, coord, tab, 2);
	new_data[((e->height_bud - coord.y - 1) / div) * OPP
		+ (coord.x / div) * (e->width * 4) + 2] = val;
	*/
}

void		over_sampling_resize_buddha(t_env *e, char *tab)
{
	char	*new_data;
	t_coord coord;

	ft_bzero(&coord, sizeof(t_coord));
	new_data = ft_memalloc((MEM_OPENCL));
	while (coord.y < e->height_bud)
	{
		coord.x = 0;
		while (coord.x < e->width_bud)
		{
			put_val_in_image(e, coord, tab, new_data);
			coord.x += e->bud.over;
		}
		coord.y += e->bud.over;
	}
	mlxji_clear_img(e->img);
	ft_memcpy(e->img->data, new_data, (MEM_OPENCL));
	free(new_data);
}
