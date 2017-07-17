/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 05:06:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/17 02:44:39 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
/*
static unsigned char	char_max(int nb)
{
//	if (nb > 254)
//		return (254);
	return (nb);
}
*/
static void				cl_run_kernel(t_env *e, t_cl *cl)
{
	cl_event event;

	event = 0;
	if (e->num)
		e->cl.global_item_size = e->width * e->height;
	else
		e->cl.global_item_size = e->width_bud * e->height_bud;
	cl->err = clGetKernelWorkGroupInfo(cl->kernel, cl->device_id,
	CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &e->cl.local_item_size, NULL);
	cl_check_err(cl->err, "clGetKernelWorkGroupInfo");
	if (e->cl.global_item_size % cl->local_item_size)
		end_of_program(e, "Global_item_size %% Local item size != 0");
	cl_check_err(e->cl.err, "clGetKernelWorkGroup");
	cl->err = clEnqueueNDRangeKernel(cl->cq, cl->kernel, 1, NULL,
			&cl->global_item_size, &cl->local_item_size, 0, NULL, &event);
	cl_check_err(cl->err, "clEnqueueNDRangeKernel");
	clWaitForEvents(1, &event);
	cl->err = clFlush(cl->cq);
	cl_check_err(cl->err, "clFlush");
}

static void				cl_stock_in_buff(t_env *e, int *dest,
												int *src, int add)
{
	int i;

	i = 0;
	while (i < e->mem_opencl)
	{
		dest[i * 4 + add] = src[i];
		i++;
	}
}

static void				cl_get_ret(t_env *e, t_cl *cl)
{
	if (e->num)
	{
		cl->err = clEnqueueReadBuffer(cl->cq, cl->mem, CL_TRUE, 0,
				e->width * e->height * 4, e->img->data, 0, NULL, NULL);
		cl_check_err(cl->err, "clEnqueueReadBuffer");
	}
	else
	{
		cl->err = clEnqueueReadBuffer(cl->cq, cl->mem, CL_TRUE, 0,
				e->mem_opencl * sizeof(int), e->buff_patern, 0, NULL, NULL);
		cl_stock_in_buff(e, e->ftab, e->buff_patern, 0);
		cl->err = clEnqueueReadBuffer(cl->cq, cl->mem2, CL_TRUE, 0,
				e->mem_opencl * sizeof(int), e->buff_patern, 0, NULL, NULL);
		cl_stock_in_buff(e, e->ftab, e->buff_patern, 1);
		cl->err = clEnqueueReadBuffer(cl->cq, cl->mem3, CL_TRUE, 0,
				e->mem_opencl * sizeof(int), e->buff_patern, 0, NULL, NULL);
		cl_stock_in_buff(e, e->ftab, e->buff_patern, 2);
		cl_check_err(cl->err, "clEnqueueReadBuffer");
		clFinish(cl->cq);
		if (!e->num)
			buddhabrot_color(e, e->ftab);
		if (!e->num)
			over_sampling_resize_buddha(e, e->ftab);
	}
}

int						cl_draw(t_env *e)
{
	time_t		t1;
	time_t		t2;
	t_cl		*cl;

	t1 = time(NULL);
	cl = &(e->cl);
	cl_set_buffer_and_arg(e, &(e->cl));
	cl_run_kernel(e, &(e->cl));
	cl_get_ret(e, &(e->cl));
	t2 = time(NULL);
	e->sec = (t2 - t1) % 60;
	e->min = (t2 - t1) / 60;
	return (1);
}
