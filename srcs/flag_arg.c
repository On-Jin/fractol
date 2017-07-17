/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 22:13:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/17 05:13:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	check_name(t_env *e, char **argv, int *i)
{
	while (argv[*i])
	{
		if (!ft_strcmp(argv[*i], "mandelbrot"))
			e->num = NUM_MANDEL;
		else if (!ft_strcmp(argv[*i], "julia"))
			e->num = NUM_JULIA;
		else
		{
			ft_putstr_fd("./fractol [-GP] {NOTHING}or{mandelbrot,julia}\n", 2);
			return (0);
		}
		(*i)++;
	}
	return (1);
}

static int	check_arg_argv(t_env *e, char **argv, int i)
{
	int k;

	k = 1;
	while (argv[i][k])
	{
		if (argv[i][k] == 'G')
			(e->flag |= F_GPU);
		else if (argv[i][k] == 'P')
			(e->flag |= F_PRECISION);
		else
		{
			ft_putstr_fd("./fractol [-GP] {NOTHING}or{mandelbrot,julia}\n", 2);
			return (0);
		}
		k++;
	}
	return (1);
}

int			flag_arg(t_env *e, int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '-' || !argv[i][1])
		{
			if (!(check_name(e, argv, &i)))
				return (0);
		}
		else
		{
			if (!(check_arg_argv(e, argv, i)))
				return (0);
		}
		i++;
	}
	return (1);
}
