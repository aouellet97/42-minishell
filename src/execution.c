/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouellet <aouellet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:08:22 by kmehour           #+#    #+#             */
/*   Updated: 2023/10/18 20:38:42 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*
	@brief Raise error

	@param err_str Error message to be printed
	@param err_nb Exit status number
*/
void	ft_raise_err(char *err_str, int err_nb)
{
	(void) err_str;
	perror(NULL);

	exit(err_nb);
}

/*
	@brief Execute Command given as a string
*/
int	ft_exec_struct(t_exec *cmd, char *const envp[])
{
	// ft_print_exec_struct(cmd);
	int res;

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
		dup2(cmd->infile, STDIN_FILENO);
		dup2(cmd->outfile, STDOUT_FILENO);

		close(cmd->pfd[0]);
		close(cmd->pfd[1]);
		if (cmd->infile != STDIN_FILENO)
			close(cmd->infile);
		if (cmd->outfile != STDOUT_FILENO)
			close(cmd->outfile);


		ft_exec_struct(cmd, envp);
		exit(555);
	}
	if (cmd->infile != STDIN_FILENO)
		close(cmd->infile);
	if (cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
}

void ft_setio(t_exec **cmd_tab)
{
	// ==== DEBUG =====
	// Set pipes manually

	// int infile = open("infile", R_OK, 0644);
	// int outfile = open("outfile", W_OK | O_TRUNC | O_CREAT, 0644);

	// printf("infile %i | outfile %i\n", infile, outfile);
	// dup2(cmd->infile, STDIN_FILENO);
	// dup2(cmd->outfile, STDOUT_FILENO);

	int i;
	int pfd[2];

	i = 0;

	pfd[0] = STDIN_FILENO;
	pfd[1] = STDOUT_FILENO;

	while (cmd_tab[i])
	{
		cmd_tab[i]->infile = pfd[0];
		if (cmd_tab[i + 1] && pipe(pfd) != 0)
		{
			ft_raise_err("Pipe error", 69);
		}
		cmd_tab[i]->outfile = pfd[1];
		i++;
	}


	//=================
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

