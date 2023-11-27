#include "minishell.h"

void ft_check_open_quotes(char *line)
{
	int i;
	char *ptr;


	i = 0;
	while(line[i])
	{
		if( line[i] == '"' || line[i] == '\'')
		{
			ptr = ft_strchr(&line[i + 1], line[i]);
			if (!ptr)
				ft_raise_err("unclosed quotes", 99);
			i += ptr - &line[i];
		}
		i++;
	}
}

int skip_quotes(char *str, int i, char quote)
{
	char *next_quote;
	int j;

	j = i;
	while (str[j])
	{
		if( str[j] == quote)
		{
			next_quote = ft_strchr(&str[j + 1], str[j]);
			if (next_quote)
				return j + (next_quote - &str[j]);
		}
		j++;
	}
	return i;
}

int is_meta(char c)
{
	return(c == '|' || c == '<' || c == '>');
}

int get_char_index(char*s, char c)
{
	int i;

	i = 0;
	while(s[i])
	{
		if(s[i] == c)
			return i;
		i++;
	}
	return -1;
}
