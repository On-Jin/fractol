/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 05:06:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/11 20:25:46 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	cl_set_arg(t_env *e, t_cl *cl)
{
	cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem, CL_TRUE, 0, sizeof(char) * MEM_OPENCL, e->img->data, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer");
	cl->err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), (void *)&(cl->mem));
	cl->err = clSetKernelArg(cl->kernel, 1, sizeof(long int), &(e->zoom));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 2, sizeof(long int), &(e->iter));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 3, sizeof(V_PRECI), &(e->ajj_y));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 4, sizeof(V_PRECI), &(e->ajj_x));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 5, sizeof(int), &(e->move_y));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 6, sizeof(int), &(e->move_x));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 7, sizeof(int), &(e->clock));
	cl_check_err(cl->err, "clSetKernelArg");
}

static void	cl_run_kernel(t_env *e, t_cl *cl)
{
	(void)e;
	size_t global_item_size;
	size_t local_item_size;

	global_item_size = WIDTH * HEIGHT;
	cl->err = clGetKernelWorkGroupInfo(cl->kernel, cl->device_id,
				CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &local_item_size, NULL);
	cl_check_err(cl->err, "clGetKernelWorkGroupInfo");
	cl->err = clEnqueueNDRangeKernel(cl->cq, cl->kernel, 1, NULL,
			&global_item_size, &local_item_size, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueNDRangeKernel");
	clFinish(cl->cq);
}

int			cl_draw(t_env *e)
{
	t_cl	*cl;

	cl = &(e->cl);
	cl_set_arg(e, &(e->cl));
	cl_run_kernel(e, &(e->cl));
	cl->err = clEnqueueReadBuffer(cl->cq, cl->mem, CL_TRUE, 0,
			MEM_OPENCL * sizeof(char), e->img->data, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueReadBuffer");
	return (1);
}
