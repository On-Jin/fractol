/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_end_opencl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:05:49 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/19 05:44:05 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		cl_end_opencl(t_env *e, t_cl *cl)
{
	(void)e;
	if (cl->kernel)
		cl->err = clReleaseKernel(cl->kernel);
	cl_check_err(cl->err, "clReleaseKernel");
	if (cl->program)
		cl->err = clReleaseProgram(cl->program);
	cl_check_err(cl->err, "clReleaseProgram");
	if (cl->mem)
		cl->err = clReleaseMemObject(cl->mem);
	cl_check_err(cl->err, "clReleaseMemObject");
	if (cl->cq)
		cl->err = clReleaseCommandQueue(cl->cq);
	cl_check_err(cl->err, "clReleaseCommandQueue");
	if (cl->context)
		cl->err = clReleaseContext(cl->context);
	cl_check_err(cl->err, "clReleaseContext");
}
