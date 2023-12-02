#include "minishell.h"

void reset_loop(void)
{
	int i;

	get_ms()->rl_env = get_ms()->env;
	i = 0;
	while(get_ms()->rl_env[i])
	{
		gc_detach(get_ms()->rl_env[i]);
		i++;
	}
	gc_detach(get_ms()->rl_env);
	gc_free_all();
	get_ms()->env = copy_env(get_ms()->rl_env);
	i = 0;
	while(get_ms()->rl_env[i])
	{
		free(get_ms()->rl_env[i]);
		i++;
	}
	free(get_ms()->rl_env);
}

void init_ms(void)
{
	// get_ms()->ms_errno = 0;
	get_ms()->rl_env = NULL;
	get_ms()->reset_loop_flag = false;
	get_ms()->found_error = false;
	get_ms()->stop_hd = false;
	get_ms()->last_valid_tk = NULL;
}

int	main(int argc, char **argv, char *const envp[])
{
	(void)	argc;
	(void)	argv;
	t_exec_node *exec_list;

	ft_set_signal_actions(SIG_MAIN);
	get_ms()->env = copy_env(envp);
	t_ms *tmp = get_ms();
	(void) tmp;
	exec_list = NULL;
	while (1)
	{
		init_ms();
		//	Readline
		get_ms()->line = readline("minishell > ");
		//	Check exit conditions
		if (!get_ms()->line || ft_strcmp(get_ms()->line, "exit") == 0)
		{
			printf("exit\n");
			gc_free_all();
			free(get_ms()->line);
			exit(get_ms()->ms_errno);
		}

		//	Append to history
		if (*get_ms()->line)
		{
			// Add modified line to history
			add_history(get_ms()->line);

			// Create tokens from raw line
			t_ms_token *token_list = ft_tokenize(get_ms()->line);
			if (get_ms()->reset_loop_flag == true)
			{
				reset_loop();
				continue;
			}
			// Create t_exec_node list from tokens
			exec_list = ft_init_exec_list(token_list);
			
			// Execute Command(s)
			ft_execute_list(exec_list);
		}
		//free(get_ms()->line);
		reset_loop();
	}
}
