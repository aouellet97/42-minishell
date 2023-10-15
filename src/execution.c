/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:08:22 by kmehour           #+#    #+#             */
/*   Updated: 2023/10/15 14:13:40 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"
# include "parsing.h"
/* 
	@brief Raise error

	@param err_str Error message to be printed
	@param err_nb Exit status number
*/
void	ft_raise_err(char *err_str, int err_nb)
{
	perror(err_str);
	exit(err_nb);
}

/* 
	@brief Execute Command given as a string
*/
int	ft_exec_strcmd(char *cmd, char *const envp[])
{
	char	**cmd_tab;
	char	*cmd_path;

	cmd_tab = ft_parse_cmd(cmd);
	cmd_path = ft_get_cmd_path(cmd_tab[0], envp);
	int res = -5;
	if (cmd_path)
		res = execve(cmd_path, cmd_tab, envp);

	ft_free_tab(cmd_tab);
	ft_raise_err("command not found", 1);
	return (2);
}