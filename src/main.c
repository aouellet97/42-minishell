/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:50:43 by kmehour           #+#    #+#             */
/*   Updated: 2023/07/28 10:52:06 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	set_signal_actions();
	while (1)
	{
		line = readline("minishell > ");
		if (!line || ft_strcmp(line, "exit") == 0)
		{
			printf("exit");
			exit(0);
		}
		if (*line)
			add_history(line);
		free(line);
	}
}
