/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:37:14 by kmehour           #+#    #+#             */
/*   Updated: 2023/01/17 11:22:10 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	pin;
	size_t	n_len;

	pin = 0;
	if (!needle || !haystack)
		return (NULL);
	n_len = ft_strlen(needle);
	if (!*needle)
		return ((char *)haystack);
	while ((len - pin) >= (n_len) && haystack[pin])
	{
		if (!ft_strncmp((haystack + pin), needle, n_len))
			return ((char *)(haystack + pin));
		pin++;
	}
	return (NULL);
}
