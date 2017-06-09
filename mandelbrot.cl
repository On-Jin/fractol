
#include "fractol.hl"

__kernel void	mandelbrot(
__global char *out,
float zoom,
float iter,
float ajj_y,
float ajj_x,
int move_y,
int move_x,
int clock)
{
	int		recup = get_global_id(0);
	int		x = recup % WIDTH;
	int		y = recup / WIDTH;
	int		d_x = x + ajj_x + move_x;
	int		d_y = y + ajj_y + move_y;
	float	c_r = 0;
	float	c_i = 0;
	float	z_r = 0;
	float	z_i = 0;
	float	tmp;
	int		i;
	t_px	px;
	float	h = clock;
	float	s = 0.7;
	float	v = 0.7;

	i = 0;
	c_r = (d_x) / zoom + X1;
	c_i = (d_y) / zoom + Y1;

	while (z_r * z_r + z_i * z_i < 4 && i < iter)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * z_i * tmp + c_i;
		i++;
	}
	if (i != iter)
	{
		h += (360 / iter) * i;
		if (h > 360)
		{
			h -= 360;
		}
//		s = s + (0.30 / iter) * i;
//		v = v + (0.10 / iter) * i;
		mlxji_hsv_to_rgb(&px, h, s, v);
//		px.r = (255 / iter) * i;
//		px.r = 0;
//		px.g = 0;
//		px.b = 0;
		out[x * OPP + y * (WIDTH * 4)] = px.b;
		out[x * OPP + y * (WIDTH * 4) + 1] = px.g;
		out[x * OPP + y * (WIDTH * 4) + 2] = px.r;
	}
}
/*
HSV baic
g = 0;
b = 0;
*/
