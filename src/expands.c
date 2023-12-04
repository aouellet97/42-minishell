#include "minishell.h"

char	*expand_dollar_sign(char *line, int *i)
{
	char	*user_var;
	char	*var_string;
	int		start;

	start = 0;
	user_var = NULL;
	var_string = NULL;
	start = *i + 1;
	while (line[start] && (ft_isalnum(line[start]) || line[start] == '_'))
		start++;
	if (start > *i + 1)
	{
		user_var = ft_substr(line, *i + 1, start - (*i + 1));
		var_string = get_var_string(user_var, get_ms()->env);
		line = get_new_line(line,*i, start, var_string);
		gc_free(user_var);
		(*i)--;
	}
	return (line);
}

char	*expand_quotes_dollar_sign(char *line, int *i)
{
	char	*new_line;
	char	**split;

	new_line = NULL;
	if (*i == 0)
	{
		new_line = ft_strdup(line + 1);
	}
	else
	{
		line[*i] = SPLIT_SEP;
		split = ft_split(line, SPLIT_SEP);
		new_line = ft_strjoin(split[0], split[1]);
	}
	if ((*i) > 0)
		(*i)--;
	return (new_line);
}

char	*remove_quotes(char *line, int i)
{
	char	*next_quote;
	char	**split;

	next_quote = NULL;
	split = NULL;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			next_quote = ft_strchr(&line[i + 1], line[i]);
			*next_quote = SPLIT_SEP;
			line[i] = SPLIT_SEP;
			i += (next_quote - &line[i]);
		}
		i++;
	}
	split = ft_split(line, SPLIT_SEP);
	line = NULL;
	i = 0;
	while (split && split[i])
	{
		line = ft_strjoin(line, split[i]);
		i++;
	}
	return (line);
}

char	*expand(char*line)
{
	int	i;
	int	dq_count;

	dq_count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			dq_count++;
		if (line[i] == '\'' && dq_count % 2 == 0)
			i = skip_single_quotes(line, i);
		if (line[i] == '$' && line[i + 1] == '?')
			line = expand_exit_status(line, i);
		if (line[i] == '$' && dq_count % 2 == 0
			&& (line[i + 1] == '\'' || line[i + 1] == '\"'))
			line = expand_quotes_dollar_sign(line, &i);
		if (line[i] == '$')
			line = expand_dollar_sign(line, &i);
		i++;
	}
	return (line);
}
