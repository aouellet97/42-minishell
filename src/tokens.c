#include "minishell.h"

t_ms_token	*get_token(t_ms_token *head, char *content)
{
	t_ms_token	*new_token;
	t_ms_token	*ptr;
	char		*exp_content;

	new_token = gc_calloc(1, sizeof(t_ms_token));
	new_token->raw_content = ft_strdup(content);
	exp_content = expand(content);
	new_token->tk_type = ft_assigne_tk_type(exp_content);
	new_token->content = remove_quotes(exp_content, 0);
	new_token->next = NULL;
	if (head == NULL)
	{
		return (new_token);
	}
	ptr = head;
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	ptr->next = new_token;
	return (head);
}

t_ms_token	*get_meta_token(t_ms_token*head, char *line, int *i)
{
	char	*content;
	char	c;
	int		start;

	content = NULL;
	start = *i;
	c = line[*i];
	while (line[*i] && line[*i] == c)
		(*i)++;
	content = ft_substr(line, start, *i - start);
	if (!line[*i])
		ft_raise_err(NULL, "syntax error near unexpected token", 258);
	if ((ft_strlen(content) > 1 && c == '|')
		|| (ft_strlen(content) > 2 && c != '|'))
		ft_raise_err(NULL, "syntax error near unexpected token", 258);
	return (get_token(head, content));
}

t_ms_token	*get_str_token(t_ms_token*head, char *line, int *i)
{
	char	*content;
	int		start;

	content = NULL;
	start = *i;
	while (line[*i] && !is_whitespace(line[*i]) && !is_meta(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '\"')
			*i = skip_quotes(line, *i, line[*i]);
		(*i)++;
	}
	content = ft_substr(line, start, *i - start);
	return (get_token(head, content));
}

void	ft_check_unexpected(t_ms_token *head)
{
	t_ms_token	*ptr;
	bool		*ms_flag;

	ms_flag = &(get_ms()->reset_loop_flag);
	ptr = head;
	if (head->tk_type == TK_PIPE)
		*ms_flag = true;
	while (ptr && !(*ms_flag))
	{
		get_ms()->last_valid_tk = ptr->content;
		if (ptr->tk_type == TK_PIPE
			&& ptr->next && ptr->next->tk_type == TK_PIPE)
		{
			*ms_flag = true;
		}
		if (ft_is_redirection(ptr)
			&& ptr->next && ptr->next->tk_type != TK_STR)
		{
			*ms_flag = true;
			break ;
		}
		ptr = ptr->next;
	}
	if (*ms_flag)
		ft_raise_err(NULL, "syntax error near unexpected token", 258);
}

t_ms_token	*ft_tokenize(char *line)
{
	t_ms_token	*token_list;
	int			i;

	token_list = NULL;
	i = 0;
	ft_check_open_quotes(line);
	while (line[i])
	{
		if (is_whitespace(line[i]))
			i++;
		else if (is_meta(line[i]))
			token_list = get_meta_token(token_list, line, &i);
		else if (!is_whitespace(line[i]))
			token_list = get_str_token(token_list, line, &i);
	}
	ft_check_unexpected(token_list);
	free(get_ms()->line);
	get_ms()->line = NULL;
	return (token_list);
}
