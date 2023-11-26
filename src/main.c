#include "minishell.h"



//-------------------- delete


int	main(int argc, char **argv, char *const envp[])
{
	char	*line;
	(void)	argc;
	(void)	argv;
	t_exec_node *exec_list;

	ft_set_signal_actions(SIG_MAIN);
	get_ms()->env = copy_env(envp);
	
	while (1)
	{
		//	Readline
		line = readline("minishell > ");
		get_ms()->line = line;
		//	Check exit conditions
		if (!line || ft_strcmp(line, "exit") == 0)
		{
			printf("exit\n");
			gc_free_all();
			exit(0);
		}

		//	Append to history
		if (*line)
		{

			// Add modified line to history
			add_history(line);

			// Create tokens from raw line
			t_ms_token *token_list = ft_tokenize(line);

			// Create t_exec_node list from tokens

			exec_list = ft_init_exec_list(token_list);
			
			// Execute Command(s)
			ft_execute_list(exec_list);
		}
		free(line);
	}
}
