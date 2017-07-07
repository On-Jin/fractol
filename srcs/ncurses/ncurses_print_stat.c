/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_print_stat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 10:56:37 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/07 16:31:41 by ntoniolo         ###   ########.fr       */
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

	mvwprintw(nc->win, 11, 4, "____x : [%f]", e->tool.ajj_x / e->tool.zoom);
	mvwprintw(nc->win, 12, 4, "____y : [%f]", e->tool.ajj_y / e->tool.zoom);

	mvwprintw(nc->win, 14, 4, "____x : Min[%.2f] Max[%.2f]", e->tool.xmin, e->tool.xmax);
	mvwprintw(nc->win, 15, 4, "____y : Min[%.2f] Max[%.2f]", e->tool.ymin, e->tool.ymax);

	mvwprintw(nc->win, 16, 4, "Incr_dir [%i]\n", e->incr_dir);
}
