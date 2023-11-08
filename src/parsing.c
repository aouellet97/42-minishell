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

char *replace_by_exit_status(char*line,int i)
{
	char*new_line;
	char*first_part;
	char*second_part;
	int number;
	
	number = 123; //replace with exit status function

	first_part = ft_substr(line,0,i);
	second_part = ft_strjoin(ft_itoa(number),line + i + 2);
	//printf("here %s\n",second_part);
	new_line = ft_strjoin(first_part,second_part);
	return new_line;
}

char* replace_vars_by_value(char *line)
{
	char *user_var;
	char *var_string;
	int flag;
	int i;
	int start;

	start = 0;
	i = 0;
	flag = 0;
	user_var = NULL;
	var_string = NULL;
	while(line[i])
	{
	
		if(line[i] == '\"')
			flag++;
		if(line[i] == '\'' && flag % 2 == 0)
			i = skip_single_quotes(line, i);
		if(line[i] == '$' && line[i + 1] == '?')
			line = replace_by_exit_status(line,i);
		if(line[i] == '$')
		{
			start = i + 1;
			while(line[start] && (ft_isalnum(line[start]) || line[start] == '_'))
				start++;
			if(start > i + 1)
			{
				user_var = ft_substr(line, i + 1, start - (i + 1));
				var_string = get_var_string(user_var,get_ms()->env);

				line = get_new_line(line,i, start, var_string);
				gc_free(user_var);
				i--;
			}
		}
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
