#include "minishell.h"

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
			print_tokens(token_list, line);

			// Create t_exec_node list from tokens
			exec_list = ft_init_exec_list(token_list);

			// Execute Command(s)
			if(strcmp(line,"env") == 0)
				ft_env(get_ms());
			else if(strcmp(line,"pwd") == 0)
				ft_pwd();
			else if(strcmp(exec_list->tab[0],"echo") == 0)
				ft_echo(exec_list->tab);
			else if(strcmp(exec_list->tab[0],"cd") == 0)
				ft_cd(exec_list->tab,get_ms());
			else if(strcmp(exec_list->tab[0],"export") == 0)
				ft_export(get_ms(),exec_list->tab);
			else if(strcmp(exec_list->tab[0],"unset") == 0)
				ft_unset(get_ms(),exec_list->tab);
			else
				ft_execute_list(exec_list);
		}
		free(line);
	}
}

