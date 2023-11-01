
#include "minishell.h"

/*
	@brief Raise error

	@param err_str Error message to be printed
	@param err_nb Exit status number
*/
void	ft_raise_err(char *err_str, int err_nb)
{
	char *mod_err_str;

	// TODO : add free gc function

	// Distinguish between our raised errors, to be removed !!
	mod_err_str = ft_strjoin("MINISHELL ERROR - ", err_str); // DEBUG line
	perror(mod_err_str);
	free(mod_err_str); // DEBUG line
	exit(err_nb);
}

/*
	@brief Execute Command given as a string
*/
int	ft_exec_struct(t_exec *cmd, char *const envp[])
{
	// ft_print_exec_struct(cmd);
	int res;

	res = -1;
	if (cmd->path)
		res = execve(cmd->path, cmd->tab, envp);
	// ft_free_tab(cmd->tab);
	ft_raise_err("command not found", res);
 	return (2);
}

void	ft_execute(t_exec *cmd, char *const envp[])
{
	// set input outpu gracer a dup2()
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		// ft_set_signal_actions(SIG_CHILD);
		dup2(cmd->input, STDIN_FILENO);
		dup2(cmd->output, STDOUT_FILENO);

		close(cmd->pfd[0]);
		close(cmd->pfd[1]);
		if (cmd->input != STDIN_FILENO)
			close(cmd->input);
		if (cmd->output != STDOUT_FILENO)
			close(cmd->output);


		ft_exec_struct(cmd, envp);
		exit(555);
	}
	if (cmd->input != STDIN_FILENO)
		close(cmd->input);
	if (cmd->output != STDOUT_FILENO)
		close(cmd->output);
}

void ft_execute_tab(t_exec **cmd_tab, char *const envp[])
{
	int i;
	// int pfd[2];

	i = 0;
	while (cmd_tab[i])
	{
		ft_execute(cmd_tab[i], envp);
		i++;
	}

	i = 0;
	while (cmd_tab[i])
	{
		wait(&cmd_tab[i]->pid);
		i++;
	}
}

/*
	@brief Executes a single t_exec_node after setting in and outs
*/
void	ft_execute_node(t_exec_node *cmd, char *const envp[])
{
	int res;
	// set input outpu gracer a dup2()
	res = -1;
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		// ft_set_signal_actions(SIG_CHILD);
		dup2(cmd->input, STDIN_FILENO);
		dup2(cmd->output, STDOUT_FILENO);

		close(cmd->pfd[0]);
		close(cmd->pfd[1]);
		if (cmd->input != STDIN_FILENO)
			close(cmd->input);
		if (cmd->output != STDOUT_FILENO)
			close(cmd->output);

		if (cmd->path)
			res = execve(cmd->path, cmd->tab, envp);
		// ft_free_tab(cmd->tab);
		ft_raise_err("command not found", res);
		exit(555);
	}
	if (cmd->input != STDIN_FILENO)
		close(cmd->input);
	if (cmd->output != STDOUT_FILENO)
		close(cmd->output);
}

/*
	@brief Execute t_exec_node list
*/
void ft_execute_list(t_exec_node *head, char *const envp[])
{
	t_exec_node	*ptr;

	ptr = head;
	while (ptr)
	{
		ft_execute_node(ptr, envp);
		ptr = ptr->next;
	}

	ptr = head;
	while (ptr)
	{
		wait(&ptr->pid);
		ptr = ptr->next;
	}
}

t_exec_node *ft_init_exec_list(t_ms_token *head, char *const envp[])
{
	t_exec_node	dummy;
	t_ms_token	*tk_ptr;
	t_exec_node	*curr_node;
	char		*strcmd;

	tk_ptr = head;
	curr_node = &dummy;
	while(tk_ptr)
	{
		strcmd = NULL;
		while (tk_ptr && tk_ptr->tk_type == TK_STR)
		{
			strcmd = ft_strjoin_char(strcmd, tk_ptr->content, 29);
			tk_ptr = tk_ptr->next;
		}
		if (tk_ptr && tk_ptr->tk_type == TK_PIPE)
		{
			curr_node->next = ft_parse_input(strcmd, envp);
			curr_node = curr_node->next;
			tk_ptr = tk_ptr->next;
		}
	}
	curr_node->next = ft_parse_input(strcmd, envp);
	curr_node = curr_node->next;
	return dummy.next;
}

t_exec_node *ft_creat_exec_node()
{
	t_exec_node *new_node;

	new_node = ft_calloc(1, sizeof(t_exec_node));
	if (new_node == NULL)
		ft_raise_err("Mem allocation error", 1);
	return new_node;
}