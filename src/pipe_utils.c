#include "minishell.h"

/*
	@brief Duplicats an fd if it is not STD
 */
int	ft_dup2(int fd, int dest)
{
	int	res;

	res = 0;
	if (fd > STDERR_FILENO)
		res = dup2(fd, dest);
	if (res == -1)
	{
		ft_raise_err("Critical", "Dup2 error", 69);
	}
	return (res);
}

/*
	@brief Create a pipe and sets the in/out of current and next node
 */
void	ft_set_node_pipes(t_exec_node *node)
{
	if (!node || !node->next)
		return ;
	if (pipe(node->pfd) == -1)
	{
		ft_raise_err("Critical", "Pipe error", 69);
		ft_free_n_exit(1);
	}
	if (node->output == STDOUT_FILENO)
		node->output = node->pfd[1];
	if (node->next->input == STDIN_FILENO)
		node->next->input = node->pfd[0];
	node->next->prev_pipe_out = node->pfd[0];
}

/*
	@brief duplicates node in/out and close remaining fd's
 */
void	ft_dup_in_out(t_exec_node *cmd)
{
	ft_close(cmd->pfd[0]);
	ft_dup2(cmd->input, STDIN_FILENO);
	ft_close(cmd->input);
	ft_dup2(cmd->output, STDOUT_FILENO);
	ft_close(cmd->output);
	ft_close(cmd->pfd[1]);
	ft_close(cmd->prev_pipe_out);
	ft_close_all_fds(get_ms()->fd_list);
}
