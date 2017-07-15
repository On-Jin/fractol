/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 06:36:09 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/15 22:24:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ncurses_print_fractal(t_env *e, t_nc *nc)
{
	int i;

	i = 0;
	while (i < NB_FRACTAL)
	{
		if (nc->cursor == i && !nc->menu && !nc->menu_bud)
			wattron(nc->win, WA_REVERSE);
		wattron(nc->win, COLOR_PAIR(i));
		mvwprintw(nc->win, 9 + i, 2, "%s", e->name_fractal[i]);
		wattroff(nc->win, COLOR_PAIR(i));
		if (nc->cursor == i && !nc->menu && !nc->menu_bud)
			wattroff(nc->win, WA_REVERSE);
		i++;
	}
}

static void	ncurses_print_option(t_nc *nc, char *str, int add_y, int condi)
{
	mvwprintw(nc->win, 6 + add_y, 2, "%s", str);
	if (condi)
	{
		wattron(nc->win, COLOR_PAIR(NC_GREEN));
		mvwprintw(nc->win, 6 + add_y, 13, "ON ");
		wattroff(nc->win, COLOR_PAIR(NC_GREEN));
	}
	else
	{
		wattron(nc->win, COLOR_PAIR(NC_RED));
		mvwprintw(nc->win, 6 + add_y, 13, "OFF");
		wattroff(nc->win, COLOR_PAIR(NC_RED));
	}
	mvwprintw(nc->win, 6 + add_y, 16, "]");
}

static void	ncurses_menu_print_base(t_env *e, t_nc *nc)
{
	(void)e;
	wattron(nc->win, WA_BOLD);
	mvwprintw(nc->win, 4, NC_WIDTH / 2 - 4, "%s", "Welcome.");
	ncurses_print_option(nc, "MOD_GPU   [", 0, e->flag & F_GPU);
	ncurses_print_option(nc, "MOD_PRECI [", 1, e->flag & F_PRECISION);
	ncurses_print_fractal(e, nc);
}

void		ncurses_menu(t_env *e, t_nc *nc)
{
	(void)e;
	werase(nc->win);
	box(nc->win, 0, 0);
	ncurses_menu_print_base(e, nc);
	if (nc->menu_bud)
		ncurses_menu_bud(e, nc);
	ncurses_key(e, &e->nc);
	wrefresh(nc->win);
}
