/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 21:52:37 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/17 03:39:15 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_basic(t_env *e, t_tool *tool)
{
	e->tool.iter = 50;
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
	(void)tool;
	e->height_bud = e->height * e->varover[bud->over];
	e->width_bud = e->width * e->varover[bud->over];
	e->mem_opencl = e->width_bud * e->height_bud;
	e->buff_patern = ft_memalloc(e->mem_opencl * sizeof(int));
	e->ftab = ft_memalloc(e->mem_opencl * 4 * 4);
	e->max_iter = 100000000;
	e->min_iter = 10;
}

static void	init_sierpinski(t_env *e, t_tool *tool)
{
	(void)e;
	tool->iter = 1;
	e->bud.over = 1;
	tool->move_x = 0;
	tool->move_y = 0;
	e->tr.tx[0] = e->width / 2;
	e->tr.ty[0] = 300;
	e->tr.tx[1] = e->width / 2 + 100;
	e->tr.ty[1] = 400;
	e->tr.tx[2] = e->width / 2 - 100;
	e->tr.ty[2] = 400;
	e->max_iter = 12;
	e->min_iter = 1;
}

static void	init_tree(t_env *e, t_tool *tool)
{
	tool->iter = 12;
	e->max_iter = 17;
	e->min_iter = 1;
	e->to.x1 = e->width / 2;
	e->to.y1 = e->height - e->height / 8;
	e->size_tree = 200;
	e->value = 0.9;
	e->satu = 0.9;
}

static int	verif_fract(t_env *e)
{
	if ((e->num == NUM_BUDD || e->num == NUM_BURN)
			&& !(e->flag & F_GPU))
	{
		ft_putstr_fd("Impossible en mode CPU\n", 2);
		return (0);
	}
	if ((e->num == NUM_TRI || e->num == NUM_TREE)
			&& (e->flag & F_GPU))
	{
		ft_putstr_fd("IMpossible en mode GPU\n", 2);
		return (0);
	}
	return (1);
}

void		init_dir(t_env *e)
{
	if (e->flag & F_GPU)
	{
		e->width = WIDTH_GPU;
		e->height = HEIGHT_GPU;
	}
	else
	{
		e->width = WIDTH_CPU;
		e->height = HEIGHT_CPU;
	}
	if (!(verif_fract(e)))
		end_of_program(e, NULL);
	if (e->num == 3)
		init_sierpinski(e, &e->tool);
	else if (e->num == 4)
		init_tree(e, &e->tool);
	else if (e->num)
		init_basic(e, &e->tool);
	else
		init_bud(e, &e->tool, &e->bud);
}
