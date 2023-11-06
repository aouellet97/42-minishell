/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:23:26 by kmehour           #+#    #+#             */
/*   Updated: 2023/01/17 11:23:52 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		signe;
	int		i;
	int		result;

	i = 0;
	signe = 1;
	result = 0;
	if (!str)
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			signe *= -1;
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (signe * result);
}
