/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:21:09 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/11 14:54:59 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			loop(t_env *e)
{
	gettimeofday(&(e->cur), NULL);
	if ((e->cur.tv_sec - e->step.tv_sec))
	{
		ft_printf("\033[31mFps : %i\033[0m\n", e->fps);
		e->fps = 0;
		gettimeofday(&e->step, NULL);
		ft_printf("Zoom : %lf Ajj [%lf]\n", e->zoom, e->iter);
	}
	e->clock += e->dir_clock;
	if (e->clock > 360)
		e->clock = 0;
	mlxji_clear_img(e->img);
	cl_draw(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	e->fps++;
	return (1);
}
