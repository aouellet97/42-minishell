/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:51:46 by kmehour           #+#    #+#             */
/*   Updated: 2023/10/14 12:06:17 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

void test_parsing(char *line){
	change_wspace(line);
	char **list = ft_split(line, SPLIT_SEP);
	print_tab(list);
}

void print_tab(char **list)
{
	int i = 0;

	printf("\n\n========= DEBUG =========\n\n");
	while(list[i])
	{
		printf("%s\n", list[i]);
		i++;
	}
	printf("\n\n=========================\n\n");
}



