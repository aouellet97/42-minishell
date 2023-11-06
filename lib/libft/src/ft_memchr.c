/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 19:19:17 by kmehour           #+#    #+#             */
/*   Updated: 2023/01/17 11:21:09 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*s;

	if (!str)
		return (NULL);
	s = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (s[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (0x0);
}
