#include "minishell.h"

char	**ft_parse_cmd(char *cmd_str)
{
	char **new_tab;

	ft_change_wspace(cmd_str);
	new_tab= ft_split(cmd_str, SPLIT_SEP);
	return (new_tab);
}

char	**ft_sep_tokens(char *cmd_str)
{
	char **new_tab;

	ft_change_wspace(cmd_str);
	new_tab= ft_split(cmd_str, SPLIT_SEP);
	return (new_tab);
}

t_exec_node *ft_creat_exec_node()
{
	t_exec_node *new_node;

	new_node = gc_calloc(1, sizeof(t_exec_node));
	if (new_node == NULL)
		ft_raise_err("Mem allocation error", 1);
	new_node->next = NULL;
	return new_node;
}

/*
	@brief Parse the raw input of a command into a t_exec structure

	@param strcmd Command in string format
	@param envp Environment system variable
 */
t_exec_node	*ft_parse_input(char *strcmd)
{
	t_exec_node	*cmd = NULL;

	cmd = ft_creat_exec_node();

	cmd->input = STDIN_FILENO;
	cmd->output = STDOUT_FILENO;
	cmd->pfd[0] = -1;
	cmd->pfd[1] = -1;
	cmd->tab = ft_parse_cmd(strcmd);
	cmd->path = ft_get_cmd_path(cmd->tab[0], get_ms()->env);

	return cmd;
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

char* get_var_string(char *var, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0 &&
			get_char_index(env[i],'=') == (int)ft_strlen(var))
			return env[i];
		i++;
	}
	//look user variables
	return NULL;
}

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
	
	number = 123; //replace with struct erno

	first_part = ft_substr(line,0,i);
	second_part = ft_strjoin(ft_itoa(number),line + i + 2);
	//printf("here %s\n",second_part);
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

// void	ft_change_dollar_sign(char *str)
// {
// 	int i;
// 	char *next_quote;

// 	i = 0;
// 	while (str[i]){
// 		if (str[i] == '$'){
// 			str[i] = SPLIT_SEP;
// 		}
// 		if( str[i] == '"' || str[i] == '\'')
// 		{
// 			next_quote = ft_strchr(&str[i + 1], str[i]);
// 			if (next_quote){
// 				// *next_quote = SPLIT_SEP;
// 				// str[i] = SPLIT_SEP;
// 				i += (next_quote - &str[i]);
// 			}
// 		}
// 		i++;
// 	}
// }

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








/*
	@brief Return the number of occurences if a char in a string
 */
int ft_str_char_count(const char *str, char c)
{
	int count;
	int i;

	i = 0;
	count = 1;
	while(str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}







