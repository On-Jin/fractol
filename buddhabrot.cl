
#include "fractol.hl"

#pragma OPENCL EXTENSION cl_khr_double : enable
#pragma OPENCL EXTENSION cl_khr_global_int64_base_atomics : enable
#pragma OPENCL EXTENSION cl_khr_printf : enable
#pragma OPENCL EXTENSION cl_intel_printf : enable
#pragma OPENCL EXTENSION cl_khr_int64_base_atomics : enable

int				cl_is_ok(V_PRECI c_r, V_PRECI c_i, long int iter)
{
	V_PRECI tmp;
	V_PRECI z_r = 0;
	V_PRECI z_i = 0;
	int i;

	i = 0;
	while (z_r * z_r + z_i * z_i < 4 && i < iter)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * z_i * tmp + c_i;
		i++;
	}
	return (i);
}

__kernel void	buddhabrot(
		volatile __global int *out,
		volatile __global int *out2,
		volatile __global int *out3,
		t_tool tool,
		int clock,
		t_bud bud)
{
	int tab[6] = {0, 1, 2, 4, 8, 16};
	int			width_bud = WIDTH * tab[bud.over];
	int			height_bud = HEIGHT * tab[bud.over];
	int		recup = get_global_id(0);
	if (recup < 0 || recup >= width_bud * height_bud)
		return ;
	int			x = recup % width_bud;
	int			y = recup / width_bud;
	long int	d_x = x;
	long int	d_y = y;
	V_PRECI		c_r = 0;
	V_PRECI		c_i = 0;
	V_PRECI		z_r = 0;
	V_PRECI		z_i = 0;
	V_PRECI		tmp;
	int			i;
	int		kx, ky;
	int			k;
	volatile __global int *ptr;
	i = 0;

	c_r = (((V_PRECI)d_x) / ((V_PRECI)height_bud * 1.125)) *
				((V_PRECI)tool.xmax - (V_PRECI)tool.xmin) + tool.xmin;
	c_i = (((V_PRECI)d_y) / (V_PRECI)height_bud) *
				((V_PRECI)tool.ymax - (V_PRECI)tool.ymin) + tool.ymin;
	
	i = cl_is_ok(c_r, c_i, tool.iter);

	if (i < tool.iter)
	{
		k = 0;
		z_r = 0;
		z_i = 0;
		while (k < i)
		{
			tmp = z_r;
			z_r = z_r * z_r - z_i * z_i + c_r;
			z_i = 2 * z_i * tmp + c_i;
			kx = (int)(((z_r - tool.xmin) / (((V_PRECI)tool.xmax - (V_PRECI)tool.xmin)) * ((V_PRECI)height_bud * 1.125)));
			ky = (int)(((z_i - tool.ymin) / (((V_PRECI)tool.ymax - (V_PRECI)tool.ymin)) * ((V_PRECI)height_bud)));
			if (ky > 1 && ky < height_bud - 1 &&
					kx > 1 && kx < width_bud - 1)
			{
				if (k > bud.min[0] && k < bud.max[0])
				{
					ptr = (&(out[((kx) + (ky * width_bud) + 0)]));
					atomic_inc(ptr);
				}
				if (k > bud.min[1] && k < bud.max[1])
				{
					ptr = (&(out2[((kx) + (ky * width_bud) + 1)]));
					atomic_inc(ptr);
				}
				if (k > bud.min[2] && k < bud.max[2])
				{
					ptr = (&(out3[((kx) + (ky * width_bud) + 2)]));
					atomic_inc(ptr);
				}
			}
			k++;
		}
	}
}
