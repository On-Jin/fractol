
#include "fractol.hl"

#pragma OPENCL EXTENSION cl_khr_double : enable
#pragma OPENCL EXTENSION cl_khr_global_int64_base_atomics : enable
#pragma OPENCL EXTENSION cl_khr_printf : enable
#pragma OPENCL EXTENSION cl_intel_printf : enable
#pragma OPENCL EXTENSION cl_khr_int64_base_atomics : enable

int				cl_is_ok(V_PRECI c_r, V_PRECI c_i, long int zoom, long int iter)
{
	V_PRECI tmp;
	V_PRECI z_r = 0;
	V_PRECI z_i = 0;
	int i;

	i = 0;
//	barrier(CLK_GLOBAL_MEM_FENCE);	
	while (z_r * z_r + z_i * z_i < 4 && i < iter)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * z_i * tmp + c_i;
		i++;
//		barrier(CLK_GLOBAL_MEM_FENCE);	
	}
//	barrier(CLK_GLOBAL_MEM_FENCE);	
	return (i);
}

__kernel void	buddhabrot(
		__global volatile int *out,
		t_tool tool,
		int clock,
		t_bud bud,
		__global volatile int *out2,
		__global volatile int *out3)
{
	int tab[6] = {0, 1, 2, 4, 8, 16};
	int			width_bud = WIDTH * tab[bud.over];
	int			height_bud = HEIGHT * tab[bud.over];
	int		recup = get_global_id(0);
	if (recup < 0 || recup >= width_bud * height_bud)
		return ;
	int			x = recup % width_bud;
	int			y = recup / width_bud;
	long int	d_x = x + (V_PRECI)tool.ajj_x + tool.move_x;
//	printf("D_x = %f + %i\n", tool.ajj_x, tool.move_x);
	long int	d_y = y + (V_PRECI)tool.ajj_y + tool.move_y;
//	printf("D_y = %f + %i\n", tool.ajj_y, tool.move_y);
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

	c_r = (d_x) / (V_PRECI)tool.zoom + X1;
//	printf("c_r = %i / %.2f + %i\n", d_x, tool.zoom + X1);
	c_i = (d_y) / (V_PRECI)tool.zoom + Y1;
//	printf("c_r = %i / %.2f + %i\n", d_y, tool.zoom + Y1);
	
	i = cl_is_ok((d_x) / (V_PRECI)tool.zoom + X1,
				(d_y) / (V_PRECI)tool.zoom + Y1,
				tool.zoom, tool.iter);

	//barrier(CLK_GLOBAL_MEM_FENCE);
	
	if (i != tool.iter)
	{
		k = 0;
		z_r = 0;
		z_i = 0;
		c_r = (d_x) / (V_PRECI)tool.zoom + X1;
		c_i = (d_y) / (V_PRECI)tool.zoom + Y1;
		while (k < i)
		{
			tmp = z_r;
			z_r = z_r * z_r - z_i * z_i + c_r;
			z_i = 2 * z_i * tmp + c_i;
			ky = (int)((z_i - Y1) * (V_PRECI)tool.zoom - (V_PRECI)tool.ajj_y - tool.move_y);
			kx = (int)((z_r - X1) * (V_PRECI)tool.zoom - (V_PRECI)tool.ajj_x - tool.move_x);
			if (ky > 0 && ky < height_bud &&
					kx > 0 && kx < width_bud)
			{
				if (k < 2000 &&out[(kx * OPP) + (ky * width_bud) + 0] < 254)
				{
					ptr = (&(out[((kx) + (ky * width_bud) + 0)]));
					atomic_inc(ptr);
				}
				if (k < 20000 && out2[(kx * OPP) + (ky * width_bud) + 1] < 254)
				{
					ptr = (&(out2[((kx) + (ky * width_bud) + 1)]));
					atomic_inc(ptr);
				}
				if (k < 200000 && out3[(kx * OPP) + (ky * width_bud) + 2] < 254)
				{
					ptr = (&(out3[((kx) + (ky * width_bud) + 2)]));
					atomic_inc(ptr);
				}
			}
	//		barrier(CLK_GLOBAL_MEM_FENCE);
			k++;
		}
	}
	//barrier(CLK_GLOBAL_MEM_FENCE);
}
