/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 06:48:09 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/07 16:03:45 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
/*
static void draw_case(t_env *e, t_px *px, t_pxtopx *to, int len)
{
	t_pxtopx	new;
	int			i;

	new.x1 = to->x1 - len;
	new.y1 = to->y1 - len;
	new.x2 = to->x2 - len;
	new.y2 = to->y2 - len;
	i = 0;
	while (i < len * 2)
	{
		new.x1++;
		new.x2++;
		mlxji_draw_line(e->img, px, &new);
		i++;
	}
}
*/
double	conversion_radians(double degre)
{
	return (degre / 180 * 3.1415);
}

static double loop_angle(double nb)
{
	if (nb > 360)
		nb -= 360;
	return (nb);
}

int		recur_tree(t_env *e, t_px *px, t_pxtopx to, int iter, double angle)
{
	t_px lol;
	double ret;

	lol.r = 255;
	lol.g = 0;
	lol.b = 0;
	if (iter == 0)
		return (1);
	ret = conversion_radians(angle);
	to.x2 = to.x1 - (200 / (12 - iter + 1));
	to.y2 = to.y1;
	int nx = to.x2 - to.x1;
	int ny = to.y2 - to.y1;
	to.x2 = to.x1 + (nx) * cos(ret) - (ny) * sin(ret);
	to.y2 = to.y1 + (ny) * cos(ret) + (nx) * sin(ret);
//	draw_case(e, &lol, &to, (6 / (12 - iter + 1)));
	mlxji_draw_line(e->img, &lol, &to);
//	ft_printf("Y %i->%i\nX %i->%i\n\n", to.y1, to.y2, to.x1, to.x2);
	to.x1 = to.x2;
	to.y1 = to.y2;
	recur_tree(e, px, to, iter-1, loop_angle(angle - (e->mouse_x / 10)));
	recur_tree(e, px, to, iter-1, loop_angle(angle + (e->mouse_y / 10)));
	return (1);
}

int		draw_tree(t_env *e)
{
	bzero(e->img->data, WIDTH*HEIGHT*4);
	t_pxtopx	to;
	t_px		px;
/*static int lol = 0;
static int tic = 0;

lol++;
	px.g = 0;
if (lol == 360)
{
	if (tic)
		tic = 0;
	else
		tic = 1;
	lol = 0;
}
	if (tic)
	{
		px.r = 0;
		px.b = 0;
	}
	else
	{
		px.r = 255;
		px.b = 255;
	}
*/
		px.r = 255;
		px.b = 255;
/*
	to.x1 = WIDTH / 2;				//
	to.y1 = HEIGHT - HEIGHT / 8;	//PT DE ROTATION
	to.x2 = to.x1 - 30;	//
	to.y2 = to.y1;		//LEN DE ROTATION
	int nx = to.x2 - to.x1;
	int ny = to.y2 - to.y1;//SET
	double ret = conversion_radians(lol);
	(void)nx;(void)ny;
	to.x2 = to.x1 + (nx) * cos(ret) - (ny) * sin(ret);
	to.y2 = to.y1 + (ny) * cos(ret) + (nx) * sin(ret);
*/
	to.x1 = WIDTH / 2;
	to.y1 = HEIGHT  - HEIGHT / 8;
//	to.x2 = to.x1;
//	to.y2 = to.y1 - 60;
//	draw_case(e, &px, &to, 6);
//	to.x1 = to.x2;
//	to.y1 = to.y2;
	recur_tree(e, &px, to, 12, 90);
//	recur_tree(e, &px, to, 6, 145);
	ft_printf("Finish\n");
	mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
	return (1);
}
