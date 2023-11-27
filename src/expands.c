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

char *expand_exit_status(char*line,int i)
{
	char*new_line;
	char*first_part;
	char*second_part;
	int number;
	
	number = errno; //replace with struct erno

	first_part = ft_substr(line,0,i);
	second_part = ft_strjoin(ft_itoa(number),line + i + 2);
	new_line = ft_strjoin(first_part,second_part);
	return new_line;
}

char* expand_dollar_sign(char *line,int *i) //could remove the int pointer and i-- at end
{
	char *user_var;
	char *var_string;
	int start;

	start = 0;
	user_var = NULL;
	var_string = NULL;

	start = *i + 1;
	while(line[start] && (ft_isalnum(line[start]) || line[start] == '_'))
		start++;
	if(start > *i + 1)
	{
		user_var = ft_substr(line, *i + 1, start - (*i + 1));
		var_string = get_var_string(user_var,get_ms()->env);

		line = get_new_line(line,*i, start, var_string);
		gc_free(user_var);
		(*i)--;
	}
	
	return line;
}

char* expand_quotes_dollar_sign(char *line,int *i)
{
	char *new_line;
	char** split;
	new_line = NULL;
	if(*i == 0)
	{
		new_line = ft_strdup(line + 1);
	}
	else
	{
		line[*i] = SPLIT_SEP;
		split = ft_split(line,	SPLIT_SEP);

		new_line = ft_strjoin(split[0],split[1]);
	}
	(*i)--;
	return new_line;
}

char*	remove_quotes(char *line)
{
	int i;
	char *next_quote;
	char	**split;

	i = 0;
	next_quote = NULL;
	split = NULL;
	while (line[i])
	{
		if(line[i] == '"' || line[i] == '\'')
		{
			next_quote = ft_strchr(&line[i + 1], line[i]);
			*next_quote = SPLIT_SEP;
			line[i] = SPLIT_SEP;
			i += (next_quote - &line[i]);
		}
		i++;
	}
	split = ft_split(line,SPLIT_SEP);
	line = NULL;
	i = 0;
	while(split[i])
	{
		line = ft_strjoin(line, split[i]);
		i++;
	}
	
	return line;
}

char* expand(char*line)
{
	int i;
	int dq_count;

	dq_count = 0; 
	i = 0;
	while(line[i])
	{
		if(line[i] == '\"')
			dq_count++;
		if(line[i] == '\'' && dq_count % 2 == 0)
			i = skip_single_quotes(line, i);
		if(line[i] == '$' && line[i + 1] == '?')
			line = expand_exit_status(line,i);
		if(line[i] == '$' && dq_count % 2 == 0 && (line[i + 1] == '\'' || line[i + 1] == '\"'))
			line = expand_quotes_dollar_sign(line,&i);
		if(line[i] == '$')
			line = expand_dollar_sign(line,&i);
		i++;
	}

	return line;
}
