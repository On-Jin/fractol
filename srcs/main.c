/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 02:10:14 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/09 01:12:45 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_env(t_env *e)
{
	e->zoom = 100;
	e->iter = 50;
}

int			main(void)
{
	t_env e;

	ft_bzero(&e, sizeof(t_env));
	init_env(&e);
	init_mlx(&e);
	cl_init_opencl(&e);
	draw(&e);
	mlx_hook(e.win, 2, 0, &event_key_on, &e);
	mlx_key_hook(e.win, &event_key_off, &e);
	mlx_mouse_hook(e.win, &event_mouse, &e);
	mlx_hook(e.win, 6, 0, &event_move_mouse, &e);
	mlx_loop_hook(e.mlx, &loop, &e);
	mlx_loop(e.mlx);
	end_of_program(&e);
//	ft_bzero(&e, sizeof(t_env));
//	while(1);
	return (0);
}
