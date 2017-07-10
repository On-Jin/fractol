/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_menu_bud.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 08:03:27 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/10 21:55:44 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ncurses_print_set(t_env *e, t_nc *nc)
{
	int i;

	(void)e;
	i = 0;
	while (i < NB_PRESET_BUD)
	{
		if (nc->cursor == i)
			wattron(nc->win, WA_REVERSE);
		mvwprintw(nc->win, 9 + i, 16 + 9, "%s", "Lolilol");
		if (nc->cursor == i)
			wattroff(nc->win, WA_REVERSE);
		i++;
	}
}

void		ncurses_menu_bud(t_env *e, t_nc *nc)
{
	wattron(nc->win, COLOR_PAIR(e->num));
	mvwprintw(nc->win, 9, 13, "---------->");
	wattroff(nc->win, COLOR_PAIR(e->num));
	ncurses_print_set(e, nc);
}
