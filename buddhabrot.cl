
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
	int			height_bud = WIDTH * tab[bud.over];
	int			width_bud = HEIGHT * tab[bud.over];
	int		recup = get_global_id(0);
	if (recup < 0 || recup >= width_bud * height_bud)
		return ;
	int			x = recup % width_bud;
	int			y = recup / width_bud;
	long int	d_x = x + tool.move_x;
	long int	d_y = y + tool.move_y;
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

	c_r = (((V_PRECI)d_x) / ((V_PRECI)HEIGHT * 1.125)) *
				((V_PRECI)tool.xmax - (V_PRECI)tool.xmin) + tool.xmin;
	c_i = (((V_PRECI)d_y) / (V_PRECI)HEIGHT) *
				((V_PRECI)tool.ymax - (V_PRECI)tool.ymin) + tool.ymin;
	
	i = cl_is_ok(c_r, c_i, tool.iter);

	if (i != tool.iter)
	{
		k = 0;
		z_r = 0;
		z_i = 0;
		while (k < i)
		{
			tmp = z_r;
			z_r = z_r * z_r - z_i * z_i + c_r;
			z_i = 2 * z_i * tmp + c_i;
			kx = (int)(((z_r - tool.xmin) / ((V_PRECI)tool.xmax - (V_PRECI)tool.xmin)) * ((V_PRECI)HEIGHT * 1.125)) - tool.move_x;
			ky = (int)(((z_i - tool.ymin) / ((V_PRECI)tool.ymax - (V_PRECI)tool.ymin)) * ((V_PRECI)HEIGHT)) - tool.move_y;
			if (ky > 1 && ky < height_bud - 1 &&
					kx > 1 && kx < width_bud - 1)
			{
				if (atomic_max(&(out[(kx * OPP) + (ky * width_bud) + 0]), 0) < 254)
				{
					ptr = (&(out[((kx) + (ky * width_bud) + 0)]));
					atomic_inc(ptr);
				}
//				if (out2[(kx * OPP) + (ky * width_bud) + 1] < 254)
//				{
//					ptr = (&(out2[((kx) + (ky * width_bud) + 1)]));
//					atomic_inc(ptr);
//				}
//				if (out3[(kx * OPP) + (ky * width_bud) + 2] < 254)
//				{
//					ptr = (&(out3[((kx) + (ky * width_bud) + 2)]));
//					atomic_inc(ptr);
//				}
			}
			k++;
		}
	}
}
