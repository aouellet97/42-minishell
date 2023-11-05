/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:17:39 by kmehour           #+#    #+#             */
/*   Updated: 2023/11/05 11:38:32 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wordcount(const char *s, char c)
{
	size_t	count;

	if (!s || !*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	*ft_cpword(char *str, char **tab, char sep)
{
	int	i;
	int	idx;

	i = 0;
	idx = 0;
	if (!str[0])
		return (str);
	while (str[i] && str[i] != sep)
		i++;
	if (!i)
		return (str);
	while (tab[idx])
		idx++;
	tab[idx] = (char *)gc_calloc(i + 1, 1);
	if (!tab[idx])
	{
		ft_free_tab(tab);
		return (NULL);
	}
	ft_strlcpy(tab[idx], str, i + 1);
	return (str + i);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	tab_size;
	char	*ptr;

	if (!s)
		return (NULL);
	tab_size = ft_wordcount(s, c) + 1;
	tab = (char **)gc_calloc(tab_size, sizeof(char *));
	if (!tab)
		return (NULL);
	ptr = (char *)s;
	while (ptr && *ptr)
	{
		while (*ptr == c)
			ptr++;
		ptr = ft_cpword(ptr, tab, c);
	}
	if (!ptr)
		return (NULL);
	return (tab);
}
