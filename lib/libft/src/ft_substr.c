/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:27:50 by kmehour           #+#    #+#             */
/*   Updated: 2023/11/05 11:39:16 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	dest_size;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	dest_size = ft_strlen((s + start)) + 1;
	if ((dest_size - 1) > len)
		dest_size = len + 1;
	ptr = (char *)gc_calloc(dest_size, 1);
	if (!ptr || !s)
		return (NULL);
	ft_strlcpy(ptr, (s + start), dest_size);
	return (ptr);
}
