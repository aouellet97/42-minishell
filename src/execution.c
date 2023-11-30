#include "minishell.h"

/*
	@brief Check if command is a builtin, if so return the builtin function pointer

	@param cmd Command to be checked
	@returns A pointer to the builtin function if cmd is builtin, else NULL
 */
t_builtin_ptr get_builtin_ptr(t_exec_node *cmd)
{
	if (!cmd || !cmd->tab)
		return (NULL);
	if (strcmp(cmd->tab[0], "env") == 0)
		return (&ft_env);
	if (strcmp(cmd->tab[0], "pwd") == 0)
		return (&ft_pwd);
	if (strcmp(cmd->tab[0], "echo") == 0)
		return (&ft_echo);
	if (strcmp(cmd->tab[0], "cd") == 0)
		return (&ft_cd);
	if (strcmp(cmd->tab[0], "export") == 0)
		return (&ft_export);
	if (strcmp(cmd->tab[0], "unset") == 0)
		return (&ft_unset);
	if (strcmp(cmd->tab[0], "exit") == 0)
		return (&ft_exit);
	return (NULL);
}

/*
	@brief Executes a single t_exec_node after setting in and outs
*/
void ft_execute_node(t_exec_node *cmd)
{
	t_builtin_ptr builtin_ptr;

	if(!cmd || !(cmd->tab))
	{
		get_ms()->ms_errno = 0;
		return;
	}
	builtin_ptr = get_builtin_ptr(cmd);
	// if (builtin_ptr != NULL)
	// printf(COLOR_BLUE "DEBUG - this is a builtin\n" COLOR_RESET);
	fflush(NULL);

	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		// readline("Waiting in child ...");
		// ft_set_signal_actions(SIG_CHILD);
		ft_dup2(cmd->input, STDIN_FILENO);
		ft_close(cmd->input);
		ft_dup2(cmd->output, STDOUT_FILENO);
		ft_close(cmd->output);
		ft_close(cmd->pfd[0]);
		ft_close(cmd->pfd[1]);
		ft_close(cmd->prev_pipe_out);
		if (cmd->error_flag == true)
		{
			gc_free_all();
			exit(1);
		}
		// Execut builtin
		if (builtin_ptr)
		{
			exit(builtin_ptr(get_ms(), cmd->tab));
		}
		else if (cmd->path)
		{
			execve(cmd->path, cmd->tab, get_ms()->env);
		}
		ft_raise_err(" command not found", 127);
	}
}

void ft_exec_single_node(t_exec_node *cmd, t_builtin_ptr builtin_ptr)
{
	int std_in;
	int std_out;

	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	if (std_in == -1 || std_out == -1)
	{
		// Handle error
	}
	ft_dup2(cmd->input, STDIN_FILENO);
	ft_dup2(cmd->output, STDOUT_FILENO);
	ft_dup2(cmd->input, STDIN_FILENO);
	ft_dup2(cmd->output, STDOUT_FILENO);
	ft_close(cmd->input);
	ft_close(cmd->output);
	get_ms()->ms_errno = builtin_ptr(get_ms(), cmd->tab);
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	ft_close(std_in);
	ft_close(std_out);
}

/*
	@brief Execute t_exec_node list
*/
void ft_execute_list(t_exec_node *head)
{
	t_builtin_ptr builtin_ptr;
	t_exec_node *ptr;
	int wstat;

	ptr = head;
	builtin_ptr = get_builtin_ptr(ptr);
	if (!ptr->next && builtin_ptr && !ptr->error_flag)
	{
		ft_exec_single_node(ptr, builtin_ptr);
		return;
	}

	while (ptr)
	{
		ft_set_node_pipes(ptr);
		ft_execute_node(ptr);
		ft_close(ptr->input);
		ft_close(ptr->output);
		ft_close(ptr->prev_pipe_out);
		ptr = ptr->next;
	}

	ptr = head;
	while (ptr)
	{
		waitpid(ptr->pid, &wstat, 0);
		if (WIFEXITED(wstat))
		{
			get_ms()->ms_errno = WEXITSTATUS(wstat);
			// printf("DEBUG - node executed, return status %d\n", get_ms()->ms_errno);
		}
		ft_close(ptr->pfd[0]);
		ft_close(ptr->pfd[1]);
		ptr = ptr->next;
	}
}
