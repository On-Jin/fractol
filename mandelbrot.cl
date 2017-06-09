
#define X1 -2.1
#define Y1 -1.2
#define WIDTH 1920
#define HEIGHT 1080

typedef struct	s_res
{
	int		ret_iter[WIDTH * HEIGHT];
}				t_res;

//ajout e->move && e->ajj

__kernel void	mandelbrot(
__global char *out,
float zoom,
int iter)
{
	int		recup = get_global_id(0);
	int		x = recup % WIDTH;
	int		y = recup / WIDTH;
	float	c_r = 0;
	float	c_i = 0;
	float	z_r = 0;
	float	z_i = 0;
	float	tmp;
	int		i;

	i = 0;
	c_r = (x) / zoom + X1;
	c_i = (y) / zoom + Y1;
/*
	while (z_r * z_r + z_i * z_i < 4 && i < 50)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * z_i * tmp + c_i;
		i++;
	}
*/
	out[recup] = i;
}
