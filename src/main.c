/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouellet <aouellet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:50:43 by kmehour           #+#    #+#             */
/*   Updated: 2023/10/20 17:48:52 by aouellet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void test_parsing(char *line);

char*replace_vars_by_value(char *line, char *const envp[]);

int	main(int argc, char **argv, char *const envp[])
{
	char	*line;
	(void)	argc;
	(void)	argv;
	//t_exec	*command;

	ft_set_signal_actions(SIG_MAIN);
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
		{
			add_history(line);
			//	Parse Input
			//command = ft_parse_input(line, envp);
			
			//	Execute Command(s)
			//ft_execute(command, envp);
		}
		line = replace_vars_by_value(line,envp);
		printf("%s\n", line);
		
		free(line);
	}
}
