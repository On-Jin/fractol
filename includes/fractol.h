/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 02:18:53 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/09 02:20:48 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/includes/ft_printf.h"
# include "../libmlxji/includes/mlxji.h"
# include "mlx.h"
# include <OpenCL/opencl.h>

# define HEIGHT 1080
# define WIDTH 1920

# define MEM_OPENCL (HEIGHT * WIDTH * 4)
# define MAX_SOURCE_SIZE (900)

typedef struct	s_res
{
	int			y;
	int			x;
}				t_res;

typedef struct	s_cl
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	cq;
	cl_mem				mem;
	cl_program			program;
	cl_kernel			kernel;
	cl_platform_id		platform_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				err;
}				t_cl;

typedef struct	s_env
{
	t_cl		cl;
	void		*mlx;
	void		*win;
	t_img		*img;

	int			key[269];
	int			mouse_x;
	int			mouse_y;
	float		zoom;
	float		iter;
	int		ajj_x;
	int		ajj_y;
}				t_env;

void			init_mlx(t_env *e);

int				event_move_mouse(int x, int y, t_env *e);
int				event_mouse(int button, int x, int y, t_env *e);
int				event_key_on(int keycode, t_env *e);
int				event_key_off(int keycode, t_env *e);

void			cl_check_err(cl_int err, const char *name);
void			cl_end_opencl(t_env *e, t_cl *cl);
int				cl_init_opencl(t_env *e);

int				draw(t_env *e);
int				loop(t_env *e);

void			end_of_program(t_env *e);

#endif
