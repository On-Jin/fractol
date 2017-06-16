/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 02:18:53 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/16 07:41:11 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/includes/ft_printf.h"
# include "../libmlxji/includes/mlxji.h"
# include "mlx.h"
# include <OpenCL/opencl.h>
# include <sys/time.h>

#if defined(MODE_GPU)
	# define HEIGHT 1080
	# define WIDTH 1920
	# define GPU 1
#else
	# define HEIGHT 600
	# define WIDTH 1000
	# define GPU 0
#endif

//# define HEIGHT_BUD (1080 * 8)
//# define WIDTH_BUD (1920 * 8)
//# define MEM_OPENCL_BUD (HEIGHT_BUD * WIDTH_BUD * 4)

#if defined(MODE_PRECI)
	#define M_PRECI 1
	#define V_PRECI double
#else
	#define M_PRECI 0
	#define V_PRECI float
#endif

# define NUM_BUDD 0
# define NUM_MANDEL 1
# define NUM_JULIA 2

# define MEM_OPENCL (HEIGHT * WIDTH * 4)
# define MAX_SOURCE_SIZE (11000)
# define OPP 4

# define X1_MAN -2.1
# define Y1_MAN -1.2

typedef struct	s_cl
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	cq;
	cl_mem				mem;
	cl_mem				mem2;
	cl_mem				mem3;
	cl_program			program;
	cl_kernel			kernel;
	cl_platform_id		platform_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				err;
	size_t				global_item_size;
	size_t				local_item_size;
}				t_cl;

typedef struct	s_bud
{
	int			over;
	int			anti;
	float		gain;
	int			min[3];
	int			max[3];
}				t_bud;

typedef struct	s_tool
{
	long int	zoom;
	long int	iter;
	V_PRECI		ajj_x;
	V_PRECI		ajj_y;
	int			move_x;
	int			move_y;
}				t_tool;

typedef struct	s_kit
{
	V_PRECI c_r;
	V_PRECI c_i;
	V_PRECI z_r;
	V_PRECI z_i;
	V_PRECI tmp;
	int		i;
}				t_kit;

typedef struct	s_env
{
	t_cl		cl;
	void		*mlx;
	void		*win;
	t_img		*img;

	t_tool		tool;
	t_bud		bud;

	struct		timeval step;
	struct		timeval cur;
	int			fps;

	char		*ftab;
	int	*buff_patern;

	int			turn;

	int			varover[6];
	int			width_bud;
	int			height_bud;
	int			mem_opencl_bud;

	int			num;
	char		open_var_jul;
	float		jul_y;
	float		jul_x;

	int			key[269];
	int			dir_clock;
	int			clock;

	int			mouse_x;
	int			mouse_y;
}				t_env;

void			init_mlx(t_env *e);

int				event_move_mouse(int x, int y, t_env *e);
int				event_mouse(int button, int x, int y, t_env *e);
int				event_key_on(int keycode, t_env *e);
int				event_key_off(int keycode, t_env *e);

int				menu(t_env *e);

void			over_sampling_resize(t_env *e, char *tab);

void			cl_check_err(cl_int err, const char *name);
void			cl_end_opencl(t_env *e, t_cl *cl);
int				cl_init_opencl(t_env *e);

void			buddhabrot_color(t_env *e, char *tab);

int				cl_draw(t_env *e);

int				draw(t_env *e);
int				loop(t_env *e);

void			end_of_program(t_env *e);

#endif
