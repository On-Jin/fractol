
#include "fractol.hl"

#pragma OPENCL EXTENSION cl_khr_printf : enable
#pragma OPENCL EXTENSION cl_khr_double : enable

V_PRECI	ft_pow(V_PRECI nb, int pow)
{
	int	p;
	V_PRECI	result;

	p = 1;
	result = 1;
	if (pow < 0)
    	return (0);
	if (pow == 0)
    	return (1);
	while (p <= pow)
	{
    	result = result * nb;
    	p = p + 1;
    }
	return (result);
}

V_PRECI		ft_abs(V_PRECI a)
{
	if (a < 0)
		return (a*-1);
	return (a);
}

void		init_color_value(t_tool *tool, t_color *c, int clock)
{
	if (tool->color == 0 || tool->color == 2)
	{
		c->h = clock;
		c->s = 0.8;
		c->v = 0.8;
	}
	else if (tool->color == 1)
	{
		c->h = clock;
		c->s = 0.8;
		c->v = 0.2;
	}
	else if (tool->color == 3)
	{
		c->s = 0;
		c->h = 0;
		c->v = 0.9 / 360 * clock;
	}
}

void		set_color_value(t_tool *tool, t_color *hsv, t_px *px, int i, int clock)
{
		if (tool->color == 2 || tool->color == 1)
		{
			hsv->s = hsv->s + (0.2 / tool->iter) * i;
			hsv->v = hsv->v + (0.8 / tool->iter) * i;
			hsv->h += (360 / (float)tool->iter) * i;
			if (hsv->h > 360)
			{
				hsv->h -= 360;
			}
			mlxji_hsv_to_rgb(px, hsv->h, hsv->s, hsv->v);
		}
		else if (tool->color == 0)
		{
			hsv->h += (360 / (float)tool->iter) * i;
			if (hsv->h > 360)
			{
				hsv->h -= 360;
			}
			mlxji_hsv_to_rgb(px, hsv->h, hsv->s, hsv->v);
		}
		else if (tool->color == 3)
		{
			hsv->v += (0.9 / (float)tool->iter) * (float)i;
			if (hsv->v > 0.9)
				hsv->v -= 0.9;
			mlxji_hsv_to_rgb(px, hsv->h, hsv->s, hsv->v);
		}
}

__kernel void	mandelbrot(
__global char *out,
t_tool tool,
int clock,
int	num,
float jul_y,
float jul_x)
{
	int		recup = get_global_id(0);
	if (recup < 0 || recup >= WIDTH * HEIGHT)
		return ;
	int		x = recup % WIDTH;
	int		y = recup / WIDTH;
	long int	d_x = x;
	long int	d_y = y;
	V_PRECI	c_r = 0;
	V_PRECI	c_i = 0;
	V_PRECI	z_r = 0;
	V_PRECI	z_i = 0;
	V_PRECI	tmp;
	int		i;
	t_px	px;
	t_color	hsv;
	V_PRECI ret;
	V_PRECI res;

	init_color_value(&tool, &hsv, clock);
	i = 0;
	c_r = (((V_PRECI)d_x + tool.move_x) / ((V_PRECI)HEIGHT * 1.125)) *
		((V_PRECI)tool.xmax - (V_PRECI)tool.xmin) + tool.xmin;
	c_i = (((V_PRECI)d_y + tool.move_y) / (V_PRECI)HEIGHT) *
		((V_PRECI)tool.ymax - (V_PRECI)tool.ymin) + tool.ymin;
	if (num == 1)
	{
		while ((res = z_r * z_r + z_i * z_i) < 4 && i < tool.iter)
		{
			if (tool.mode == 1)
			{
				if (ret == res)
						break ;
					ret = res;
			}
			tmp = z_r;
			z_r = z_r * z_r - z_i * z_i + c_r;
			z_i = 2 * z_i * tmp + c_i;
			x;
			i++;
		}
	}
	else if (num == 5)
	{
		while ((res = z_r * z_r + z_i * z_i) < 4 && i < tool.iter)
		{
			if (tool.mode & 1)
			{
				if (ret == res)
					break ;
				ret = res;
			}
			z_r = ft_abs(ft_pow(z_r, 2)) - ft_pow(z_i, 2) + c_r;
			z_i = 2 * ft_abs(z_i * tmp) + c_i;
			tmp = z_r;
			i++;
		}
	}
	else
	{
		z_r = jul_x;
		z_i = jul_y;
		while ((res = c_r * c_r + c_i * c_i) < 4 && i < tool.iter)
		{
			if (tool.mode & 1)
			{
				if (ret == res)
					break ;
				ret = res;
			}
			tmp = c_r;
			c_r = c_r * c_r - c_i * c_i + z_r;
			c_i = 2 * c_i * tmp + z_i;
			i++;
		}
	}
	if (i != tool.iter)
	{
		set_color_value(&tool, &hsv, &px, i, clock);
		out[x * OPP + y * (WIDTH * 4)] = px.b;
		out[x * OPP + y * (WIDTH * 4) + 1] = px.g;
		out[x * OPP + y * (WIDTH * 4) + 2] = px.r;
	}
	else
	{
		out[x * OPP + y * (WIDTH * 4)] = 0;
		out[x * OPP + y * (WIDTH * 4) + 1] = 0;
		out[x * OPP + y * (WIDTH * 4) + 2] = 0;
	}
}
