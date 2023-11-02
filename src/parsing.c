# include "minishell.h"

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

	new_node = ft_calloc(1, sizeof(t_exec_node));
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
t_exec_node	*ft_parse_input(char *strcmd, char *const envp[])
{
	t_exec_node	*cmd = NULL;

	cmd = ft_creat_exec_node();

	cmd->input = STDIN_FILENO;
	cmd->output = STDOUT_FILENO;
	cmd->pfd[0] = -1;
	cmd->pfd[1] = -1;
	cmd->tab = ft_parse_cmd(strcmd);
	cmd->path = ft_get_cmd_path(cmd->tab[0], envp);

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

char* get_var_string(char *var, char *const envp[])
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0 &&
			get_char_index(envp[i],'=') == (int)ft_strlen(var))
			return envp[i];
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
	
	
	//printf("DEBUG - first_part: %s\n", first_part);
	//printf("DEBUG - second_part: %s\n", second_part);


	//free(first_part);
	//free(second_part);
	// free(line);

	return new_line;
}

char* replace_vars_by_value(char *line, char *const envp[])
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
		if(line[i] == '\'' && flag == 0)
			flag = 1;
		else if(line[i] == '\'' && flag == 1)
			flag = 0;
		if(line[i] == '$' && flag == 0)
		{
			start = i + 1;
			while(line[start] && (ft_isalnum(line[start]) || line[start] == '_'))
				start++;

			user_var = ft_substr(line, i + 1, start - (i + 1));
			var_string = get_var_string(user_var,envp);

			line = get_new_line(line,i, start, var_string);
			
			free(user_var);
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
