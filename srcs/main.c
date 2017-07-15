/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 02:10:14 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/16 00:05:29 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_tab(t_env *e)
{
	e->tab_mode[NUM_TREE] = 2;
	e->tab_color[NUM_TREE] = 2;
	e->tab_color[NUM_MANDEL] = 4;
	e->tab_mode[NUM_MANDEL] = 2;
	e->tab_color[NUM_JULIA] = 4;
	e->tab_mode[NUM_JULIA] = 2;
	e->tab_color[NUM_BURN] = 4;
	e->tab_mode[NUM_BURN] = 2;
}

static void	init_env(t_env *e)
{
	e->varover[0] = 0;
	e->varover[1] = 1;
	e->varover[2] = 2;
	e->varover[3] = 4;
	e->varover[4] = 8;
	e->varover[5] = 16;
	ft_strcpy(e->name_fractal[0], "buddhabrot");
	ft_strcpy(e->name_fractal[1], "mandelbrot");
	ft_strcpy(e->name_fractal[2], "julia");
	ft_strcpy(e->name_fractal[3], "sierpinski (NO_GPU)");
	ft_strcpy(e->name_fractal[4], "tree (NO_GPU)");
	ft_strcpy(e->name_fractal[5], "burningship");
	ft_strcpy(e->name_preset[0], "preset_bud/example3");
	ft_strcpy(e->name_preset[1], "preset_bud/example2");
	ft_strcpy(e->name_preset[2], "mandelbrot.cl");
	ft_strcpy(e->name_preset[3], "preset_bud/");
	ft_strcpy(e->name_preset[4], "");
	init_tab(e);
	e->incr_dir = 1;
}

int			main(int argc, char **argv)
{
	t_env e;

	ft_bzero(&e, sizeof(t_env));
	if (!(flag_arg(&e, argc, argv)))
		return (0);
	init_env(&e);
	ncurses_init(&e, &e.nc, NC_HEIGHT, NC_WIDTH);
	while (!e.nc.menu)
		ncurses_menu(&e, &e.nc);
	init_dir(&e);
	init_mlx(&e);
	if (e.flag & F_GPU)
		cl_init_opencl(&e);
	mlx_hook(e.win, 2, 0, &event_key_on, &e);
	mlx_key_hook(e.win, &event_key_off, &e);
	mlx_mouse_hook(e.win, &event_mouse, &e);
	mlx_hook(e.win, 6, 0, &event_move_mouse, &e);
	mlx_loop_hook(e.mlx, &loop, &e);
	mlx_loop(e.mlx);
	end_of_program(&e, NULL);
//	ft_bzero(&e, sizeof(t_env));
//	while(1);
	return (0);
}
