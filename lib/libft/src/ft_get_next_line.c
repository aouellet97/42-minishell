/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouellet <aouellet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:15:15 by kmehour           #+#    #+#             */
/*   Updated: 2023/11/19 18:36:11 by aouellet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*ft_strjoin_free(char *str1, const char *str2)
{
	char	*new_string;
	size_t	len_str1;
	size_t	len_str2;

	len_str1 = ft_strlen(str1);
	len_str2 = ft_strlen(str2);
	new_string = gc_calloc(len_str1 + len_str2 + 1, 1);
	if (!new_string)
	{
		free(str1);
		return (NULL);
	}
	new_string[len_str1 + len_str2] = '\0';
	ft_memcpy(new_string, (void *)str1, len_str1);
	ft_memcpy((new_string + len_str1), (void *)str2, len_str2);
	free(str1);
	return (new_string);
}

char	*load_data(int fd, char *cache)
{
	char	*buffer;
	int		ret;

	buffer = (char *)gc_calloc(BUFFER_SIZE + 1, sizeof(char));
	ret = BUFFER_SIZE;
	if (read(fd, buffer, 0) < 0)
	{
		printf("INVALID FD\n");
		free(buffer);
		return (NULL);
	}
	while (ft_strchr(cache, '\n') == NULL)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret <= 0)
			break ;
		buffer[ret] = '\0';
		cache = ft_strjoin_free(cache, buffer);
	}
	free(buffer);
	return (cache);
}

char	*get_line(char *cache)
{
	char	*next_line;
	int		i;

	i = 0;
	if (!cache[0])
	{
		return (NULL);
	}
	while (cache[i] && cache[i] != '\n')
		i++;
	if (cache[i] == '\n')
		i++;
	next_line = gc_calloc(i + 1, sizeof(char));
	if (!next_line)
		return (NULL);
	while (i-- > 0)
		next_line[i] = cache[i];
	return (next_line);
}

char	*trim_cache(char *cache)
{
	char	*trimmed;
	char	*ptr;

	ptr = ft_strchr(cache, '\n');
	if (!cache[0] || !ptr)
	{
		free(cache);
		return (NULL);
	}
	trimmed = ft_strdup(ptr + 1);
	free(cache);
	if (!trimmed)
		return (NULL);
	return (trimmed);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*next_line;

	cache = load_data(fd, cache);
	if (!cache)
		return (NULL);
	next_line = get_line(cache);
	cache = trim_cache(cache);
	return (next_line);
}
