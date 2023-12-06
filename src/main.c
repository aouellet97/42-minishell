/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:40:50 by kmehour           #+#    #+#             */
/*   Updated: 2023/12/06 17:40:51 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_loop(void)
{
	int	i;

	get_ms()->rl_env = get_ms()->env;
	i = 0;
	while (get_ms()->rl_env[i])
	{
		gc_detach(get_ms()->rl_env[i]);
		i++;
	}
	gc_detach(get_ms()->rl_env);
	gc_free_all();
	get_ms()->env = copy_env(get_ms()->rl_env);
	i = 0;
	while (get_ms()->rl_env[i])
	{
		free(get_ms()->rl_env[i]);
		i++;
	}
	free(get_ms()->rl_env);
}

void	init_ms(void)
{
	get_ms()->rl_env = NULL;
	get_ms()->reset_loop_flag = false;
	get_ms()->found_error = false;
	get_ms()->stop_hd = false;
	get_ms()->last_valid_tk = NULL;
}

int	ft_exec_line(void)
{
	t_ms_token	*token_list;
	t_exec_node	*exec_list;

	exec_list = NULL;
	token_list = NULL;
	if (*get_ms()->line)
	{
		add_history(get_ms()->line);
		token_list = ft_tokenize(get_ms()->line);
		if (get_ms()->reset_loop_flag == true)
		{
			reset_loop();
			return (1);
		}
		exec_list = ft_init_exec_list(token_list);
		ft_execute_list(exec_list);
	}
	return (0);
}

int	main(int argc, char **argv, char *const envp[])
{
	(void) argc;
	(void) argv;
	get_ms()->env = copy_env(envp);
	while (1)
	{
		ft_set_signal_actions(SIG_MAIN);
		init_ms();
		get_ms()->line = readline("minishell > ");
		if (!get_ms()->line || ft_strcmp(get_ms()->line, "exit") == 0)
		{
			printf("exit\n");
			gc_free_all();
			free(get_ms()->line);
			exit(get_ms()->ms_errno);
		}
		if (ft_exec_line() == 1)
			continue ;
		reset_loop();
	}
}
