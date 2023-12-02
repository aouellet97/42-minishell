#include "minishell.h"

char* get_new_line(char*line, int start, int end, char*var_string)
{
	char *first_part = NULL;
	char *second_part = NULL;
	char *new_line = NULL;
	char *var_value = NULL;

	first_part = ft_substr(line,0,start);

	if(var_string)
		var_value = var_string + get_char_index(var_string,'=') + 1;
	second_part = ft_strjoin(var_value,line + end);
	new_line = ft_strjoin(first_part,second_part);
	return new_line;
}

int skip_single_quotes(char *str, int i)
{
	char *next_quote;
	int j;

	j = i;
	while (str[j])
	{
		if( str[j] == '\'')
		{
			next_quote = ft_strchr(&str[j + 1], str[j]);
			if (next_quote)
				return j + (next_quote - &str[j]);
		}
		j++;
	}
	return i;
}