# include "minishell.h"


/*
	@brief Check if a cher is a white space
 */
int	is_whitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

void	ft_change_wspace(char *str)
{
	int i;
	char *next_quote;

	i = 0;
	while (str[i]){
		if (is_whitespace(str[i])){
			str[i] = SPLIT_SEP;
		}
		if( str[i] == '"' || str[i] == '\'')
		{
			next_quote = ft_strchr(&str[i + 1], str[i]);
			if (next_quote){
				// *next_quote = SPLIT_SEP;
				// str[i] = SPLIT_SEP;
				i += (next_quote - &str[i]);
			}
		}
		i++;
	}
}

char	**ft_parse_cmd(char *cmd_str)
{
	char **new_tab;

	ft_change_wspace(cmd_str);
	new_tab= ft_split(cmd_str, SPLIT_SEP);
	return (new_tab);
}

/*
	@brief Gets the first word of a string
*/
char	*ft_getfwd(char *str)
{
	int		i;
	char	*word;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != 29)
		i++;
	word = ft_substr(str, 0, i);
	return (word);
}

/*
	@brief Parse the raw input of a command into a t_exec structure

	@param strcmd Command in string format
	@param envp Environment system variable
 */
t_exec	*ft_parse_input(char *strcmd, char *const envp[])
{
	t_exec	*cmd = NULL;

	cmd = malloc(sizeof(t_exec));

	cmd->input = STDIN_FILENO;
	cmd->output = STDOUT_FILENO;
	cmd->tab = ft_parse_cmd(strcmd);
	cmd->path = ft_get_cmd_path(cmd->tab[0], envp);

	return cmd;
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

/*
	@brief Parse readline output and populate t_exec struct
*/
t_exec	**ft_parse_pipes(char *line, char *const envp[])
{
	int i;
	int cmd_count;
	t_exec **exec_tab = NULL;
	char **cmd_tab = NULL;

	// Count number of |
	cmd_count = ft_str_char_count(line, '|');

	// Create t_exec array
	cmd_tab = ft_split(line, '|');
	exec_tab = (t_exec **) ft_calloc((cmd_count + 1),  sizeof(t_exec*));

	i = 0;
	while(i < cmd_count)
	{
		// Populate structurs
		exec_tab[i] = ft_parse_input(cmd_tab[i], envp);
		i++;
	}

	// Set pipes
	ft_set_pipes(exec_tab, cmd_count);

	// ft_free_tab(cmd_tab);
	return exec_tab;
}
