
#include "minishell.h"

/* 
	@brief Check if command is a builtin, if so return the builtin function pointer
	
	@param cmd Command to be checked
	@returns A pointer to the builtin function if cmd is builtin, else NULL
 */
t_builtin_ptr get_builtin_ptr(t_exec_node *cmd)
{
	
	if(strcmp(cmd->tab[0],"env") == 0)
		return (&ft_env);
	if(strcmp(cmd->tab[0],"pwd") == 0)
		return (&ft_pwd);
	if(strcmp(cmd->tab[0],"echo") == 0)
		return (&ft_echo);
	if(strcmp(cmd->tab[0],"cd") == 0)
		return (&ft_cd);
	if(strcmp(cmd->tab[0],"export") == 0)
		return (&ft_export);
	if(strcmp(cmd->tab[0],"unset") == 0)
		return (&ft_unset);
	return (NULL);
}

/*
	@brief Executes a single t_exec_node after setting in and outs
*/
void	ft_execute_node(t_exec_node *cmd)
{
	int res;
	t_builtin_ptr builtin_ptr;

	res = 0;
	builtin_ptr = get_builtin_ptr(cmd);
	// if (builtin_ptr != NULL)
		// printf(COLOR_BLUE "DEBUG - this is a builtin\n" COLOR_RESET);
	fflush(NULL);

	if (cmd->error_flag == true)
		return ;

	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		// ft_set_signal_actions(SIG_CHILD);
		if (cmd->input > 2)
		{
			dup2(cmd->input, STDIN_FILENO);
			close(cmd->input);
		}
		if (cmd->output > 2)
		{
			dup2(cmd->output, STDOUT_FILENO);
			close(cmd->output);
		}
		close(cmd->pfd[0]);
		close(cmd->pfd[1]);
		// Execut builtin
		if (builtin_ptr)
		{
			builtin_ptr(get_ms(), cmd->tab);
			exit (0);
		}
		else if (cmd->path)
		{
			res = execve(cmd->path, cmd->tab, get_ms()->env);
		}
		ft_raise_err("command not found", res);
		exit(555);
	}

}

/*
	@brief Execute t_exec_node list
*/
void ft_execute_list(t_exec_node *head)
{
	t_exec_node	*ptr;

	ptr = head;
	while (ptr)
	{
		ft_set_node_pipes(ptr);
		ft_execute_node(ptr);
		if (ptr->input > 2)
			close(ptr->input);
		if (ptr->output > 2)
			close(ptr->output);
		ptr = ptr->next;
	}

	ptr = head;
	while (ptr)
	{
		waitpid(ptr->pid, NULL, 0);
		close(ptr->pfd[0]);
		close(ptr->pfd[1]);
		ptr = ptr->next;
	}
}
