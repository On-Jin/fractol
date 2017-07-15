/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 07:07:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/16 01:26:27 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	cl_set_arg_buddhabrot(t_env *e, t_cl *cl)
{
	cl->err = clSetKernelArg(cl->kernel, 0,
			sizeof(cl_mem), (void *)&(cl->mem));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 1,
			sizeof(cl_mem), (void *)&(cl->mem2));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 2,
			sizeof(cl_mem), (void *)&(cl->mem3));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 3, sizeof(t_tool), &(e->tool));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 4, sizeof(int), &(e->clock));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 5, sizeof(t_bud), &(e->bud));
	cl_check_err(cl->err, "clSetKernelArg");
}

static void	cl_set_arg_mandelbrot(t_env *e, t_cl *cl)
{
	cl_check_err(cl->err, "clEnqueueWriteBuffer");
	cl->err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), (void *)&(cl->mem));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 1, sizeof(t_tool), &(e->tool));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 2, sizeof(int), &(e->clock));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 3, sizeof(int), &(e->num));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 4, sizeof(float), &(e->jul_y));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 5, sizeof(float), &(e->jul_x));
	cl_check_err(cl->err, "clSetKernelArg");
}

void		cl_set_buffer_and_arg(t_env *e, t_cl *cl)
{
	if (e->num)
		cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem, CL_TRUE, 0,
				sizeof(char) * MEM_OPENCL, e->img->data, 0, NULL, NULL);
	else
	{
		bzero(e->buff_patern, e->mem_opencl * 4);
		cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem, CL_TRUE, 0, e->mem_opencl * 4, e->buff_patern, 0, NULL, NULL);
		
		cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem2, CL_TRUE, 0,
				sizeof(int) * e->mem_opencl, e->buff_patern, 0, NULL, NULL);
		cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem3, CL_TRUE, 0,
				sizeof(int) * e->mem_opencl, e->buff_patern, 0, NULL, NULL);
	}
	if (e->num)
		cl_set_arg_mandelbrot(e, cl);
	else
		cl_set_arg_buddhabrot(e, cl);
}
