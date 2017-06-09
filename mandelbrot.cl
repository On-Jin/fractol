
#define X1 -2.1
#define Y1 -1.2
#define WIDTH 1920
#define HEIGHT 1080
#define OPP 4

typedef struct	s_res
{
	int		ret_iter[WIDTH * HEIGHT];
}				t_res;

__kernel void	mandelbrot(
__global char *out,
float zoom,
int iter,
float ajj_y,
float ajj_x,
int move_y,
int move_x)
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
		out[x * OPP + y * (WIDTH * 4)] = i * 255 / iter;
}
