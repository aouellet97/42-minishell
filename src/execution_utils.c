
# include "execution.h"
# include "parsing.h"
# include "testing.h"

char	*ft_strjoin_sep(const char *s1, const char *s2, const char *separator)
{
	size_t	len_str1;
	size_t	len_str2;
	size_t	len_sep;
	// char	*separator;
	char	*new_string;

	if (separator == NULL)
		separator = "";
	len_str1 = ft_strlen(s1);
	len_str2 = ft_strlen(s2);
	len_sep  = ft_strlen(separator);
	new_string = malloc(len_str1 + len_sep + len_str2 + 1);
	if (!new_string)
		return (NULL);
	new_string[len_str1 + len_sep + len_str2] = '\0';
	ft_memcpy(new_string, (void *)s1, len_str1);
	ft_memcpy((new_string + len_str1), separator, 1);
	ft_memcpy((new_string + len_str1 + 1), (void *)s2, len_str2);
	return (new_string);
}

char	*ft_strjoin_char(const char *s1, const char *s2, char c)
{
	char sep[2];

	sep[0] = c;
	sep[1] = '\0';
	return ft_strjoin_sep(s1, s2, sep);
}

/*
	@brief Concatenate two strings, joined with a chosen separator

	@param parent left part of the joined path
	@param child right part of the joined path
	@return Full path string, Null if memory allocation crashed
*/
char *ft_strjoin_path(const char *parent, const char *child)
{
	return ft_strjoin_sep(parent, child, "/");
}

/*
	@brief Search and check access to a command in PATH

	@param cmd Command name
	@param envp Enviroment variable
	@return return the command path if accessible, NULL otherwise
 */
char	*ft_get_cmd_path(char *cmd, char *const envp[])
{
	char	**path_tab;
	char	*tmp;
	int		res;
	int		i;

	i = 0;
	path_tab = ft_get_envpaths(envp);
	res = -1;
	while (path_tab[i])
	{
		tmp = ft_strjoin_path(path_tab[i], cmd);
		res = access(tmp, R_OK);
		if (res == 0)
			break ;
		free(tmp);
		i++;
	}
	ft_free_tab(path_tab);
	if (res == 0)
		return (tmp);
	return (NULL);
}

/*
	@brief extracts the PATH variable from the env in a table

	@param envp Environment variable
	@return A char table[][] containing PATH folders
*/
char	**ft_get_envpaths(char *const envp[])
{
	char	*env_paths;
	char	**tab;

	env_paths = "";
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
		{
			env_paths = ft_strdup(*envp + 5);
		}
		envp++;
	}
	tab = ft_split(env_paths, ':');
	free(env_paths);
	return (tab);
}

/*
	@brief Create a pipe and sets the in/out of current and next node
 */
void	ft_set_node_pipes(t_exec_node *node)
{
	if (!node || !node->next)
		return;
	if (pipe(node->pfd) == -1)
	{
		ft_raise_err("Pipe error", 4);
	}
	node->output = node->pfd[1];
	node->next->input = node->pfd[0];
}