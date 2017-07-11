/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 02:10:14 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/10 22:08:50 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_basic(t_env *e, t_tool *tool)
{
	e->tool.iter = 50;
	tool->zoom = 300;
	tool->move_x = (WIDTH / 2 * -1) + ((2.1) * tool->zoom);
	tool->move_y = (HEIGHT / 2 * -1) + ((1.2) * tool->zoom);
	e->bud.over = 1;
	tool->xmin = -2.1;
	tool->xmax = 0.6;
	tool->ymin = -1.2;
	tool->ymax = 1.2;
	e->max_iter = 10000;
	e->min_iter = 10;
}

static void	init_bud(t_env *e, t_tool *tool, t_bud *bud)
{
	int		set_zoom[5];

	set_zoom[0] = 0;
	set_zoom[1] = 300;
	set_zoom[2] = 700;
	set_zoom[3] = 1400;
	set_zoom[4] = 3000;
	e->width_bud = HEIGHT * e->varover[bud->over];
	e->height_bud = WIDTH * e->varover[bud->over];
	e->mem_opencl_bud = e->width_bud * e->height_bud;
	(void)tool;
	tool->move_y = (e->height_bud / 2 * -1) + ((1.2) * set_zoom[bud->over]);
	e->buff_patern = ft_memalloc(e->mem_opencl_bud * sizeof(int));
	e->ftab = ft_memalloc(e->mem_opencl_bud * 4);
	e->max_iter = 100000000;
	e->min_iter = 10;
}

static void	init_sierpinski(t_env *e, t_tool *tool)
{
	(void)e;
	tool->zoom = 1;
	tool->iter = 1;
	e->bud.over = 1;
	tool->move_x = 0;
	tool->move_y = 0;
	e->tr.tx[0] = WIDTH / 2;
	e->tr.ty[0] = 300;
	e->tr.tx[1] = WIDTH / 2 + 100;
	e->tr.ty[1] = 400;
	e->tr.tx[2] = WIDTH / 2 - 100;
	e->tr.ty[2] = 400;
	e->max_iter = 12;
	e->min_iter = 1;
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
	ft_strcpy(e->name_preset[0], "preset_bud/example3");
	ft_strcpy(e->name_preset[1], "preset_bud/example2");
	ft_strcpy(e->name_preset[2], "mandelbrot.cl");
	ft_strcpy(e->name_preset[3], "preset_bud/");
	ft_strcpy(e->name_preset[4], "");
	e->incr_dir = 1;
}

static void	init_dir(t_env *e)
{
	t_tool *tool;

	tool = &e->tool;
	tool->xmin = -2.1;
	tool->xmax = 0.6;
	tool->ymin = -1.2;
	tool->ymax = 1.2;
	if (e->num == 3)
		init_sierpinski(e, &e->tool);
	else if (e->num || !GPU)
		init_basic(e, &e->tool);
	else
		init_bud(e, &e->tool, &e->bud);
}

static int	get_arg(t_env *e, int argc, char **argv)
{
	(void)e;
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("./fractol [NOTHING]\n", 2);
		return (0);
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_env e;

	ft_bzero(&e, sizeof(t_env));
	if (!(get_arg(&e, argc, argv)))
		return (0);
	init_env(&e);
//	ncurses_init(&e, &e.nc, NC_HEIGHT, NC_WIDTH);
//	while (!e.nc.menu)
//		ncurses_menu(&e, &e.nc);
	init_dir(&e);
	init_mlx(&e);
	if (GPU)
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
