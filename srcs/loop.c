/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 00:21:09 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/20 01:52:15 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			loop(t_env *e)
{
	ncurses_refresh(e, &e->nc);
	gettimeofday(&(e->cur), NULL);
	if ((e->cur.tv_sec - e->step.tv_sec))
	{
//		ft_printf("\033[31mFps : %i\033[0m\n", e->fps);
		e->fps = 0;
		gettimeofday(&e->step, NULL);
//		ft_printf("Zoom : %li Ajj [%i]\nJulia : [%.3f][%.3f]\n",
//				e->tool.zoom, e->tool.iter, e->jul_y, e->jul_x);
	}
	e->clock += e->dir_clock;
	if (e->clock > 360)
		e->clock = 0;
	e->fps++;
//	draw_tree(e);
//	return (2);
	if (!e->num && !e->turn)
		return (1);
	e->turn = 0;
	if (e->num == 3)
		ft_bzero(e->img->data, MEM_OPENCL);
#if (GPU == 1)
	cl_draw(e);
#else
	draw(e);
#endif
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
