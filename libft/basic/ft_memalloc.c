/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 16:16:21 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/08 02:02:19 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

void	*ft_memalloc(size_t size)
{
	void *tab;

	if (!(tab = malloc(size)))
		exit(0);
	if (tab == NULL)
		return (NULL);
	ft_bzero(tab, size);
	return (tab);
}
