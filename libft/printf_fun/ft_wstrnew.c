/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 19:24:25 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/08 02:02:40 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/printf_fun.h"

wchar_t		*ft_wstrnew(size_t size)
{
	wchar_t	*str;
	size_t	i;

	if (!(str = (wchar_t*)ft_memalloc(sizeof(*str) * size + 1)))
		exit(0);
	if (!str)
		return (NULL);
	i = 0;
	while (i < size + 1)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}
