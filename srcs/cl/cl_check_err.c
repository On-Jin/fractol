/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_check_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 03:02:35 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/18 08:56:34 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	cl_check_err(cl_int err, const char *name)
{
	if (err != CL_SUCCESS)
	{
		ft_printf("Error : %s (%i)\n", name, err);
		exit(EXIT_FAILURE);
	}
}
