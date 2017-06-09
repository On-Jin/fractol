/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 05:06:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/09 05:43:07 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	cl_set_arg(t_env *e, t_cl *cl)
{
	(void)e;
	cl->err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), (void *)&(cl->mem));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 1, sizeof(float), &(e->zoom));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 2, sizeof(int), &(e->iter));
	cl_check_err(cl->err, "clSetKernelArg");
}

static void	cl_run_kernel(t_env *e, t_cl *cl)
{
	(void)e;
	size_t global_item_size;
	size_t local_item_size;

	global_item_size = WIDTH * HEIGHT;
	local_item_size = 1;
	cl->err = clEnqueueNDRangeKernel(cl->cq, cl->kernel, 1, NULL,
			&global_item_size, &local_item_size, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueNDRangeKernel");
}

int			cl_draw(t_env *e)
{
	t_cl	*cl;
	t_res	res;

	cl = &(e->cl);
	ft_bzero(&res, sizeof(t_res));
	cl_set_arg(e, &(e->cl));
	cl_run_kernel(e, &(e->cl));
	cl->err = clEnqueueReadBuffer(cl->cq, cl->mem, CL_TRUE, 0,
			HEIGHT * WIDTH * sizeof(int), res.ret_iter, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueReadBuffer");
	int i = 0;
	while (i < HEIGHT * WIDTH)
	{
		if (!(i%WIDTH))
			ft_printf("\n");
		ft_printf("%i_", res.ret_iter[i]);
		i++;
	}
	while (1);
	return (1);
}
