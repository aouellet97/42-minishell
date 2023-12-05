#include "minishell.h"

/*
	@brief Appends an fd to the fd list
 */
void	ft_append_fd(int fd)
{
	t_lst	*new;
	t_lst	*head;

	head = get_ms()->fd_list;
	new = gc_calloc(1, sizeof(t_lst));
	new->value = fd;
	new->next = NULL;
	if (!head)
	{
		get_ms()->fd_list = new;
		return ;
	}
	while (head->next)
		head = head->next;
	head->next = new;
}

int	ft_open(char *path, int flags, int mode)
{
	int	fd;

	fd = open(path, flags, mode);
	ft_append_fd(fd);
	return (fd);
}

int	ft_pipe(int pipefd[2])
{
	int	res;

	res = pipe(pipefd);
	ft_append_fd(pipefd[0]);
	ft_append_fd(pipefd[1]);
	return (res);
}

/*
	@brief Closes an fd if it is not STD
 */
int	ft_close(int fd)
{
	int	res;

	res = 0;
	if (fd > STDERR_FILENO)
		res = close(fd);
	return (res);
}

void	ft_close_all_fds(t_lst *fd_head)
{
	while (fd_head)
	{
		ft_close(fd_head->value);
		fd_head = fd_head->next;
	}
}
