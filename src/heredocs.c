/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:40:51 by kmehour           #+#    #+#             */
/*   Updated: 2023/12/06 17:40:52 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_expand(char*line)
{
	char	*gc_line;
	int		i;

	i = 0;
	gc_line = ft_strdup(line);
	free(line);
	while (gc_line[i])
	{
		if (gc_line[i] == '$' && gc_line[i + 1] == '?')
			gc_line = expand_exit_status(gc_line, i);
		if (gc_line[i] == '$')
			gc_line = expand_dollar_sign(gc_line, &i);
		i++;
	}
	get_ms()->hdline = gc_line;
	gc_detach(get_ms()->hdline);
}

int	open_heredoc_file(void)
{
	static int	heredoc_i = 0;
	char		*file_name;
	char		*n;

	n = ft_itoa(heredoc_i);
	file_name = ft_strjoin("/tmp/.heredoc_file-", n);
	get_ms()->hd_filename = file_name;
	gc_free(n);
	heredoc_i++;
	return (ft_open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777));
}

void	heredoc_write(char*eof, int fd, bool expansion)
{
	signal(SIGINT, sigint_handle);
	while (1)
	{
		get_ms()->hdline = readline("> ");
		if (!get_ms()->hdline || (ft_strcmp(get_ms()->hdline, eof) == 0
				&& (ft_strlen(get_ms()->hdline) == ft_strlen(eof))))
			break ;
		if (expansion == true)
			heredoc_expand(get_ms()->hdline);
		ft_putstr_fd(get_ms()->hdline, fd);
		ft_putstr_fd("\n", fd);
		if (get_ms()->hdline)
		{
			free(get_ms()->hdline);
			get_ms()->hdline = NULL;
		}
	}
	if (get_ms()->hdline)
	{
		free(get_ms()->hdline);
		get_ms()->hdline = NULL;
	}
	close(fd);
	ft_free_n_exit(0);
}

int	heredoc_wait_open(int fd, int id, int wstat)
{
	waitpid(id, &wstat, 0);
	close(fd);
	if (WIFEXITED(wstat))
	{
		if (WEXITSTATUS(wstat) == 222)
		{
			get_ms()->stop_hd = true;
			get_ms()->heredeoc_mode = false;
			return (-1);
		}
	}
	fd = ft_open(get_ms()->hd_filename, O_RDONLY, 0777);
	get_ms()->heredeoc_mode = false;
	if (fd == -1)
	{
		get_ms()->stop_hd = true;
		ft_raise_err(NULL, "heredoc error", 1);
		return (-1);
	}
	return (fd);
}

int	ft_create_heredoc(char*eof)
{
	bool	expansion;
	int		fd;
	int		id;
	int		wstat;

	fd = 0;
	id = 0;
	wstat = 0;
	expansion = false;
	if (get_char_index(eof, '\'') == -1 && get_char_index(eof, '\"') == -1)
		expansion = true;
	eof = remove_quotes(eof, 0);
	if (!eof)
		eof = "\0";
	fd = open_heredoc_file();
	get_ms()->hdline = NULL;
	get_ms()->heredeoc_mode = true;
	get_ms()->hd_fd = fd;
	id = fork();
	if (id == 0)
		heredoc_write(eof, fd, expansion);
	return (heredoc_wait_open(fd, id, wstat));
}
