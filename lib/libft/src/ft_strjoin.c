/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:18:22 by kmehour           #+#    #+#             */
/*   Updated: 2023/11/05 11:38:48 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *str1, const char *str2)
{
	char	*new_string;
	size_t	len_str1;
	size_t	len_str2;

	len_str1 = ft_strlen(str1);
	len_str2 = ft_strlen(str2);
	new_string = gc_calloc(len_str1 + len_str2 + 1, 1);
	if (!new_string)
		return (NULL);
	new_string[len_str1 + len_str2] = '\0';
	ft_memcpy(new_string, (void *)str1, len_str1);
	ft_memcpy((new_string + len_str1), (void *)str2, len_str2);
	return (new_string);
}
