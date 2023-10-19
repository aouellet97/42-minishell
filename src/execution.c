/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
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
	ft_raise_err("command not found", 1);
 	return (2);
}

void	ft_execute(t_exec *cmd, char *const envp[])
{
	int pid;

	pid = fork();

	if (pid == 0) 
	{
		ft_exec_struct(cmd, envp);	
	}
	wait(&pid);
}

void ft_execute_tab(t_exec **cmd_tab, char *const envp[])
{
	int i;

	i = 0;
	while (cmd_tab[i])
	{
		ft_execute(cmd_tab[i], envp);
		i++;
	}
}