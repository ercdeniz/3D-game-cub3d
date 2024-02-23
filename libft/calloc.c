/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:35:54 by ercdeniz          #+#    #+#             */
/*   Updated: 2024/02/23 14:36:29 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*tmp;
	void	*ptr;
	size_t	length;

	length = count * size;
	ptr = malloc(length);
	if (ptr)
	{
		tmp = (char *)ptr;
		while (length--)
			*tmp++ = 0;
	}
	return (ptr);
}
