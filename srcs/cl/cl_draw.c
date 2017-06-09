/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 05:06:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/09 07:00:44 by ntoniolo         ###   ########.fr       */
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
//	clEnqueueTask(cl->cq, cl->kernel, 0, NULL,NULL);
	cl_check_err(cl->err, "clEnqueueNDRangeKernel");
	clFinish(cl->cq);
}

int			cl_draw(t_env *e)
{
	t_cl	*cl;
	t_res	res;
	char	*ret;

	ret = ft_strnew(HEIGHT * WIDTH);
	cl = &(e->cl);
	ft_bzero(&res, sizeof(t_res));
	cl_set_arg(e, &(e->cl));
	cl_run_kernel(e, &(e->cl));
	cl->err = clEnqueueReadBuffer(cl->cq, cl->mem, CL_TRUE, 0,
			HEIGHT * WIDTH * sizeof(char), ret, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueReadBuffer");

	t_px px;

	px.r = 0;
	px.g = 0;	
	int i = 0;
	int y = 0, x;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			px.b = 0;
			if (ret[i] && ret[i] != 50)
				px.b = i * 255 / 50;
			if (x > 0 && y > 0 && x < WIDTH - 50 && y < HEIGHT - 50)
			mlxji_put_pixel(e->img, x, y, &px);
			i++;
			x++;
		}
		y++;
	}
	return (1);
}
