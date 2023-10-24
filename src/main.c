#include "minishell.h"

char*replace_vars_by_value(char *line, char *const envp[]);

int	main(int argc, char **argv, char *const envp[])
{
	char	*line;
	(void)	argc;
	(void)	argv;
	t_exec	**exec_tab = NULL;

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

			//	Parse Raw input
			exec_tab = ft_parse_pipes(line, envp);

			//	Execute Command(s)
			ft_execute_tab(exec_tab, envp);
		}
		free(line);
	}
}
