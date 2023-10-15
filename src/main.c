/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:50:43 by kmehour           #+#    #+#             */
/*   Updated: 2023/10/15 13:46:59 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "testing.h"
#include "execution.h"

void test_parsing(char *line);

int	main(int argc, char **argv, char *const envp[])
{
	char	*line;
	(void)	argc;
	(void)	argv;

	ft_set_signal_actions();
	while (1)
	{
		//	Readline
		line = readline("minishell > ");

		//	Check exit conditions
		if (!line || ft_strcmp(line, "exit") == 0)
		{
			printf("exit\n");
			exit(0);
		}
		//	Append to history
		if (*line)
			add_history(line);

		//	Parse Input
		
		//	Execute Command(s)
		ft_exec_strcmd(line, envp);
		

		free(line);
	}
}
