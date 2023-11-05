/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:52:15 by kmehour           #+#    #+#             */
/*   Updated: 2023/11/05 11:38:20 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_digits(int n)
{
	int	size;

	size = 0;
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;
	int		is_negative;
	long	nbr;

	nbr = n;
	is_negative = (n <= 0);
	if (is_negative)
		nbr = -nbr;
	size = count_digits(n) + is_negative;
	str = gc_calloc(size + 1, 1);
	if (!str)
		return (NULL);
	str[size--] = 0;
	while (nbr > 0)
	{
		str[size--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (!str[1] && !size)
		str[0] = '0';
	if (str[1] && !size)
		str[0] = '-';
	return (str);
}
