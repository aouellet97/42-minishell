#include "execution.h"
#include "parsing.h"
#include "testing.h"

int	ft_is_dir(char *str)
{
	return ft_strchr("./", str[0]) || ft_strchr(str, '/');
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

	i = -1;
	path_tab = ft_get_envpaths(envp);
	res = -1;
	if (cmd && ft_is_dir(cmd) && access(cmd, X_OK) == 0)
		return (cmd);
	else
	{
		while (path_tab[++i])
		{
			tmp = ft_strjoin_path(path_tab[i], cmd);
			res = access(tmp, R_OK);
			if (res == 0)
				break ;
			gc_free(tmp);
		}
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
	gc_free(env_paths);
	return (tab);
}

/*
	@brief Create and initialize a t_exec_node
 */
t_exec_node	*ft_creat_exec_node(void)
{
	t_exec_node	*new_node;

	new_node = gc_calloc(1, sizeof(t_exec_node));
	new_node->next = NULL;
	new_node->input = STDIN_FILENO;
	new_node->output = STDOUT_FILENO;
	new_node->pfd[0] = -1;
	new_node->pfd[1] = -1;
	new_node->prev_pipe_out = -1;
	new_node->error_flag = false;
	new_node->path = NULL;
	new_node->tab = NULL;
	get_ms()->node_i++;
	return (new_node);
}

/*
	@brief For the NORM !!
 */
void	ft_free_n_exit(int err_code)
{
	rl_clear_history();
	ft_close_all_fds(get_ms()->fd_list);
	gc_free_all();
	exit(err_code);
}
