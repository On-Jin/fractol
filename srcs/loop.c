/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:21:09 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/14 01:31:18 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			loop(t_env *e)
{
	ncurses_refresh(e, &e->nc);
	gettimeofday(&(e->cur), NULL);
	if ((e->cur.tv_sec - e->step.tv_sec))
	{
		e->ret_fps = e->fps;
		e->fps = 0;
		gettimeofday(&e->step, NULL);
	}
	e->clock += e->dir_clock;
	if (e->clock > 360)
		e->clock = 0;
	e->fps++;
	if (!e->num && !e->turn)
		return (1);
	e->turn = 0;
	if (e->num == 3)
		ft_bzero(e->img->data, MEM_OPENCL);
	if (GPU == 1)
		cl_draw(e);
	else
		draw(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
