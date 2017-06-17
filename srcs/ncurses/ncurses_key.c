/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 07:12:56 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/17 09:03:23 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ncurses_key_putnbr(t_nc *nc, int ret)
{
	(void)nc;(void)ret;
//	if (ret == NC_PUT_NBR)
//		mvwscanw(nc->inf, 50, 2, "%i", &nc->wall_cycle);
}

static void	ncurses_key_move(t_env *e, t_nc *nc, int ret)
{
	(void)e;
	if (ret == KEY_DOWN)
	{
		if (!nc->menu_bud && nc->cursor < NB_FRACTAL - 1)
			nc->cursor++;
		else if (nc->menu_bud && nc->cursor < NB_PRESET_BUD - 1)
			nc->cursor++;
	}
	else if (ret == KEY_UP && nc->cursor > 0)
		nc->cursor--;
}

void		ncurses_key(t_env *e, t_nc *nc)
{
	int		ret;

	(void)e;
	timeout(1);
	ret = getch();
	if (ret > 'A' && ret < 'z')
		nc->key = ret;
	ncurses_key_putnbr(nc, ret);
	ncurses_key_move(e, nc, ret);
	if (ret == KEY_RIGHT)
	{
		if (nc->menu_bud)
			ncurses_parsing(e, nc);
		if (!nc->menu_bud)
			e->num = nc->cursor;
		if (e->num)
			nc->menu = 1;
		else
			nc->menu_bud = 1;
	}
	else if (ret == KEY_LEFT)
	{
		nc->menu = 0;
		nc->menu_bud = 0;
		nc->cursor = 0;
	}
}
