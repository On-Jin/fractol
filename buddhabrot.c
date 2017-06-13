
#include "fractol.hl"

#pragma OPENCL EXTENSION cl_khr_printf : enable
#pragma OPENCL EXTENSION cl_khr_double : enable

# define WIDTH_BUD (1920 * 4)
# define HEIGHT_BUD (1080 * 4)

__kernel void	buddhabrot(
		__global char *out,
		long int zoom,
		long int  iter,
		V_PRECI ajj_y,
		V_PRECI ajj_x,
		int move_y,
		int move_x,
		int clock,
		int seuil)
{
	int		recup = get_global_id(0);
	if (recup < 0 || recup >= WIDTH_BUD * HEIGHT_BUD)
		return ;
	int			x = recup % WIDTH_BUD;
	int			y = recup / WIDTH_BUD;
	long int	d_x = x + (V_PRECI)ajj_x + move_x;
	long int	d_y = y + (V_PRECI)ajj_y + move_y;
	V_PRECI		c_r = 0;
	V_PRECI		c_i = 0;
	V_PRECI		z_r = 0;
	V_PRECI		z_i = 0;
	V_PRECI		tmp;
	int			i;
	V_PRECI		kx, ky;
	t_px		px;
	float		h = clock;
	float		s = 0.7;
	float		v = 0.7;
	int			tab_x[10000];
	int			tab_y[10000];
	int			k;

	if (!(recup % 1000000))
	printf("++\n");
	i = 0;
	c_r = (d_x) / (V_PRECI)zoom + X1;
	c_i = (d_y) / (V_PRECI)zoom + Y1;
	while (z_r * z_r + z_i * z_i < 4 && i < iter)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * z_i * tmp + c_i;
		ky = (z_i - Y1) * (V_PRECI)zoom - (V_PRECI)ajj_y - move_y;
		kx = (z_r - X1) * (V_PRECI)zoom - (V_PRECI)ajj_x - move_x;
		tab_y[i] = (int)ky;
		tab_x[i] = (int)kx;
		i++;
	}
	k = 0;
	if (i != iter)
	{
		while (k < i)
		{
			if (tab_y[k] > 0 && tab_y[k] < HEIGHT_BUD &&
					tab_x[k] > 0 && tab_x[k] < WIDTH_BUD)
			{
				if (i > seuil && out[(tab_x[k] * OPP) + (tab_y[k] * WIDTH_BUD * 4)] < 254)
				{
					out[(tab_x[k] * OPP) + (tab_y[k] * WIDTH_BUD * 4)]++;
					out[(tab_x[k] * OPP) + (tab_y[k] * WIDTH_BUD * 4) + 1]++;
					out[(tab_x[k] * OPP) + (tab_y[k] * WIDTH_BUD * 4) + 2]++;
				}
/*
				if (i > seuil && i < 2000 && out[(tab_x[k] * OPP) + (tab_y[k] * WIDTH_BUD * 4)] < 250)
				{
					out[(tab_x[k] * OPP) + (tab_y[k] * WIDTH_BUD * 4) + 1]++;
				}
				if (i > seuil && i < 3000 && out[(tab_x[k] * OPP) + (tab_y[k] * WIDTH_BUD * 4)] < 250)
				{
					out[(tab_x[k] * OPP) + (tab_y[k] * WIDTH_BUD * 4) + 2]++;
				}
*/
			}
			k++;
		}
	}
}
