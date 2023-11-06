/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:36:44 by kmehour           #+#    #+#             */
/*   Updated: 2023/07/12 21:45:53 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*ps1;
	unsigned char	*ps2;

	i = 0;
	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	while (ps1[i] && ps2[i])
	{
		if (ps1[i] != ps2[i])
			break ;
		i++;
	}
	return (ps1[i] - ps2[i]);
}
