
#include "fractol.hl"

#pragma OPENCL EXTENSION cl_khr_printf : enable
#pragma OPENCL EXTENSION cl_khr_double : enable

//# define width_bud (1920 * 8)
//# define height_bud (1080 * 8)


__kernel void	buddhabrot(
		__global char *out,
		long int zoom,
		long int  iter,
		V_PRECI ajj_y,
		V_PRECI ajj_x,
		int move_y,
		int move_x,
		int clock,
		int seuil,
		int over)
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

	i = 0;
	c_r = (d_x) / (V_PRECI)zoom + X1;
	c_i = (d_y) / (V_PRECI)zoom + Y1;
	while (z_r * z_r + z_i * z_i < 4 && i < iter)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * z_i * tmp + c_i;
//		ky = (z_i - Y1) * (V_PRECI)zoom - (V_PRECI)ajj_y - move_y;
//		kx = (z_r - X1) * (V_PRECI)zoom - (V_PRECI)ajj_x - move_x;
		i++;
	}
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
				if (k > seuil && k < 200 && out[(kx * OPP) + (ky * width_bud * 4)] < 254)
				{
					out[(kx * OPP) + (ky * width_bud * 4)]++;
//					out[(kx * OPP) + (ky * width_bud * 4) + 1]++;
//					out[(kx * OPP) + (ky * width_bud * 4) + 2]++;
				}
				if (k > seuil && k < 2000 && out[(kx * OPP) + (ky * width_bud * 4)] < 254)
				{
					out[(kx * OPP) + (ky * width_bud * 4) + 1]++;
				}
				if (k > seuil && k < 20000 && out[(kx * OPP) + (ky * width_bud * 4)] < 254)
				{
					out[(kx * OPP) + (ky * width_bud * 4) + 2]++;
				}
			}
			k++;
		}
	}
}
/*
		while (k < i)
		{
			if (tab_y[k] > 0 && tab_y[k] < height_bud &&
					tab_x[k] > 0 && tab_x[k] < width_bud)
			{
				if (i > seuil && out[(tab_x[k] * OPP) + (tab_y[k] * width_bud * 4)] < 254)
				{
					out[(tab_x[k] * OPP) + (tab_y[k] * width_bud * 4)]++;
					out[(tab_x[k] * OPP) + (tab_y[k] * width_bud * 4) + 1]++;
					out[(tab_x[k] * OPP) + (tab_y[k] * width_bud * 4) + 2]++;
				}

//				if (i > seuil && i < 2000 && out[(tab_x[k] * OPP) + (tab_y[k] * width_bud * 4)] < 250)
//				{
//					out[(tab_x[k] * OPP) + (tab_y[k] * width_bud * 4) + 1]++;
//				}
//				if (i > seuil && i < 3000 && out[(tab_x[k] * OPP) + (tab_y[k] * width_bud * 4)] < 250)
//				{
//					out[(tab_x[k] * OPP) + (tab_y[k] * width_bud * 4) + 2]++;
//				}
			}
			k++;
		}
*/
