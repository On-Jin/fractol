/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_end_opencl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:05:49 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/08 17:42:15 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		cl_end_opencl(t_env *e, t_cl *cl)
{
	(void)e;
	cl->err = clFlush(cl->cq);
	cl_check_err(cl->err, "clFlush");
	cl->err = clReleaseKernel(cl->kernel);
	cl_check_err(cl->err, "clReleaseKernel");
	cl->err = clReleaseProgram(cl->program);
	cl_check_err(cl->err, "clReleaseProgram");
	cl->err = clReleaseMemObject(cl->mem);
	cl_check_err(cl->err, "clReleaseMemObject");
	cl->err = clReleaseCommandQueue(cl->cq);
	cl_check_err(cl->err, "clReleaseCommandQueue");
	cl->err = clReleaseContext(cl->context);
	cl_check_err(cl->err, "clReleaseContext");
}
