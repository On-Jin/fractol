/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_print_stat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 10:56:37 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/17 11:05:28 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ncurses_print_stat(t_env *e, t_nc *nc)
{
	mvwprintw(nc->win, 2, 4, "Iter  : [%i]", e->tool.iter);
	mvwprintw(nc->win, 3, 4, "Zoom  : [%i]", e->tool.zoom);

	mvwprintw(nc->win, 5, 4, "Ajj_x : [%f]", e->tool.ajj_x);
	mvwprintw(nc->win, 6, 4, "Ajj_y : [%f]", e->tool.ajj_y);

	mvwprintw(nc->win, 8, 4, "Mov_x : [%i]", e->tool.move_x);
	mvwprintw(nc->win, 9, 4, "Mov_y : [%i]", e->tool.move_y);

	mvwprintw(nc->win, 8, 4, "____x : [%f]", e->tool.ajj_x / e->tool.zoom);
	mvwprintw(nc->win, 9, 4, "____y : [%f]", e->tool.ajj_y / e->tool.zoom);
}
