#include "minishell.h"
/*
	@brief Check if a cher is a white space
 */
int	is_whitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

void	ft_change_wspace(char *str)
{
	int		i;
	char	*next_quote;

	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]))
			str[i] = SPLIT_SEP;
		if (str[i] == '"' || str[i] == '\'')
		{
			next_quote = ft_strchr(&str[i + 1], str[i]);
			if (next_quote)
				i += (next_quote - &str[i]);
		}
		i++;
	}
}

/*
	@brief Check if token is any redirection type
*/
int	ft_is_redirection(t_ms_token *tk_ptr)
{
	return (tk_ptr->tk_type == TK_IN_REDIR
		|| tk_ptr->tk_type == TK_OUT_REDIR
		|| tk_ptr->tk_type == TK_OUT_REDIR_AP);
}
