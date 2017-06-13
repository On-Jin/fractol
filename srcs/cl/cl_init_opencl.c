/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_init_opencl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 03:02:43 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/13 04:59:15 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include <stdio.h>
#include <string.h>

static void		cl_load_src(t_env *e, char *k_src, size_t *src_size)
{
	int		fd;

	(void)e;
	*src_size = 0;
	if (e->num)
		fd = open("./mandelbrot.cl", O_RDONLY);
	else
		fd = open("./buddhabrot.c", O_RDONLY);
	if (!fd)
	{
		ft_putstr_fd("Failed to load source.\n", 2);
		exit(0);
	}
	read(fd, k_src, MAX_SOURCE_SIZE);
	*src_size = ft_strlen(k_src);
	close(fd);
}

//k_src Malloc car clCreateProgramWithSource fait surrement des modifs

static void		cl_create_base(t_env *e, t_cl *cl)
{
	(void)e;
	char	*k_src;
	size_t	src_size;

	k_src = (char*)ft_memalloc(MAX_SOURCE_SIZE);
	cl->err = clGetPlatformIDs(1, &(cl->platform_id), &(cl->ret_num_platforms));
	cl_check_err(cl->err, "clGetPlatformIDs");
	cl->err = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_GPU,
			1, &(cl->device_id), &(cl->ret_num_devices));
	cl_check_err(cl->err, "clGetDeviceIDs");

	cl->context = clCreateContext(NULL, 1, &(cl->device_id), NULL, NULL, &(cl->err));
	cl_check_err(cl->err, "clCreateContext");
	cl->cq = clCreateCommandQueue(cl->context, cl->device_id, 0, &(cl->err));
	cl_check_err(cl->err, "clCreateCommandQueue");

	cl_load_src(e, k_src, &src_size);
	cl->mem = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			MEM_OPENCL * sizeof(char), NULL, &(cl->err));
	cl_check_err(cl->err, "clCreateBuffer");

	cl->program = clCreateProgramWithSource(cl->context, 1, (const char **)&k_src,
			(const size_t *)&src_size, &(cl->err));
	cl_check_err(cl->err, "clCreateProgramWithSource");
	ft_strdel(&k_src);
}

static void		cl_compile_kernel(t_env *e, t_cl *cl)
{
	char		buffer[10000];
	size_t		len;

	(void)e;
	if (M_PRECI)
		cl->err = clBuildProgram(cl->program, 0, NULL, "-D MODE_PRECI -I.", NULL, NULL);
	else
		cl->err = clBuildProgram(cl->program, 0, NULL, "-I.", NULL, NULL);
	if (cl->err != CL_SUCCESS)
	{
		cl->err = clGetProgramBuildInfo(cl->program, cl->device_id,
				CL_PROGRAM_BUILD_LOG, 10000, buffer, &len);
		if (cl->err == CL_SUCCESS)
			ft_printf("\033[31mCompiler error message :\033[0m\n%s\n", buffer);
		else
		{
			ft_printf("Error while retrieving compiler log%;\n");
			ft_printf("Try increasing buffer size to 100 000%;\n");
		}
		exit(0);
	}
}

int		cl_init_opencl(t_env *e)
{
	cl_create_base(e, &e->cl);
	cl_compile_kernel(e, &e->cl);
	if (e->num)
		e->cl.kernel = clCreateKernel(e->cl.program, "mandelbrot", &(e->cl.err));
	else
		e->cl.kernel = clCreateKernel(e->cl.program, "buddhabrot", &(e->cl.err));
	cl_check_err(e->cl.err, "clCreateKernel");
	return (1);
}
