
#include "fractol.hl"

#pragma OPENCL EXTENSION cl_khr_double : enable
#pragma OPENCL EXTENSION cl_khr_int64_base_atomics : enable
#pragma OPENCL EXTENSION cl_khr_global_int64_base_atomics : enable
#pragma OPENCL EXTENSION cl_khr_printf : enable
#pragma OPENCL EXTENSION cl_intel_printf : enable

__kernel void	buddhabrot(
		__global volatile int *out,
		long int zoom,
		long int  iter,
		V_PRECI ajj_y,
		V_PRECI ajj_x,
		int move_y,
		int move_x,
		int clock,
		int seuil,
		int over,
		__global volatile int *out2,
		__global volatile int *out3)
{
	int tab[5] = {0, 1, 2, 4, 8};
	int			width_bud = WIDTH * tab[over];
	int			height_bud = HEIGHT * tab[over];
	int		recup = get_global_id(0);
	if (recup < 0 || recup >= width_bud * height_bud)
		return ;
	int			x = recup % width_bud;
	int			y = recup / width_bud;
	long int	d_x = x + (V_PRECI)ajj_x + move_x;
	long int	d_y = y + (V_PRECI)ajj_y + move_y;
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

	c_r = (d_x) / (V_PRECI)zoom + X1;
	c_i = (d_y) / (V_PRECI)zoom + Y1;
	while (z_r * z_r + z_i * z_i < 4 && i < iter)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * z_i * tmp + c_i;
		i++;
		barrier(CLK_GLOBAL_MEM_FENCE);
	}
	barrier(CLK_GLOBAL_MEM_FENCE);
	if (i != iter)
	{
		k = 0;
		z_r = 0;
		z_i = 0;
		c_r = (d_x) / (V_PRECI)zoom + X1;
		c_i = (d_y) / (V_PRECI)zoom + Y1;
		while (k < i)
		{
			tmp = z_r;
			z_r = z_r * z_r - z_i * z_i + c_r;
			z_i = 2 * z_i * tmp + c_i;
			ky = (int)((z_i - Y1) * (V_PRECI)zoom - (V_PRECI)ajj_y - move_y);
			kx = (int)((z_r - X1) * (V_PRECI)zoom - (V_PRECI)ajj_x - move_x);
			if (ky > 0 && ky < height_bud &&
					kx > 0 && kx < width_bud)
			{
				if (out[(kx * OPP) + (ky * width_bud) + 0] < 254)
				{
					ptr = (&(out[((kx) + (ky * width_bud) + 0)]));
					atom_inc(ptr);
				}
				if (out2[(kx * OPP) + (ky * width_bud) + 1] < 254)
				{
					ptr = (&(out2[((kx) + (ky * width_bud) + 1)]));
					atom_inc(ptr);
				}
				if (out3[(kx * OPP) + (ky * width_bud) + 2] < 254)
				{
					ptr = (&(out3[((kx) + (ky * width_bud) + 2)]));
					atom_inc(ptr);
				}
			}
			barrier(CLK_GLOBAL_MEM_FENCE);
			k++;
		}
	}
	barrier(CLK_GLOBAL_MEM_FENCE);
}