#include "minishell.h"

char*replace_vars_by_value(char *line, char *const envp[]);

int	main(int argc, char **argv, char *const envp[])
{
	char	*line;
	(void)	argc;
	(void)	argv;
	t_exec_node *exec_list;

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
			// Add modified line to history
			add_history(line);

			// Parse Raw input
			// Create tokens from raw line
			t_ms_token *token_list = ft_tokenize_cmd(line, envp);

			// Create t_exec_node list from tokens
			exec_list = ft_init_exec_list(token_list, envp);
			
			// Set pipes
			ft_set_nodes_pipes(exec_list);

			//	Execute Command(s)
			ft_execute_list(exec_list, envp);

		}
		free(line);
	}
}
