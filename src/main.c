#include "minishell.h"

void reset_loop()
{
	char**new_env;
	int len;
	int i;

	i = 0;

	len = get_env_size(get_ms()->env);
	new_env = malloc(sizeof(char*) * (len +1));
	new_env[len] = NULL;

	while(get_ms()->env[i])
	{
		new_env[i] = malloc(sizeof(char) * ft_strlen(get_ms()->env[i]) + 1);
		//free if error
		ft_strlcpy(new_env[i],get_ms()->env[i],ft_strlen(get_ms()->env[i])+1);
		i++;
	}
	gc_free_all();
	get_ms()->env = copy_env(new_env);
	i = 0;
	while(new_env[i])
	{
		free(new_env[i]);
		i++;
	}
	free(new_env);
	free(get_ms()->line);
}

int	main(int argc, char **argv, char *const envp[])
{
	(void)	argc;
	(void)	argv;
	t_exec_node *exec_list;

	ft_set_signal_actions(SIG_MAIN);
	get_ms()->env = copy_env(envp);
	get_ms()->ms_errno = 0;
	exec_list = NULL;
	while (1)
	{
		get_ms()->stop_hd = false;
		//	Readline
		get_ms()->line = readline("minishell > ");
		//	Check exit conditions
		if (!get_ms()->line || ft_strcmp(get_ms()->line, "exit") == 0)
		{
			printf("exit\n");
			gc_free_all();
			exit(get_ms()->ms_errno);
		}

		//	Append to history
		if (*get_ms()->line)
		{
			// Add modified line to history
			add_history(get_ms()->line);

			// Create tokens from raw line
			t_ms_token *token_list = ft_tokenize(get_ms()->line);
			
			// Create t_exec_node list from tokens
			exec_list = ft_init_exec_list(token_list);
			

			// Execute Command(s)
			ft_execute_list(exec_list);
		}
		//free(get_ms()->line);
		reset_loop();
	}
}
