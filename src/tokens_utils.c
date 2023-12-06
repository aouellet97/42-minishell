/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:40:40 by kmehour           #+#    #+#             */
/*   Updated: 2023/12/06 17:40:41 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_open_quotes(char *line)
{
	int		i;
	char	*ptr;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			ptr = ft_strchr(&line[i + 1], line[i]);
			if (!ptr)
			{
				ft_raise_err(NULL, "unclosed quotes", 77);
				get_ms()->reset_loop_flag = true;
				return ;
			}
			i += ptr - &line[i];
		}
		i++;
	}
}

int	skip_quotes(char *str, int i, char quote)
{
	char	*next_quote;
	int		j;

	j = i;
	while (str[j])
	{
		if (str[j] == quote)
		{
			next_quote = ft_strchr(&str[j + 1], str[j]);
			if (next_quote)
				return (j + (next_quote - &str[j]));
		}
		j++;
	}
	return (i);
}

int	is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	get_char_index(char*s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/*
	@brief Assigns the token type according based on the content
*/
int	ft_assigne_tk_type(char *content, bool *ds_exp)
{
	if (!content[0])
		return (TK_NULL);
	if (*ds_exp == true)
		return (TK_STR);
	if (content[0] == '<' && content[1] == '<' && !content[2])
		return (TK_HEREDOC);
	if (content[0] == '>' && content[1] == '>' && !content[2])
		return (TK_OUT_REDIR_AP);
	if (content[0] == '<' && !content[1])
		return (TK_IN_REDIR);
	if (content[0] == '>' && !content[1])
		return (TK_OUT_REDIR);
	if (content[0] == '|' && !content[1])
		return (TK_PIPE);
	return (TK_STR);
}
