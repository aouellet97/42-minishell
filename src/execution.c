#include "minishell.h"

/*
	@brief Check if command is a builtin, if so return
	the builtin function pointer

	@param cmd Command to be checked
	@returns A pointer to the builtin function if cmd is builtin, else NULL
 */
t_builtin_ptr	get_builtin_ptr(t_exec_node *cmd)
{
	if (!cmd || !cmd->tab)
		return (NULL);
	if (ft_istrcmp(cmd->tab[0], "env") == 0)
		return (&ft_env);
	if (ft_istrcmp(cmd->tab[0], "echo") == 0)
		return (&ft_echo);
	if (ft_istrcmp(cmd->tab[0], "pwd") == 0)
		return (&ft_pwd);
	if (ft_istrcmp(cmd->tab[0], "cd") == 0)
		return (&ft_cd);
	if (ft_strcmp(cmd->tab[0], "export") == 0)
		return (&ft_export);
	if (ft_strcmp(cmd->tab[0], "unset") == 0)
		return (&ft_unset);
	if (ft_strcmp(cmd->tab[0], "exit") == 0)
		return (&ft_exit);
	return (NULL);
}

void	ft_exec_single_node(t_exec_node *cmd, t_builtin_ptr builtin_ptr)
{
	int		std_in;
	int		std_out;
	t_ms	*mini_struct;

	mini_struct = get_ms();
	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	if (std_in == -1 || std_out == -1)
		ft_raise_err("Unexpected", "No standard in/out", 69);
	ft_dup2(cmd->input, STDIN_FILENO);
	ft_dup2(cmd->output, STDOUT_FILENO);
	ft_close(cmd->input);
	ft_close(cmd->output);
	cmd->std_in = std_in;
	cmd->std_out = std_out;
	mini_struct->ms_errno = builtin_ptr(mini_struct, cmd->tab, cmd);
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	ft_close(std_in);
	ft_close(std_out);
}

/*
	@brief Executes a single t_exec_node after setting in and outs
*/
void	ft_execute_node(t_exec_node *cmd)
{
	t_builtin_ptr	builtin_ptr;

	builtin_ptr = get_builtin_ptr(cmd);
	signal(SIGINT, SIG_IGN);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		ft_set_signal_actions(SIG_CHILD);
		ft_dup_in_out(cmd);
		if (!cmd || !(cmd->tab))
			ft_free_n_exit(0);
		if (cmd->error_flag)
			ft_free_n_exit(1);
		if (builtin_ptr)
			ft_free_n_exit(
				builtin_ptr(get_ms(), cmd->tab, cmd));
		else if (cmd->path)
			execve(cmd->path, cmd->tab, get_ms()->env);
		ft_raise_err(cmd->tab[0], "command not found", 127);
		ft_free_n_exit(get_ms()->ms_errno);
	}
}

void	ft_wait_execs(t_exec_node *ptr)
{
	int	wstat;

	wstat = 0;
	while (ptr)
	{
		waitpid(ptr->pid, &wstat, 0);
		if (WIFEXITED(wstat))
		{
			get_ms()->ms_errno = WEXITSTATUS(wstat);
		}
		ft_close(ptr->pfd[0]);
		ptr = ptr->next;
	}
}

/*
	@brief Execute t_exec_node list
*/
void	ft_execute_list(t_exec_node *head)
{
	t_builtin_ptr	builtin_ptr;
	t_exec_node		*ptr;

	ptr = head;
	builtin_ptr = get_builtin_ptr(ptr);
	if (ptr && !ptr->next && builtin_ptr && !ptr->error_flag)
	{
		ft_exec_single_node(ptr, builtin_ptr);
		return ;
	}
	while (ptr)
	{
		ft_set_node_pipes(ptr);
		ft_execute_node(ptr);
		ft_close(ptr->input);
		ft_close(ptr->output);
		ft_close(ptr->pfd[1]);
		ft_close(ptr->prev_pipe_out);
		ptr = ptr->next;
	}
	ft_wait_execs(head);
}
