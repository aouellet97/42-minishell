#include "minishell.h"

int	main(int argc, char **argv, char *const envp[])
{
	char	*line;
	(void)	argc;
	(void)	argv;
	(void)	envp;
	// t_exec	**exec_tab = NULL;

	ft_set_signal_actions(SIG_MAIN);
	while (1)
	{
		//	Readline
		line = readline("TEST > ");

		// TODO
		// Copy envp[] into linked list

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
			// Create tokens from raw line
			t_ms_token *token_list = ft_tokenize_cmd(line);
			ft_print_tokens(token_list);

			t_exec_node *exec_list;
			exec_list = ft_init_exec_list(token_list);
			ft_set_nodes_pipes(exec_list);
			ft_print_exec_nodes(exec_list);

			ft_execute_list(exec_list);
		}
		free(line);
	}
}
