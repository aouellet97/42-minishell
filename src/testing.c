/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:51:46 by kmehour           #+#    #+#             */
/*   Updated: 2023/10/15 15:35:58 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void test_parsing(char *line){
	ft_change_wspace(line);
	char **list = ft_split(line, SPLIT_SEP);
	ft_print_tab(list);
}

void ft_print_tab(char **list)
{
	int i = 0;

	printf("\n\n\t========= TABLE =========\n");
	while(list[i])
	{
		printf("\t- %s\n", list[i]);
		i++;
	}
	printf("\n\t=========================\n\n");
}

void ft_print_exec_struct(t_exec *cmd)
{
	
	printf("\
	============ Command ============\n\
	\tInput : %i\n\
	\tOutput : %i\n\
	\tPath : %s\n\
	=================================\n\
	", cmd->infile, cmd->outfile, cmd->path);
	
	ft_print_tab(cmd->tab);
}













