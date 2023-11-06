/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:18:38 by kmehour           #+#    #+#             */
/*   Updated: 2023/05/08 11:20:25 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ps1;
	unsigned char	*ps2;

	i = 0;
	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	if (n < 1)
		return (0);
	while (ps1[i] && ps2[i] && i < n - 1)
	{
		if (ps1[i] != ps2[i])
			break ;
		i++;
	}
	return (ps1[i] - ps2[i]);
}
