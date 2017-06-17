/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_refresh.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 06:23:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/17 06:35:47 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ncurses_refresh(t_env *e, t_nc *nc)
{
	(void)e;
	werase(nc->win);
	box(nc->win, 0, 0);
	mvwprintw(nc->win, 1, 1, "slt");
	wrefresh(nc->win);
}
