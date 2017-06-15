/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 05:06:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/15 03:41:26 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	cl_set_arg(t_env *e, t_cl *cl)
{
	if (e->num)
		cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem, CL_TRUE, 0, sizeof(char) * MEM_OPENCL, e->img->data, 0, NULL, NULL);
	else
	{
		ft_printf("Lol\n");
		//	clEnqueueFillBuffer(cl->cq, cl->mem, );
		char *buf;
		buf = ft_memalloc(e->mem_opencl_bud);
		cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem, CL_TRUE, 0, sizeof(char) * e->mem_opencl_bud, buf, 0, NULL, NULL);
		free(buf);
		ft_printf("Lol\n");
	}
	cl_check_err(cl->err, "clEnqueueWriteBuffer");
	cl->err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), (void *)&(cl->mem));
	cl_check_err(cl->err, "clSetKernelArg");
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
	if (e->num)
	{
		cl->err = clSetKernelArg(cl->kernel, 8, sizeof(int), &(e->num));
		cl_check_err(cl->err, "clSetKernelArg");
		cl->err = clSetKernelArg(cl->kernel, 9, sizeof(float), &(e->jul_y));
		cl_check_err(cl->err, "clSetKernelArg");
		cl->err = clSetKernelArg(cl->kernel, 10, sizeof(float), &(e->jul_x));
		cl_check_err(cl->err, "clSetKernelArg");
	}
	else
	{
		cl->err = clSetKernelArg(cl->kernel, 8, sizeof(int), &(e->seuil));
		cl_check_err(cl->err, "clSetKernelArg");
		cl->err = clSetKernelArg(cl->kernel, 9, sizeof(int), &(e->over));
		cl_check_err(cl->err, "clSetKernelArg");
	}
}

static void	cl_run_kernel(t_env *e, t_cl *cl)
{
	(void)e;
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
		ft_printf("Aie\n");
		exit(0);
	}
	//cl->local_item_size = 1;
	cl_check_err(e->cl.err, "clGetKernelWorkGroup");
	cl->err = clEnqueueNDRangeKernel(cl->cq, cl->kernel, 1, NULL,
			&cl->global_item_size, &cl->local_item_size, 0, NULL, &event);
	cl_check_err(cl->err, "clEnqueueNDRangeKernel");
	clWaitForEvents(1, &event);
	cl->err = clFlush(cl->cq);
	cl_check_err(cl->err, "clFlush");
}

int			cl_draw(t_env *e)
{
	t_cl	*cl;
	char *tab;
	cl_event event;

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
		tab = ft_memalloc(e->mem_opencl_bud * sizeof(char));
		cl->err = clEnqueueReadBuffer(cl->cq, cl->mem, CL_TRUE, 0,
				e->mem_opencl_bud * sizeof(char), tab, 0, NULL, &event);
		clWaitForEvents(1, &event);
		cl_check_err(cl->err, "clEnqueueReadBuffer");
		clFinish(cl->cq);
		ft_printf("Ptr Bleu %p\nPtr Vert %p\nPtr Roug %p\n%p\n%p\n%p\n",
		(&(tab[(0)])),
		(&(tab[(1)])),
		(&(tab[(2)])),
		tab + 0,
		tab + 1,
		tab + 2);
		if (!e->num)
			buddhabrot_color(e, tab);
		if (!e->num)
			over_sampling_resize(e, tab);
		free(tab);
	}
	return (1);
}
