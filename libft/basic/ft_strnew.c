/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 18:10:52 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/08 02:00:06 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char*)ft_memalloc(sizeof(*str) * (size + 1))))
		return (NULL);
	if (!str)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}
