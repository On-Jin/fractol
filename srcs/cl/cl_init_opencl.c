/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_init_opencl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 03:02:43 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/17 04:24:14 by ntoniolo         ###   ########.fr       */
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
		fd = open("./buddhabrot.cl", O_RDONLY);
	if (!fd)
	{
		ft_putstr_fd("Failed to load source.\n", 2);
		exit(0);
	}
	read(fd, k_src, MAX_SOURCE_SIZE);
	*src_size = ft_strlen(k_src);
	close(fd);
}

static void		cl_create_buffer(t_env *e, t_cl *cl)
{
	if (e->num)
	{
		cl->mem = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
				e->width * e->height * 4 * sizeof(char), NULL, &(cl->err));
		cl_check_err(cl->err, "clCreateBuffer");
	}
	else
	{
		cl->mem = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
				(e->mem_opencl) * sizeof(int), NULL, &(cl->err));
		cl_check_err(cl->err, "clCreateBuffer");
		cl->mem2 = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
				(e->mem_opencl) * sizeof(int), NULL, &(cl->err));
		cl_check_err(cl->err, "clCreateBuffer");
		cl->mem3 = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
				(e->mem_opencl) * sizeof(int), NULL, &(cl->err));
		cl_check_err(cl->err, "clCreateBuffer");
	}
}

static void		cl_create_base(t_env *e, t_cl *cl)
{
	char	*k_src;
	size_t	src_size;

	k_src = (char*)ft_memalloc(MAX_SOURCE_SIZE);
	cl->err = clGetPlatformIDs(1, &(cl->platform_id), &(cl->ret_num_platforms));
	cl_check_err(cl->err, "clGetPlatformIDs");
	cl->err = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_GPU,
			1, &(cl->device_id), &(cl->ret_num_devices));
	cl_check_err(cl->err, "clGetDeviceIDs");
	cl->context = clCreateContext(NULL, 1,
								&(cl->device_id), NULL, NULL, &(cl->err));
	cl_check_err(cl->err, "clCreateContext");
	cl->cq = clCreateCommandQueue(cl->context,
								cl->device_id, 0, &(cl->err));
	cl_check_err(cl->err, "clCreateCommandQueue");
	cl_load_src(e, k_src, &src_size);
	cl_create_buffer(e, cl);
	cl->program = clCreateProgramWithSource(cl->context,
										1, (const char **)&k_src,
			(const size_t *)&src_size, &(cl->err));
	cl_check_err(cl->err, "clCreateProgramWithSource");
	ft_strdel(&k_src);
}

static void		cl_compile_kernel(t_env *e, t_cl *cl)
{
	char		buffer[10000];
	size_t		len;

	(void)e;
	cl->err = clBuildProgram(cl->program, 0, NULL, "-I.", NULL, NULL);
	if (cl->err != CL_SUCCESS)
	{
		ft_bzero(buffer, 10000);
		cl->err = clGetProgramBuildInfo(cl->program, cl->device_id,
				CL_PROGRAM_BUILD_LOG, 10000, buffer, &len);
		if (cl->err == CL_SUCCESS)
			ft_printf("\033[31mCompiler error message :\033[0m\n", buffer);
		else
			ft_printf("Erreur étonnate\n");
		end_of_program(e, buffer);
	}
}

int				cl_init_opencl(t_env *e)
{
	t_cl *cl;

	cl = &e->cl;
	cl_create_base(e, &e->cl);
	cl_compile_kernel(e, &e->cl);
	if (e->num)
		e->cl.kernel = clCreateKernel(e->cl.program,
												"mandelbrot", &(e->cl.err));
	else
		e->cl.kernel = clCreateKernel(e->cl.program,
												"buddhabrot", &(e->cl.err));
	cl_check_err(e->cl.err, "clCreateKernel");
	if (e->num)
		e->cl.global_item_size = e->width * e->height;
	else
		e->cl.global_item_size = e->width_bud * e->height_bud;
	cl->err = clGetKernelWorkGroupInfo(cl->kernel, cl->device_id,
						CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t),
									&e->cl.local_item_size, NULL);
	cl_check_err(e->cl.err, "clGetKernelWorkGroup");
	return (1);
}
