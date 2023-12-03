#include "minishell.h"

int	main(int argc, char **argv, const char *envp[])
{
	char		*line;
	t_exec_node	*exec_list;
	t_ms_token	*token_list;

	(void) argc;
	(void) argv;
	ft_set_signal_actions(SIG_MAIN);
	get_ms()->env = copy_env(envp);
	while (1)
	{
		line = readline("minishell > ");
		if (!line || ft_strcmp(line, "exit") == 0)
		{
			printf("exit\n");
			gc_free_all();
			exit(0);
		}
		if (*line)
		{
			add_history(line);
			token_list = ft_tokenize(line);
			print_tokens(token_list, line);
			exec_list = ft_init_exec_list(token_list);
			ft_print_exec_nodes(exec_list);
			ft_execute_list(exec_list);
		}
		free(line);
	}
}
