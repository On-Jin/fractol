/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 08:33:22 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/10 22:27:30 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	call_gnl(t_env *e, char **line, int fd)
{
	if (get_next_line(fd, line) != 1)
		end_of_program(e, "Erreur de parsing\n");
	if (!(*line))
		end_of_program(e, "Erreur de parsing\n");
}

static void	parsing_min_max(t_env *e, char *line, int fd)
{
	char		**str;
	char		**str2;
	int			i;

	call_gnl(e, &line, fd);
	str = ft_strsplit(line, ' ');
	ft_strdel(&line);
	call_gnl(e, &line, fd);
	str2 = ft_strsplit(line, ' ');
	ft_strdel(&line);
	i = 0;
	while (str[i] && str2[i])
	{
		e->bud.min[i] = ft_atoi(str[i]);
		e->bud.max[i] = ft_atoi(str2[i]);
		ft_strdel(&str[i]);
		ft_strdel(&str2[i]);
		i++;
	}
	free(str);
	free(str2);
	if (i != 3)
		end_of_program(e, "Erreur de parsing, Zoom < 0\n");
}

static void	parsing_special(t_env *e, char *line, int fd)
{
	call_gnl(e, &line, fd);
	e->bud.over = ft_atoi(line);
	ft_strdel(&line);
	if (e->bud.over < 1 || e->bud.over > 4)
		end_of_program(e, "Erreur de parsing, Over Bud [1-4]\n");
	call_gnl(e, &line, fd);
	e->bud.anti = ft_atoi(line);
	ft_strdel(&line);
	if (e->bud.anti < 0 || e->bud.anti > 1)
		end_of_program(e, "Erreur de parsing, Anti [0-1]\n");
	call_gnl(e, &line, fd);
	e->bud.gain = (float)ft_atoi(line) / 10;
	ft_strdel(&line);
	if (e->bud.gain < 0)
		end_of_program(e, "Erreur de parsing, Gain < 0\n");
}

static void	parsing(t_env *e, char *line, int fd)
{
	call_gnl(e, &line, fd);
	e->tool.iter = (long int)ft_atoi(line);
	if (e->tool.iter < 0)
		end_of_program(e, "Erreur de parsing\n");
	ft_strdel(&line);
	call_gnl(e, &line, fd);
	e->tool.zoom = ft_atoi(line);
	ft_strdel(&line);
	if (e->tool.zoom < 0)
		end_of_program(e, "Erreur de parsing\n");
	call_gnl(e, &line, fd);
	e->tool.ajj_x = (V_PRECI)ft_atoi(line);
	ft_strdel(&line);
	call_gnl(e, &line, fd);
	e->tool.ajj_y = (V_PRECI)ft_atoi(line);
	ft_strdel(&line);
}

void		ncurses_parsing(t_env *e, t_nc *nc)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(e->name_preset[nc->cursor], O_RDONLY);
	if (!fd)
		end_of_program(e, "Erreur de fichier\n");
	parsing(e, line, fd);
	parsing_special(e, line, fd);
	parsing_min_max(e, line, fd);
	close(fd);
	wrefresh(nc->win);
}
