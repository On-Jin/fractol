/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 18:00:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/17 08:40:29 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	free_mlx(t_env *e, t_img *img)
{
	if (!e || !img)
		return ;
	if (e->mlx && e->img)
	mlx_destroy_image(e->mlx, e->img->img);
	if (e->mlx && e->win)
		mlx_destroy_window(e->mlx, e->win);
	if (e->img)
		free(e->img);
}

void		end_of_program(t_env *e, char *str)
{
	free_mlx(e, e->img);
	cl_end_opencl(e, &(e->cl));
	if (e->buff_patern)
		free(e->buff_patern);
	if (e->ftab)
		free(e->ftab);
	delwin(e->nc.win);
	endwin();
	if (str)
		ft_printf("%s", str);
	exit(0);
}
