/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 02:10:14 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/15 23:02:09 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_env(t_env *e)
{
	e->iter = 50;
	if (e->num || !GPU)
	{
		e->zoom = 300;
		e->move_x = (WIDTH / 2 * -1) + ((2.1) * e->zoom);
		e->move_y = (HEIGHT / 2 * -1) + ((1.2) * e->zoom);
	}
	else
	{
		e->over = 4;
		e->varover[0] = 0;
		e->varover[1] = 1;
		e->varover[2] = 2;
		e->varover[3] = 4;
		e->varover[4] = 8;
		e->width_bud = WIDTH * e->varover[e->over];
		e->height_bud = HEIGHT * e->varover[e->over];
		e->mem_opencl_bud = e->width_bud * e->height_bud;
		e->iter = 50;
		e->zoom = 300 * e->over; // 600 over = 2
		e->move_x = (e->width_bud / 2 * -1) + ((2.1) * e->zoom);
		e->move_y = (e->height_bud / 2 * -1) + ((1.2) * e->zoom);
	}
	e->gain = 1;
}

static int get_arg(t_env *e, int argc, char **argv)
{
	if (argc == 1)
		return (0);
	e->num = ft_atoi(argv[1]);
	if (e->num < 0 || e->num > 2)
		return (0);
	return (1);
}

int			main(int argc, char **argv)
{
	t_env e;

	ft_printf("%i %i\n", GPU, M_PRECI);
	ft_bzero(&e, sizeof(t_env));
	if (!(get_arg(&e, argc, argv)))
		return (0);
	init_env(&e);
	init_mlx(&e);
	if (GPU)
		cl_init_opencl(&e);
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
