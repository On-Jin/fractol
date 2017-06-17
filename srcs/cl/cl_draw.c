/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 05:06:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/17 11:51:28 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	cl_set_arg(t_env *e, t_cl *cl)
{
	if (e->num)
		cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem, CL_TRUE, 0, sizeof(char) * MEM_OPENCL, e->img->data, 0, NULL, NULL);
	else
	{
		bzero(e->buff_patern, e->mem_opencl_bud * 4);
		cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem, CL_TRUE, 0, sizeof(int) * e->mem_opencl_bud, e->buff_patern, 0, NULL, NULL);
		cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem2, CL_TRUE, 0, sizeof(int) * e->mem_opencl_bud, e->buff_patern, 0, NULL, NULL);
		cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem3, CL_TRUE, 0, sizeof(int) * e->mem_opencl_bud, e->buff_patern, 0, NULL, NULL);
	}
	cl_check_err(cl->err, "clEnqueueWriteBuffer");
	cl->err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), (void *)&(cl->mem));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 1, sizeof(t_tool), &(e->tool));
	cl_check_err(cl->err, "clSetKernelArg");
	cl->err = clSetKernelArg(cl->kernel, 2, sizeof(int), &(e->clock));
	cl_check_err(cl->err, "clSetKernelArg");
	if (e->num)
	{
		cl->err = clSetKernelArg(cl->kernel, 3, sizeof(int), &(e->num));
		cl_check_err(cl->err, "clSetKernelArg");
		cl->err = clSetKernelArg(cl->kernel, 4, sizeof(float), &(e->jul_y));
		cl_check_err(cl->err, "clSetKernelArg");
		cl->err = clSetKernelArg(cl->kernel, 5, sizeof(float), &(e->jul_x));
		cl_check_err(cl->err, "clSetKernelArg");
	}
	else
	{
		cl->err = clSetKernelArg(cl->kernel, 3, sizeof(t_bud), &(e->bud));
		cl_check_err(cl->err, "clSetKernelArg");
		cl->err = clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), (void *)&(cl->mem2));
		cl_check_err(cl->err, "clSetKernelArg");
		cl->err = clSetKernelArg(cl->kernel, 5, sizeof(cl_mem), (void *)&(cl->mem3));
		cl_check_err(cl->err, "clSetKernelArg");
	}
}

static void	cl_run_kernel(t_env *e, t_cl *cl)
{
	cl_event event;
	if (e->num)
		e->cl.global_item_size = WIDTH * HEIGHT;
	else
		e->cl.global_item_size = e->width_bud * e->height_bud;
	cl->err = clGetKernelWorkGroupInfo(cl->kernel, cl->device_id,
			CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &e->cl.local_item_size, NULL);
	cl_check_err(cl->err, "clGetKernelWorkGroupInfo");
	if (e->cl.global_item_size % cl->local_item_size)
	{
//		ft_printf("Aie\n");
		exit(0);
	}
	cl_check_err(e->cl.err, "clGetKernelWorkGroup");
//	ft_printf("Start Kernel execution\n");
	cl->err = clEnqueueNDRangeKernel(cl->cq, cl->kernel, 1, NULL,
			&cl->global_item_size, &cl->local_item_size, 0, NULL, &event);
	cl_check_err(cl->err, "clEnqueueNDRangeKernel");
	clWaitForEvents(1, &event);
	cl->err = clFlush(cl->cq);
	cl_check_err(cl->err, "clFlush");
//	ft_printf("End Kernel execution\n");
}

static void	cl_stock_in_buff(t_env *e, char *dest, int *src, int add)
{
	int i;

	i = 0;
	while (i < e->mem_opencl_bud)
	{
		dest[i * 4 + add] = src[i];
		i++;
	}
}

int			cl_draw(t_env *e)
{
	time_t t1, t2;
	t_cl	*cl;
	cl_event event;

	t1 = time(NULL);
	cl = &(e->cl);

	cl_set_arg(e, &(e->cl));
	cl_run_kernel(e, &(e->cl));
	if (e->num)
	{
		cl->err = clEnqueueReadBuffer(cl->cq, cl->mem, CL_TRUE, 0,
				MEM_OPENCL * sizeof(char), e->img->data, 0, NULL, &event);
		clWaitForEvents(1, &event);
		cl_check_err(cl->err, "clEnqueueReadBuffer");
	}
	else
	{
		cl->err = clEnqueueReadBuffer(cl->cq, cl->mem, CL_TRUE, 0,
				e->mem_opencl_bud * sizeof(int), e->buff_patern, 0, NULL, &event);
		clWaitForEvents(1, &event);
		cl_stock_in_buff(e, e->ftab, e->buff_patern, 0);
		cl->err = clEnqueueReadBuffer(cl->cq, cl->mem2, CL_TRUE, 0,
				e->mem_opencl_bud * sizeof(int), e->buff_patern, 0, NULL, &event);
		cl_stock_in_buff(e, e->ftab, e->buff_patern, 1);
		cl->err = clEnqueueReadBuffer(cl->cq, cl->mem3, CL_TRUE, 0,
				e->mem_opencl_bud * sizeof(int), e->buff_patern, 0, NULL, &event);
		cl_stock_in_buff(e, e->ftab, e->buff_patern, 2);
		cl_check_err(cl->err, "clEnqueueReadBuffer");
		clFinish(cl->cq);
		if (!e->num)
			buddhabrot_color(e, e->ftab);
		if (!e->num)
			over_sampling_resize(e, e->ftab);
	}
	t2 = time(NULL);
	int sec;
	sec = (t2 - t1) % 60;
	int min;
	min = (t2 - t1) / 60;
	ft_printf("\033[32mTemps : %i:%i\n\033[0m", min, sec);
	return (1);
}
