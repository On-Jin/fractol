/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:54:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/09 04:50:38 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		init_mlx(t_env *e)
{
	e->mlx = mlx_init();
	e->img = mlxji_new_img(e->mlx, WIDTH, HEIGHT);
	e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, "lotcarf");
}
