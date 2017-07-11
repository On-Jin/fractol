/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_print_parsing_buddhabrot.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 10:29:37 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/10 22:32:40 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ncurses_print_parsing_buddhabrot(t_env *e, t_nc *nc)
{
	mvwprintw(nc->win, 20, 4, "Iter : [%i]", e->tool.iter);
	mvwprintw(nc->win, 21, 4, "Zoom : [%i]", e->tool.zoom);
	mvwprintw(nc->win, 22, 4, "X    : [%i]", 0);
	mvwprintw(nc->win, 23, 4, "Y    : [%i]", 0);
	mvwprintw(nc->win, 24, 4, "Over : [%i]", e->bud.over);
	mvwprintw(nc->win, 25, 4, "Anti : [%i]", e->bud.anti);
	mvwprintw(nc->win, 26, 4, "Gain : [%.2f]", e->bud.gain);
	mvwprintw(nc->win, 27, 4, "COLOR [MIN][MAX]");
	wattron(nc->win, COLOR_PAIR(NC_RED));
	mvwprintw(nc->win, 28, 4, "Red [%i][%i]", e->bud.min[2], e->bud.max[2]);
	wattroff(nc->win, COLOR_PAIR(NC_RED));
	wattron(nc->win, COLOR_PAIR(NC_GREEN));
	mvwprintw(nc->win, 29, 4, "Green [%i][%i]", e->bud.min[1], e->bud.max[1]);
	wattroff(nc->win, COLOR_PAIR(NC_GREEN));
	wattron(nc->win, COLOR_PAIR(NC_CYAN));
	mvwprintw(nc->win, 30, 4, "Blue [%i][%i]", e->bud.min[0], e->bud.max[0]);
	wattroff(nc->win, COLOR_PAIR(NC_CYAN));
	wattron(nc->win, COLOR_PAIR(NC_GREEN));
	mvwprintw(e->nc.win, 32, 2, "Temps : %i:%i\n", e->min, e->sec);
	wattroff(nc->win, COLOR_PAIR(NC_GREEN));
}
