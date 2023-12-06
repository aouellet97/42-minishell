/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:40:54 by kmehour           #+#    #+#             */
/*   Updated: 2023/12/06 17:40:55 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_new_line(char*line, int start, int end, char*var_string)
{
	char	*first_part;
	char	*second_part;
	char	*new_line;
	char	*var_value;

	first_part = NULL;
	second_part = NULL;
	new_line = NULL;
	var_value = NULL;
	first_part = ft_substr(line, 0, start);
	if (var_string)
		var_value = var_string + get_char_index(var_string, '=') + 1;
	second_part = ft_strjoin(var_value, line + end);
	new_line = ft_strjoin(first_part, second_part);
	return (new_line);
}

int	skip_single_quotes(char *str, int i)
{
	char	*next_quote;
	int		j;

	j = i;
	while (str[j])
	{
		if (str[j] == '\'')
		{
			next_quote = ft_strchr(&str[j + 1], str[j]);
			if (next_quote)
				return (j + (next_quote - &str[j]));
		}
		j++;
	}
	return (i);
}
