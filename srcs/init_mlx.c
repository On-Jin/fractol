/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:54:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/15 21:58:54 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		init_mlx(t_env *e)
{
	e->mlx = mlx_init();
	e->img = mlxji_new_img(e->mlx, e->width, e->height);
	e->win = mlx_new_window(e->mlx, e->width, e->height, "lotcarf");
}
